/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de interfaz «estacion.hpp» de un módulo para trabajar con
 *          registros que representan estaciones del sistema Bizi Zaragoza.
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\*********************************************************************************************/

#pragma once
#include "estacion.hpp"
#include <iostream>
#include <istream>
#include <string>
#include <fstream>
using namespace std;

const int NUM_ESTACIONES = 130;


/*
 * Pre:  La cadena de caracteres «nombreFicheroEstaciones» contiene la ruta de acceso y nombre
 *       de un fichero de estaciones Bizi que sigue la sintaxis de la regla
 *       <fichero-estaciones> establecida en el enunciado y que contiene información de
 *       «NUM_ESTACIONES» estaciones.
 *       El vector «estaciones» tiene «NUM_ESTACIONES» componentes.
 * Post: Si el fichero «nombreFicheroEstaciones» y se puede leer de él, la función devuelve
 *       «true» y lee los datos de las estaciones Bizi contenidos en el fichero indicado por
 *       «nombreFicheroEstaciones» y se han almacenado en el vector «estaciones» de forma tal
 *       que en cada componente «i» se almacena el identificador y el nombre de la estación de
 *       identificador «i» + 1 (es decir, en estaciones[0] se encuentra almacenada la
 *       información de la estación con identificador 1, en estaciones[1] se encuentra
 *       almacenada la estación con identificador 2 y así sucesivamente). La información sobre
 *       el número de usos de cada estación es 0 en todas ellas. Si no se puede leer el
 *       fichero «nombreFicheroEstaciones», se limita a devolver «false».
 */
bool leerEstaciones(const string nombreFicheroEstaciones, Estacion estaciones[]) {
    const int NUM_BARRAS = 7;
    char DELIMITADOR = ';';
    char BARRA = '/';
    // Abrimos el fichero de estaciones
    ifstream fichero {nombreFicheroEstaciones};

    // Si no se ha podido abrir, devolvemos false
    if (!fichero.is_open()) {
        return false;
    }
    /* Ignorar la cabezera */
    string cabezera;
    getline(fichero, cabezera);

    for (unsigned i = 0; i<NUM_ESTACIONES; i++){
        for (unsigned n = 0; n<=NUM_BARRAS; n++){
            string estacion;
            if(n<7){
                getline(fichero, estacion, BARRA);
            }
            else{
                getline(fichero, estacion, DELIMITADOR);
                estaciones[i].identificador = stoi(estacion);
            }
        }

    }
    return true;


}


/*
 * Pre:  La cadena «nombreFicheroUsos» representa la ruta de acceso y el nombre de un
 *       fichero de texto con el formato de usos del sistema Bizi establecido en el enunciado.
 *       El vector «estaciones» tiene «NUM_ESTACIONES» componentes que almacenan información
 *       sobre estaciones Bizi de forma tal que en cada componente «i» se almacena la
 *       información de la estación de identificador «i» + 1 (es decir, en estaciones[0] se
 *       encuentra almacenada la información de la estación con identificador 1, en
 *       estaciones[1] se encuentra almacenada la estación con identificador 2 y así
 *       sucesivamente). La información sobre el número de usos de cada estación es 0 en todas
 *       ellas.
 * Post: Si no hay problemas de lectura del fichero «nombreFicheroUsos», la función devuelve
 *       «true» y actualiza el número de usos de cada estación del vector «estaciones» de
 *       acuerdo con el contenido del fichero «nombreFicheroUsos», contabilizando como un uso
 *       tanto la retirada como la devolución de bicicletas. En caso contrario, se limita a
 *       devolver «false».
 */
bool contarUsosEstaciones(const string nombreFicheroUsos, Estacion estaciones[]) {

}


/*
 * Pre:  El vector «estaciones» tiene «NUM_ESTACIONES» componentes.
 * Post: El contenido del vector «estaciones» es una permutación del contenido inicial del
 *       mismo que está ahora ordenado de mayor a menor número de usos de las estaciones.
 */
void ordenarPorUso(Estacion estaciones[]) {
    // Utilizamos un algoritmo de ordenación por selección para ordenar el vector
    // de estaciones por número de usos
    for (int i = 0; i < NUM_ESTACIONES - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < NUM_ESTACIONES; j++) {
            if (estaciones[j].numeroUsos > estaciones[minIdx].numeroUsos) {
            minIdx = j;
            }
        }
    // Intercambiamos las estaciones en las posiciones i y minIdx
    Estacion temp = estaciones[i];
    estaciones[i] = estaciones[minIdx];
    estaciones[minIdx] = temp;
    }
}


