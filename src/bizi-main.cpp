/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de implementación del módulo principal que implementa el trabajo
 *          obligatorio de Programación 1 del curso 2022-23.
\*********************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Fichero {
    string nombre;
    ifstream* f;
};

string selectorDeFichero() {
    cout << "Elección de ficheros de usos y usuarios. Opciones disponibles: " << endl;
    cout << "16: octubre 2016 a marzo 2017" << endl;
    cout << "17: marzo 2017 a agosto 2017" << endl;
    cout << "t1: datos para pruebas (10 líneas)" << endl;
    cout << "t2: datos para pruebas (2000 líneas)" << endl;
    cout << "Introduzca una opción: " << endl;

    string opcion;
    cin >> opcion;
    string fichero = "datos/usos-" + opcion + ".csv";
    return fichero;
}

bool cambiarFichero(Fichero& fichero) {
    const auto& nombre_fichero = selectorDeFichero();
    ifstream fichero_abierto {nombre_fichero};
    if (!fichero_abierto.is_open()) {
        cerr << "No se ha podido leer el fichero \"" << nombre_fichero << "\"" << endl;
        return false;
    }

    fichero.nombre = nombre_fichero;
    fichero.f = &fichero_abierto;

    cout << "El fichero \"" << fichero.nombre << "\" existe y ha sido seleccionado." << endl;
}

void pantallaUsos (const Fichero& fichero) {
    cout << "Orden: usos" << endl;
    cout << "Fichero de usos seleccionado actualmente: " << fichero.nombre << "." << endl;
    cout << "Número de usos como traslado: " << endl;
    cout << "Número de usos circulares: " << endl;
    cout << "Número total de usos: " << endl;
    cout << "Orden: " << endl;
}

bool ordenUsos (Fichero& fichero) {
    string numTraslados;   
    string numCirculares;
    int numTotalUsos;
    ifstream fichero_abierto {fichero.nombre};
    if (!fichero_abierto.is_open()){
        string cabecera;
        getline(fichero_abierto, cabecera);
        string uso;
        while (getline(fichero_abierto, uso)){
            numTotalUsos++;
            if(getline(fichero_abierto, numTraslados))
        }
 

     }
     

}

void imprimirOrdenesDisponibles () {
    cout << "ÓRDENES DISPONIBLES" << endl;
    cout << "===================" << endl;
    cout << "AYUDA:" << setw(9) << "Muestra esta pantalla de ayuda." << endl;
    cout << "FICHERO: Permite modificar la selección del fichero de usos a utilizar." << endl;
    cout << "USOS:" << setw(9) << "Escribe en la pantalla el número de usos de traslado y circulares." << endl;
    cout << "ESTADISTICAS:" << setw(9) << "Informa la distribución por edades y géneros de los usuarios." << endl;
    cout << "USUARIO <id-usuario>: Informa acerca del número de usos realizados por el" << endl; 
    cout << setw(9) << "usuario especificado." << endl;
    cout << "MAYORES <n>: " << setw(9) << "Escribe en la pantalla el número de usuarios distintos y los" << endl;
    cout << setw(9) << "<n> usuarios que más usos han hecho del sistema." << endl;
    cout << "INFORME <nombre-fichero>: Escribe en el fichero especificado un informe con el" << endl;
    cout << "número de usos de las estaciones, según el fichero seleccionado." << endl;
    cout << "DESTINOS: <nombre-fichero>: " << setw(9) << "Escribe en el fichero especificado un informe en" << endl;
    cout << setw(9) << "el que, para cada estación dada, se indica la estación a la que más." << endl;
    cout << setw(9) << "se ha viajado desde ella." << endl;
    cout << "FIN: " << setw(9) << "Termina la ejecución de este programa." << endl;
}

bool ejecutarOrden(const string& orden, Fichero& fichero) {
    if (orden == "AYUDA") {
        imprimirOrdenesDisponibles();
    } else
    if (orden == "FICHERO") {
        while (!cambiarFichero(fichero))
    }
    if (orden == "USOS"){
        ordenUsos(fichero);
    }

    else
    if (orden == "FIN") {
        return true;
    }

}

bool elejirOrden(Fichero& fichero) {
    string orden;
    cin >> orden;

    /* Transformar cada caracter de la string <orden> a 
       mayusculas con la orden std::toupper().
    */
    transform(orden.begin(), orden.end(), orden.begin(),
        [](unsigned char c){ return std::toupper(c); });

    return ejecutarOrden(orden, fichero);
}


int main(){
    Fichero f;
    bool parar {false};

    imprimirOrdenesDisponibles();
    while (!parar) {
        if (elejirOrden(f)) {
            /* elejirOrden devuelve true cuando el usuario ha decidido salir del programa.*/
            parar = true;
        }
    }
    return 0;
}
