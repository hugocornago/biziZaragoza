/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de interfaz «usuarios.hpp» de un módulo para trabajar con el fichero de 
 *          usuarios del sistema Bizi Zaragoza.
\*********************************************************************************************/

#pragma once

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const unsigned NUM_EDADES = 5;
const unsigned NUM_GENEROS = 2;
const string RANGO_EDADES[NUM_EDADES] = {"<=25", "26-35", "36-50", "51-65", ">65"};

/*
 * Pre:  «nombreFicheroUsuarios» es el nombre de un fichero que cumple con la sintaxis de la 
 *       regla <fichero-usuarios> establecida en el enunciado. La matriz «estadisticas» tiene
 *       «NUM_EDADES» filas y «NUM_GENEROS» columnas.
 * Post: Asigna a las componentes de la fila indexada por 0 el número de usuarios masculinos
 *       (columna 0) y usuarias femeninas (columna 1) el número de usuarios de 25 años o menos
 *       según el contenido del fichero «nombreFicheroUsuarios». Hace lo análogo en la fila
 *       indexada por 1 con los usuarios de entre 26 y 35 años; en la fila indexada por 2 con
 *       los usuarios de entre 36 y 50 años; en la fila indexada por 3 con los usuarios de
 *       entre 51 y 65 años y en la fila indexada por 4 con los usuarios de 65 años o más.
 *       Si se puede leer del fichero «nombreFicheroUsuarios», devuelve «true» y, en caso
 *       contrario, devuelve «false».
 */
bool obtenerEstadisticas(const string nombreFicheroUsuarios,unsigned estadisticas[][NUM_GENEROS],
unsigned indiceRangoEdad(const string rangoEdad) ) {
    // Abrir el archivo de entrada
    ifstream fichero {nombreFicheroUsuarios};
    // Comprobar si el archivo se ha abierto correctamente
    if (!fichero) {
        return false;
    }
    // Inicializar variables temporales
    string linea;
    string edad;
    string genero;
    // Leer línea por línea del archivo
    while (getline(fichero, linea)) {
        // Dividir la línea en los diferentes campos
        stringstream lineaSS(linea);
        getline(lineaSS, edad, ',');
        getline(lineaSS, genero, ',');
        // Convertir los valores a los tipos de datos adecuados
        int edadInt = stoi(edad);
        char generoChar = genero[0];
        // Incrementar el contador adecuado en la matriz de estadísticas
        unsigned indice = indiceRangoEdad(edad);
    if (indice < NUM_EDADES) {
        if (generoChar == 'M') {
        estadisticas[indice][0]++;
        }   
        else {
        estadisticas[indice][1]++;
        }
    }
}

/*
 * Pre:  El valor del parámetro «rangoEdad» es uno de los valores válidos según la regla 
 *       <rango-edad> establecida en el enunciado ("<=25", "26-35", "36-50", "51-65" o ">65")
 * Post: Devuelve, dependiendo del valor del parámetro «rangoEdad»
 *       ("<=25", "26-35", "36-50", "51-65" o ">65"), respectivamente, 0, 1, 2, 3 o 4.
 */

unsigned indiceRangoEdad(const string rangoEdad){
    for (unsigned i = 0; i < NUM_EDADES; i++) {
        if (rangoEdad == RANGO_EDADES[i]) {
            return i;
        }
    }
    return NUM_EDADES;
}    
/*
 * Pre:  ---
 * Post: Si el valor del parámetro «genero» es uno de los valores válidos según la regla 
 *       <género> establecida en el enunciado ("M" o "F"), devuelve, respectivamente, 0 o 1.
 *       En caso contrario, devuelve -1.
 */
int indiceGenero(const string genero) {
    for (unsigned i = 0; i < NUM_GENEROS; i++) {
        if (genero == GENEROS[i]) {
            return i;
        }
    }
    return -1;
}

/*
 * Pre:  «nombreFicheroUsuarios» es el nombre de un fichero que cumple con la sintaxis de la 
 *       regla <fichero-usuarios> establecida en el enunciado.
 * Post: Si en el fichero «nombreFicheroUsuarios» hay datos de un usuario con identificador
 *       igual al valor del parámetro «idUsuario», devuelve «true» y asigna a los parámetros
 *       «genero» y «rangoEdad» el valor correspondiente a ese usuario presente en el fichero:
 *       "M", "F" o "" en el caso de «genero» y "<=25", "26-35", "36-50", "51-65" o ">65" en el
 *       caso de «rangoEdad».
 */
bool buscarUsuario(const string nombreFicheroUsuarios, const unsigned idUsuario, string& genero, string& rangoEdad) {
    ifstream ficheroUsuarios(nombreFicheroUsuarios);
    if (ficheroUsuarios.is_open()) {
        string linea;
        while (getline(ficheroUsuarios, linea)) {
            stringstream lineaSS(linea);
            unsigned id;
            lineaSS >> id;
            if (id == idUsuario) {
                char generoChar;
                lineaSS >> generoChar;
                if (generoChar == 'M') {
                    genero = "M";
                } else if (generoChar == 'F') {
                    genero = "F";
                } else {
                    genero = "";
                }
                getline(lineaSS, rangoEdad, ',');
                return true;
            }
        }
        ficheroUsuarios.close();
    }
    else {
        return false;
    }
}