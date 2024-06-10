// Presentado por Juan David Rodriguez Casanova Y Luis Carlos Gomez Urquijo

#include <iostream>
#include <ctime>


using namespace std;

struct Asientos {                                                                                              //se crea el struct de asientos 
    int asientos[100];
};
void asignarAsiento(Asientos& sala) {                                                                          //se crea la funcion de añadir asientos,posible parta del codigo donde se llevara acabo la facturacion
    cout << "Ingrese el número de asiento que desea asignar (1-100): ";
    int numeroAsiento;
    cin >> numeroAsiento;
    if (numeroAsiento < 1 || numeroAsiento > 100) {
        cout << "Número de asiento inválido." << endl;
        while (numeroAsiento < 1 || numeroAsiento > 100) {
            cout << "ingrese un numero valido: ";
            cin >> numeroAsiento;
        }
        return;
    }
    else if (sala.asientos[numeroAsiento - 1] == 1) {
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
    else {
        sala.asientos[numeroAsiento - 1] = 1;
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
        cout << "La hora actual es: " << horaLocal.tm_hour << ":"
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
            cout << "Los asientos de la sala 1 han sido reiniciados." << endl;
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
            cout << "Los asientos de la sala 2 han sido reiniciados." << endl;
        }
    }
    
}
int main() {
    Asientos sala1 = { 0 };
    Asientos sala2 = { 0 };
    //tiene que estar aqui para que se inicialize en 0 solo una vez como partida
    while (true) {

        cout << "Hola bienvenido a ADMINBITS tu software de administracion de cine" << endl;
        cout << "Ingresa a la sala que deseas ingresar (1 o 2): ";
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
        reiniciarAsientos(sala1,sala2);//funcion que formatea las salas 

    }

    return 0;
}
