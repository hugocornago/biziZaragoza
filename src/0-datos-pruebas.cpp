/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: 
 * Resumen: Fichero que genera tests aleatorios más pequeños para facilitar
 *          la creacion del programa principal.
\*********************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
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
    const string ficheroOriginal {"datos/usos-16.csv"};
    string ficheroDestino {"datos/usos-t1.csv"};
    unsigned numeroDeLineasALeer = 10;
    string lineas[numeroDeLineasALeer];
    if (leerNLineas(ficheroOriginal, lineas, numeroDeLineasALeer)) {
        if (escribirFichero(ficheroDestino, lineas, numeroDeLineasALeer)) {
            cout << "Se ha escrito correctamente el primer fichero." << endl;
        } else {
            return 1;
        }
    } else {
        return 2;
    }

    ficheroDestino = "datos/usos-t2.csv";
    numeroDeLineasALeer = 2000;
    string lineas2[numeroDeLineasALeer];
    if (leerNLineas(ficheroOriginal, lineas2, numeroDeLineasALeer)) {
        if (escribirFichero(ficheroDestino, lineas2, numeroDeLineasALeer)) {
            cout << "Se ha escrito correctamente el segundo fichero." << endl;
        } else {
            return 1;
        }
    } else {
        return 2;
    }

    return 0;
}
