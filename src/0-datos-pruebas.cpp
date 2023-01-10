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


/*
 * Pre:  ---
 * Post: Devuelve una ruta de acceso relativa a un fichero de usos partiendo del valor del 
 *       parámetro «opcion», concatenando la ruta relativa de acceso al directorio de datos con
 *       el prefijo común a los ficheros de usos, la opción y la extensión de los fichero de
 *       usos.
 *       Por ejemplo, si «opcion» tiene el valor "16", devuelve la ruta "datos/usos-16.csv".
 *       Si «opcion» tiene el valor "t2", devuelve la ruta "datos/usos-t2.csv".
 */
string construirNombreFicheroUsos(const string opcion){
    return RUTA_DATOS + PREFIJO_USOS + opcion + EXTENSION;
}

/*
 * Pre: vector_lineas debe tener <numLineas>.
 * Post: Lee <numLineas> de <nombreFichero> y las almacena en <vector_lineas>
 */
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

/* 
 * Pre: <vector_lineas> contiene <longitud> o más elementos.
 * Post: Escribe en <nombreFichero>, <longitud> elementos de <vector_lineas> 
 *       separados por un salto de linea.
*/
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

/* 
 * Pre: ---
 * Post: Escribe dos ficheros (datos/usos-t1.csv) y (datos/usos-t2.csv) basandose en la especificación
 *       del enunciado.
*/
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
