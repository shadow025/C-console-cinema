#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Asientos {
    int asientos[100];
};

struct Pelicula {
    string nombre;
    int horaInicio;
    int minutoInicio;
    int horaFin;
    int minutoFin;
};

// Función para asignar un asiento
void asignarAsiento(Asientos& sala) {
    int numeroAsiento;
    string nombre;
    string documentodeidentidad;
    string apellido;

    cout << "|  Ingrese su primer nombre: ";
    cin >> nombre;
    cout << "|  Ingrese su primer apellido: ";
    cin >> apellido;
    cout << "|  Ingrese su número de cedula ciudadana: ";
    cin >> documentodeidentidad;
    cout << "|  Ingrese el número de asiento que desea asignar (1-100): ";
    cin >> numeroAsiento;

    // Validar número de asiento
    if (numeroAsiento < 1 || numeroAsiento > 100) {
        cout << "|  Número de asiento inválido.  |" << endl;
        while (numeroAsiento < 1 || numeroAsiento > 100) {
            cout << "|  Ingrese un número válido: ";
            cin >> numeroAsiento;
        }
        return;
    }

    // Verificar si el asiento ya está ocupado
    if (sala.asientos[numeroAsiento - 1] == 1) {
        while (sala.asientos[numeroAsiento - 1] == 1) {
            cout << "El asiento " << numeroAsiento << " ya está ocupado. Por favor, ingrese otro." << endl;
            cin >> numeroAsiento;
            if (sala.asientos[numeroAsiento - 1] == 0) {
                sala.asientos[numeroAsiento - 1] = 1;
                break;
            }
        }
        return;
    }

    // Asignar el asiento
    sala.asientos[numeroAsiento - 1] = 1;

    // Generar recibo
    int contador = 0;
    contador++;
    string nombre_del_recibo = "Recibo_de_" + nombre + "_" + apellido + "_nº" + to_string(contador) + ".txt";
    ofstream archivo(nombre_del_recibo);
    if (archivo.is_open()) {
        archivo << "---------------------------------" << endl;
        archivo << "|        CINE ADMINBITS        |" << endl;
        archivo << "---------------------------------" << endl;
        archivo << "| Nombre: " << nombre << " " << apellido << " |" << endl;
        archivo << "| Asiento número: " << numeroAsiento << " |" << endl;
        archivo << "| Número de documento: " << documentodeidentidad << " |" << endl;
        archivo << "| Costo del asiento: $7000" << endl;
        archivo << "---------------------------------" << endl;
        archivo.close();
        cout << "El archivo con el costo del asiento ha sido creado correctamente." << endl;
    }
    else {
        cout << "No se pudo crear el archivo." << endl;
    }

    cout << "Asiento " << numeroAsiento << " asignado correctamente." << endl;
}

// Función para imprimir el estado de los asientos
void imprimirEstadoAsientos(const Asientos& sala) {
    cout << "Estado de los asientos:" << endl;
    for (int fila = 0; fila < 10; fila++) {
        for (int columna = 0; columna < 10; columna++) {
            int indice = fila * 10 + columna;
            cout << "|L " << indice + 1 << ": ";
            if (sala.asientos[indice] == 0) {
                cout << "D ";
            }
            else {
                cout << "O ";
            }
        }
        cout << endl;
    }
}

// Función para obtener la hora local
void obtenerHoraLocal() {
    time_t tiempoActual = time(0);
    struct tm horaLocal;
    if (localtime_s(&horaLocal, &tiempoActual) == 0) {
        cout << "---La hora actual es: " << horaLocal.tm_hour << ":"
            << horaLocal.tm_min << ":" << horaLocal.tm_sec << endl;
    }
    else {
        cerr << "Error al obtener la hora local" << endl;
    }
}

// Función para reiniciar los asientos de las salas
void reiniciarAsientos(Asientos& sala1, Asientos& sala2) {
    time_t tiempoActual = time(0);
    struct tm horaLocal;
    localtime_s(&horaLocal, &tiempoActual);

    int hour = horaLocal.tm_hour;
    int min = horaLocal.tm_min;
    // Formateo de la sala 1
    if ((hour == 11 && min >= 35 && min <= 36) ||
        (hour == 13 && min >= 55 && min <= 56) ||
        (hour == 16 && min >= 5 && min <= 6) ||
        (hour == 18 && min >= 20 && min <= 21) ||
        (hour == 20 && min >= 15 && min <= 16) ||
        (hour == 22 && min >= 31 && min <= 32)) {
        for (int i = 0; i < 100; i++) {
            sala1.asientos[i] = 0;
            cout << "|------Los asientos de la sala 1 han sido reiniciados.------|" << endl;
        }
    }
    // Formateo de la sala 2
    if ((hour == 12 && min >= 1 && min <= 2) ||
        (hour == 13 && min >= 55 && min <= 56) ||
        (hour == 15 && min >= 50 && min <= 51) ||
        (hour == 18 && min >= 1 && min <= 2) ||
        (hour == 20 && min >= 14 && min <= 15) ||
        (hour == 22 && min >= 31 && min <= 32)) {
        for (int i = 0; i < 100; i++) {
            sala2.asientos[i] = 0;
            cout << "|------Los asientos de la sala 2 han sido reiniciados.------|" << endl;
        }
    }
}

