// Presentado por Juan David Rodriguez Casanova Y Luis Carlos Gomez Urquijo

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

struct Asientos {                                                                                              //se crea el struct de asientos 
    int asientos[100];
};
void asignarAsiento(Asientos& sala) {
    int numeroAsiento;
    string nombre;
    string documentodeidentidad;
    string apellido;
    cout<<"|  Ingrese su primer nombre.  |"<<endl;
    cin >> nombre;
    cout << "|  Ingrese su primer apellido.  |" << endl;
    cin >> apellido;
    cout << "|  Ingrese su numero de cedula ciudadana  |" <<endl;
    cin >> documentodeidentidad;
    cout << "|  Ingrese el numero de asiento que desea asignar (1-100): |"<<endl;
    cin >> numeroAsiento;
    if (numeroAsiento < 1 || numeroAsiento > 100) {
        cout << "|  Numero de asiento invalido.  |" <<endl;
        while (numeroAsiento < 1 || numeroAsiento > 100) {
            cout << "|  Ingrese un numero valido: |";
            cin >> numeroAsiento;
        }
        return;
    }
    else if (sala.asientos[numeroAsiento - 1] == 1) {
        while (sala.asientos[numeroAsiento - 1] == 1) {
            cout << "El asiento " << numeroAsiento << " ya esta ocupado. Por favor, ingrese otro." << endl;
            cin >> numeroAsiento;
            if (sala.asientos[numeroAsiento - 1] == 0) {
                sala.asientos[numeroAsiento - 1] = 1;
                break;
            }
        }
        return;
    }
    else {
        // Aquí se maneja el caso en el que el asiento no está asignado
        sala.asientos[numeroAsiento - 1] = 1;
        //se crea las variables que asignaran las propiedades del recibo
        int contador=0;
        contador++;
        string nombre_del_recibo = "Recibo de "+nombre+" "+apellido+ " nº" + to_string(contador) + ".txt";
        // se llama la funcion
        ofstream archivo(nombre_del_recibo);
        if (archivo.is_open()) {
            archivo << "---------------------------------" << endl;
            archivo << "|        CINE ADMINBITS        |" << endl;
            archivo << "---------------------------------" << endl;
            archivo << "| Nombre " <<nombre<<" "<< apellido << " |" << endl;
            archivo << "| Asiento numero: " <<numeroAsiento<<" |" << endl;
            archivo << "| Numero de de documento: " <<documentodeidentidad <<" |" << endl;
            archivo << "| Costo del asiento: 7000$"<< endl;
            archivo << "---------------------------------" << endl;
            archivo.close();
            cout << "El archivo con el costo del asiento ha sido creado correctamente." << endl;
        }
        else {
            cout << "No se pudo crear el archivo." << endl;
        }

        cout << "Asiento " << numeroAsiento << " asignado correctamente." << endl;
    }
}
void imprimirEstadoAsientos(const Asientos& sala) {                                                           //se crea funcion para imprimir los asientos de forma ordenada
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

// Función para obtener la hora local que se imprime en pantalla
void obtenerHoraLocal() {                                                                                     //se crea funcion para obtener la hora local del sistema para poder funcionar de acuerdo el horario de las pelicular
    // Obtener el tiempo actual
    time_t tiempoActual = time(0);

    // Crear una estructura tm para almacenar la hora local
    struct tm horaLocal;

    // Convertir el tiempo actual a hora local
    if (localtime_s(&horaLocal, &tiempoActual) == 0) {
        // Imprimir la hora local
        cout << "---La hora actual es: " << horaLocal.tm_hour << ":"
            << horaLocal.tm_min << ":" << horaLocal.tm_sec << endl;
    }
    else {
        cerr << "Error al obtener la hora local" << endl;
    }
}
//funcion que reinicia las salas 
void reiniciarAsientos(Asientos& sala1, Asientos& sala2) {
    time_t tiempoActual = time(0);
    struct tm horaLocal;
    localtime_s(&horaLocal, &tiempoActual);

    int hour = horaLocal.tm_hour;
    int min = horaLocal.tm_min;
    //formateo de la sala 1
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
    //formateo de la sala 2
    if ((hour == 12 && min >= 1 && min <= 2) ||
        (hour == 13 && min >= 55 && min <= 56) ||
        (hour == 15 && min >= 50 && min <= 51) ||
        (hour == 18 && min >= 1 && min <= 2) ||
        (hour == 20 && min >= 14 && min <= 15) ||
        (hour == 22 && min >= 31 && min <= 32)) {
        for (int i = 0; i < 100; i++) {
            sala2.asientos[i] = 0;
            cout << "|------Los asientos de la sala 2 han sido reiniciados.------|"<< endl;
        }
    }

}
int main() {
    Asientos sala1 = { 0 };
    Asientos sala2 = { 0 };
    //tiene que estar aqui para que se inicialize en 0 solo una vez como partida
    while (true) {

        cout << "|   Hola bienvenido a ADMINBITS tu software de administracion de cine   |"<< endl;
        cout << "| Peliculas de sala uno:                                                        |\n";
        cout << "| Atrapados en lo profundo           - Hora de inicio: 10 AM    - Fin: 11:15 AM |\n";
        cout << "| Ghostbusters                       - Hora de inicio: 11:55 AM - Fin: 1:55 PM  |\n";
        cout << "| Spy x Family Codigo:Blanco         - Hora de inicio: 2:15 PM  - Fin: 4:05 PM  |\n";
        cout << "| Godzilla y Kong:El nuevo imperio   - Hora de inicio: 4:25 PM  - Fin: 6:20 PM  |\n";
        cout << "| Kung Fu Panda 4                    - Hora de inicio: 6:40 PM  - Fin: 8:14 PM  |\n";
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

        if (salaElegida == 1) {
            imprimirEstadoAsientos(sala1);
            asignarAsiento(sala1);
        }
        else if (salaElegida == 2) {
            imprimirEstadoAsientos(sala2);
            asignarAsiento(sala2);

        }
        else {
            cout << "Sala inválida." << endl;
            return 1;
        }


        obtenerHoraLocal();// Llamar a la función para obtener la hora local que se imprime en pantalla
        reiniciarAsientos(sala1, sala2);//funcion que formatea las salas 

    }

    return 0;
}