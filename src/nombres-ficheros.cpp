#include <string>
#include <iostream>
#include "nombres-ficheros.hpp"
using namespace std;

const string RUTA_DATOS = "datos/";
const string PREFIJO_USOS = "usos-";
const string EXTENSION = ".csv";
const string FICHERO_ESTACIONES = RUTA_DATOS + "estaciones.csv";
const string FICHERO_USUARIOS = RUTA_DATOS + "usuarios.csv";
const string FICHERO_AYUDA = "res/ayuda.txt";
const string FICHERO_OPCIONES = "res/opciones.txt";


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
    if (opcion == "16"| opcion == "17"| opcion == "t1"| opcion == "t2"){
        return RUTA_DATOS + PREFIJO_USOS + opcion + EXTENSION;
    }    
    if (opcion == "estaciones"){
        return FICHERO_ESTACIONES;
    }
    if (opcion == "usuarios"){
        return FICHERO_USUARIOS;
    }
    if (opcion == "opciones"){
        return FICHERO_OPCIONES;
    }
        if (opcion == "ayuda") {
        return FICHERO_AYUDA;
    }
    else{
        cerr << "Seleccione una opción válida" << endl;
    }
}