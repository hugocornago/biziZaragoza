/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: 10-01-2023
 * Resumen: Fichero que genera tests aleatorios más pequeños para facilitar
 *          la creacion del programa principal.
\*********************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "nombres-ficheros.hpp"
using namespace std;


/* leer N lineas de un fichero */
/* guardar en un vector de strings */
/* string  lineas[N]*/
bool leerNLineas(string nombreFichero, string vector_lineas[], unsigned numLineas) {
    ifstream fichero {nombreFichero};

    if (!fichero.is_open()) {
        cerr << "No se ha podido abrir el fichero \""
             << nombreFichero << "\"." << endl;
        return false;
    }

    for (unsigned i = 0; i < numLineas; i++) {
        getline(fichero, vector_lineas[i]);
    }

    return true;
}

/* guardar en un fichero nuevo */
bool escribirFichero (string nombreFichero, string vector_lineas[], unsigned longitud) {
    ofstream fichero {nombreFichero};
    if (!fichero.is_open()) {
        cerr << "No se ha podido abrir el fichero \""
             << nombreFichero << "\"." << endl;
        return false;
    }
    for (unsigned i = 0; i < longitud; i++){
        fichero << vector_lineas[i] << endl;
    }
    return true;
}

int main() {
    const string opcion {"16"};
    const string opcion1 {"t1"};
    unsigned numeroDeLineasALeer = 10;
    string lineas[numeroDeLineasALeer];
    if (leerNLineas(construirNombreFicheroUsos(opcion), lineas, numeroDeLineasALeer)) {
        if (escribirFichero(construirNombreFicheroUsos(opcion1), lineas, numeroDeLineasALeer)) {
            cout << "Se ha escrito correctamente el primer fichero." << endl;
        } else {
            return 1;
        }
    } else {
        return 2;
    }
    const string opcion2 {"17"};
    const string opcion3 {"t2"};
    numeroDeLineasALeer = 2000;
    string lineas2[numeroDeLineasALeer];
    if (leerNLineas(construirNombreFicheroUsos(opcion2), lineas2, numeroDeLineasALeer)) {
        if (escribirFichero(construirNombreFicheroUsos(opcion3), lineas2, numeroDeLineasALeer)) {
            cout << "Se ha escrito correctamente el segundo fichero." << endl;
        } else {
            return 1;
        }
    } else {
        return 2;
    }

    return 0;
}