// Función para seleccionar una película y verificar disponibilidad
Pelicula seleccionarPelicula() {
    Pelicula peliculas[] = {
        {"Atrapados en lo profundo", 10, 0, 11, 15},
        {"Ghostbusters", 11, 55, 13, 55},
        {"Spy x Family Código: Blanco", 14, 15, 16, 5},
        {"Godzilla y Kong: El nuevo imperio", 16, 25, 18, 20},
        {"Kung Fu Panda 4", 18, 40, 20, 14},
        {"La Primera profecía", 20, 34, 22, 31}
    };

    cout << "Selecciona una película ingresando su número:" << endl;
    for (int i = 0; i < sizeof(peliculas) / sizeof(peliculas[0]); ++i) {
        cout << i + 1 << ". " << peliculas[i].nombre << " - Hora de inicio: " << peliculas[i].horaInicio << ":"
            << peliculas[i].minutoInicio << " - Fin: " << peliculas[i].horaFin << ":" << peliculas[i].minutoFin << endl;
    }

    int opcion;
    cin >> opcion;

    return peliculas[opcion - 1];
}

int main() {
    Asientos sala1 = { 0 };
    Asientos sala2 = { 0 };

    while (true) {
        cout << "|   Hola bienvenido a ADMINBITS tu software de administracion de cine   |" << endl;
        // Mostrar las películas y horarios disponibles
        cout << "| Peliculas de sala uno:                                                        |\n";
        cout << "| Atrapados en lo profundo           - Hora de inicio: 10 AM    - Fin: 11:15 AM |\n";
        cout << "| Ghostbusters                       - Hora de inicio: 11:55 AM - Fin: 1:55 PM  |\n";
        cout << "| Spy x Family Codigo:Blanco         - Hora de inicio: 2:15 PM  - Fin: 4:05 PM  |\n";
        cout << "| Godzilla y Kong:El nuevo imperio   - Hora de inicio: 4:25 PM  - Fin: 6:20 PM  |\n";
        cout << "| Kung Fu Panda 4                    - Hora de inicio: 6:40 PM  - Fin: 8:14 PM | \n";
        cout << "| La Primera profecia                - Hora de inicio: 8:34 PM  - Fin: 10:31 PM |\n";
        cout << "\n";
        cout << "| Peliculas de sala dos:                                                        |\n";
        cout << "| Ghostbusters                      - Hora de inicio: 10:00 AM - Fin: 12:00 PM  |\n";
        cout << "| Atrapados en lo profundo          - Hora de inicio: 12:20 PM - Fin: 1:55 PM   |\n";
        cout << "| Kung Fu Panda 4                   - Hora de inicio: 2:15 PM  - Fin: 3:49 PM   |\n";
        cout << "| Spy x Family Código: Blanco       - Hora de inicio: 4:09 PM  - Fin: 5:59 PM   |\n";
        cout << "| Godzilla y Kong: El nuevo imperio - Hora de inicio: 6:19 PM  - Fin: 8:14 PM   |\n";
        cout << "| La primera profecía               - Hora de inicio: 8:34 PM  - Fin: 10:31 PM  |\n";
        cout << "|    Ingresa a la sala que deseas ingresar (1 o 2):    |";

        int salaElegida;
        cin >> salaElegida;

        Pelicula peliculaSeleccionada;

        if (salaElegida == 1) {
            cout << "Selecciona una película de la sala 1:" << endl;
            peliculaSeleccionada = seleccionarPelicula();
        }
        else if (salaElegida == 2) {
            cout << "Selecciona una película de la sala 2:" << endl;
            peliculaSeleccionada = seleccionarPelicula();
        }
        else {
            cout << "Sala inválida." << endl;
            return 1;
        }

        // Obtener la hora actual
        time_t tiempoActual = time(0);
        struct tm horaLocal;
        localtime_s(&horaLocal, &tiempoActual);
        int horaActual = horaLocal.tm_hour;
        int minutoActual = horaLocal.tm_min;

        // Verificar si la película está disponible
        if (horaActual < peliculaSeleccionada.horaInicio ||
            (horaActual == peliculaSeleccionada.horaInicio && minutoActual < peliculaSeleccionada.minutoInicio)) {
            cout << "¡Puedes ver la película '" << peliculaSeleccionada.nombre << "'!" << endl;
        }
        else if (horaActual > peliculaSeleccionada.horaFin ||
            (horaActual == peliculaSeleccionada.horaFin && minutoActual > peliculaSeleccionada.minutoFin)) {
            cout << "La película '" << peliculaSeleccionada.nombre << "' ya ha comenzado o finalizado." << endl;
            cout << "Selecciona otra película o intenta más tarde." << endl;
            continue;
        }
        else {
            cout << "La película '" << peliculaSeleccionada.nombre << "' está en curso. ¡Disfrútala!" << endl;
        }

        // Imprimir estado de los asientos según la sala elegida
        if (salaElegida == 1) {
            imprimirEstadoAsientos(sala1);
            asignarAsiento(sala1);
        }
        else if (salaElegida == 2) {
            imprimirEstadoAsientos(sala2);
            asignarAsiento(sala2);
        }

        obtenerHoraLocal(); // Obtener y mostrar la hora local
        reiniciarAsientos(sala1, sala2); // Reiniciar asientos según el horario

    }

    return 0;
}

