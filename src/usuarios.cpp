/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de interfaz «usuarios.hpp» de un módulo para trabajar con el fichero de 
 *          usuarios del sistema Bizi Zaragoza.
\*********************************************************************************************/

#include "usuarios.hpp" 
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

constexpr char DELIMITADOR {';'};

struct Estadistica {
    unsigned identificador;
    char genero;
    std::string rango_edad;
};

void
leerEstadistica(const string& linea, Estadistica& e) {
    istringstream stream(linea);

    string id;
    getline(stream, id, DELIMITADOR);
    string genero;
    getline(stream, genero, DELIMITADOR);
    string rango_edad;
    getline(stream, rango_edad, DELIMITADOR);

    e.identificador = stoi(id);
    e.genero = genero.at(0);
    e.rango_edad = rango_edad;
}
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
bool obtenerEstadisticas(const string nombreFicheroUsuarios,
                         unsigned estadisticas[][NUM_GENEROS])
{
    ifstream fichero(nombreFicheroUsuarios);
    if (!fichero.is_open()) {
        return false;
    }

    string S;
    getline(fichero, S); // ignorar la cabezera.
    while (getline(fichero, S)) {
        Estadistica estadistica;
        leerEstadistica(S, estadistica);
        auto idx = indiceRangoEdad(estadistica.rango_edad);
        switch (estadistica.genero) {
        case 'M':
            estadisticas[idx][0]++;
        case 'F':
            estadisticas[idx][1]++;
        }
    }

    return true;
}

/*
 * Pre:  El valor del parámetro «rangoEdad» es uno de los valores válidos según la regla 
 *       <rango-edad> establecida en el enunciado ("<=25", "26-35", "36-50", "51-65" o ">65")
 * Post: Devuelve, dependiendo del valor del parámetro «rangoEdad»
 *       ("<=25", "26-35", "36-50", "51-65" o ">65"), respectivamente, 0, 1, 2, 3 o 4.
 */
unsigned indiceRangoEdad(const string rangoEdad) {
    for (int i = 0; i < 5; ++i) {
        if (rangoEdad == RANGO_EDADES[i]) {
            return i;
        }
    }

    return 0;
}

/*
 * Pre:  ---
 * Post: Si el valor del parámetro «genero» es uno de los valores válidos según la regla 
 *       <género> establecida en el enunciado ("M" o "F"), devuelve, respectivamente, 0 o 1.
 *       En caso contrario, devuelve -1.
 */
int indiceGenero(const string genero);

/*
 * Pre:  «nombreFicheroUsuarios» es el nombre de un fichero que cumple con la sintaxis de la 
 *       regla <fichero-usuarios> establecida en el enunciado.
 * Post: Si en el fichero «nombreFicheroUsuarios» hay datos de un usuario con identificador
 *       igual al valor del parámetro «idUsuario», devuelve «true» y asigna a los parámetros
 *       «genero» y «rangoEdad» el valor correspondiente a ese usuario presente en el fichero:
 *       "M", "F" o "" en el caso de «genero» y "<=25", "26-35", "36-50", "51-65" o ">65" en el
 *       caso de «rangoEdad».
 */
bool buscarUsuario(const string nombreFicheroUsuarios, const unsigned idUsuario,
                   string& genero, string& rangoEdad);