/*
 * Pre:  ---
 * Post: Si la función puede crear un fichero de texto cuyo nombre es el contenido de la cadena
 *       de caracteres «nombreFichero», la función devuelve «true» y escribe en el fichero
 *       creado la siguiente información sobre cada estación almacenada en el vector
 *       «estaciones»: puesto, número de usos, identificador de la estación y
 *       nombre, con un formato similar al siguiente:
 *
 *           Puesto    Usos  Id Nombre
 *           ------ ------- --- --------------------------------------------------
 *                1   47064  16 Plaza España
 *                2   42306  67 Avda. G. Gómez de Avellaneda - C/ Clara Campoamor
 *                3   40251  47 Plaza San Francisco - Universidad
 *           ...
 */
bool escribirInformeEstaciones(const string nombreFichero, const Estacion estaciones[]);


/*
 * Pre:  La cadena «nombreFicheroUsos» representa la ruta de acceso y el nombre de un
 *       fichero de texto con el formato de usos del sistema Bizi establecido en el enunciado.
 *       La matriz «viajes» tiene «NUM_ESTACIONES» filas de «NUM_ESTACIONES» columnas cada una.
 * Post: Si no hay problemas de lectura del fichero «nombreFicheroUsos», la función devuelve
 *       «true» y asigna a cada componente de la matriz «viajes» valores de forma que la
 *       componente viajes[i][j] contiene el número de viajes que en dicho fichero aparece un
 *       uso que tiene como origen la estación de código «i» + 1 y como destino la estación de
 *       código «j» + 1. En caso contrario, se limita a devolver «false».
 */
bool contarViajesOrigenDestino(const string nombreFicheroUsos, 
                               unsigned viajes[][NUM_ESTACIONES]);


/*
 * Pre:  La matriz «viajes» tiene «NUM_ESTACIONES» filas de «NUM_ESTACIONES» columnas cada una.
 *       Cada componente viajes[i][j] contiene un valor que representa el número de usos
 *       que tienen como origen la estación de código «i» + 1 y como destino la estación de
 *       código «j» + 1. El vector «destinosMasFrecuentes» tiene «NUM_ESTACIONES» componentes.
 * Post: Asigna a cada componente destinosMasFrecuentes[i] el índice j de la fila viajes[i] de
 *       valor máximo. Es decir, asigna a destinosMasFrecuentes[0] el índice de la columna
 *       donde se encuentra el mayor valor de entre viajes[0][0], viajes[0][1], ... y 
 *       viajes[0][NUM_ESTACIONES-1]; asigna a destinosMasFrecuentes[1] el índice de la columna
 *       donde se encuentra el mayor valor de entre viajes[1][0], viajes[1][1], ... y 
 *       viajes[1][NUM_ESTACIONES-1] y así sucesivamente.
 */
void calcularDestinosMasFrecuentes(const unsigned viajes[][NUM_ESTACIONES],
                                   unsigned destinosMasFrecuentes[]);

/*
 * Pre:  El flujo de escritura «f» ya está asociado con un dispositivo (ya sea fichero o
 *       pantalla) y se puede escribir en él. La matriz «viajes» tiene «NUM_ESTACIONES» filas
 *       de «NUM_ESTACIONES» columnas cada una. Cada componente viajes[i][j] contiene un valor
 *       que representa el número de usos que tienen como origen la estación de código «i» + 1
 *       y como destino la estación de código «j» + 1. El vector «destinosMasFrecuentes» tiene
 *       «NUM_ESTACIONES» componentes, donde cada componente destinosMasFrecuentes[i] el índice
 *       j de la fila viajes[i] de valor máximo.
 * Post: Escribe en el flujo f un informe donde se muestra, para cada estación del sistema, la
 *       estación que mayor número de viajes es destino de los viajes que parten de la primera.
 *       El informe está ordenado por identificadores crecientes de estación de origen y tiene
 *       el formato establecido en el enunciado.
 */
void escribirInformeDestinos(ostream& f, const unsigned viajes[][NUM_ESTACIONES], 
                             const unsigned destinosMasFrecuentes[]);
