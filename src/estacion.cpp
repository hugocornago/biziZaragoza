/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de interfaz «estacion.hpp» de un módulo para trabajar con
 *          registros que representan estaciones del sistema Bizi Zaragoza.
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\*********************************************************************************************/

#include "estacion.hpp"
#include "nombres-ficheros.hpp"
#include "uso.hpp"
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;


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
    const char DELIMITADOR = ';';
    const char BARRA = '/';
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
        unsigned identificador;
        for (unsigned n = 0; n<=NUM_BARRAS; n++){
            string url;

            if(n<7){
                getline(fichero, url, BARRA);
            }
            else{
                getline(fichero, url, DELIMITADOR);
                identificador = stoi(url);
            }
        }

        auto& estacion = estaciones[identificador-1];
        estacion.identificador = identificador;

        /* Lectura del nombre */
        string componente;
        getline(fichero, componente, DELIMITADOR); // ignorar el componente "about"

        getline(fichero, componente, DELIMITADOR); // componente "title"
        // guardar todo menos la primera y ultima "
        estacion.nombre = componente.substr(1, componente.size()-2); 

        getline(fichero, componente); // Obtener el resto de la linea.
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
    ifstream fichero {nombreFicheroUsos};
    if (fichero.is_open()) {
        string linea;
        
        // ignorar la cabezera
        getline(fichero, linea);

        UsoBizi uso;
        while (leerUso(fichero, uso)) {
            /* 
             * Por alguna razon, hay usos en el fichero Usos que contienen estaciones inexistentes.
             * Para remediar eso, simplemente nos saltamos el uso si no existe la estacion.
             */
            if (uso.estacionRetira <= NUM_ESTACIONES) {
                estaciones[uso.estacionRetira-1].numeroUsos++;
            }
            if (uso.estacionDevuelve <= NUM_ESTACIONES) {
                estaciones[uso.estacionDevuelve-1].numeroUsos++;
            }
        }
        
        fichero.close();
        return true;
    }
    return false;
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
bool escribirInformeEstaciones(const string nombreFichero, const Estacion estaciones[])
{
    ofstream fichero {nombreFichero};
    if (fichero.is_open()) {
        /* Cabezera */
        fichero << right << setw(6) << "Puesto"
                << right << setw(8) << "Usos"
                << right << setw(4) << "Id" << " "
                << left << setw(50) << "Nombre"
                << endl;
        fichero << "------ ------- --- --------------------------------------------------"
                << endl;

        for (int i = 0; i < NUM_ESTACIONES; ++i) {
            auto& estacion = estaciones[i];
            fichero << right << setw(6) << i+1
                    << right << setw(8) << estacion.numeroUsos
                    << right << setw(4) << estacion.identificador << " "
                    << left << setw(50) << estacion.nombre
                    << endl;
        }
        fichero.close();
        return true;
    }
    return false;
}


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
                               unsigned viajes[][NUM_ESTACIONES])
{
    ifstream fichero {nombreFicheroUsos};
    if (fichero.is_open()) {
        /* ignorar cabezera */
        string ignorar;
        getline(fichero, ignorar);

        UsoBizi uso;
        while (leerUso(fichero, uso)) {
            if (uso.estacionRetira > NUM_ESTACIONES || uso.estacionDevuelve > NUM_ESTACIONES) {
                /* 
                 * Por alguna razon, hay usos en el fichero Usos que contienen estaciones inexistentes.
                 * Para remediar eso, simplemente nos saltamos el uso si no existe la estacion.
                 */
                continue;
            }
            viajes[uso.estacionRetira-1][uso.estacionDevuelve-1]++;
        }

        return true;
    }

    return false;
}


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
                                   unsigned destinosMasFrecuentes[])
{
    for (unsigned i = 0; i < NUM_ESTACIONES; ++i) {
        auto& destino = destinosMasFrecuentes[i];

        unsigned mayor {0};
        for (unsigned j = 0; j < NUM_ESTACIONES; ++j) {
            const auto& viaje = viajes[i][j];
            if (viaje > mayor) {
                mayor = viaje;
                destino = j;
            }
        }

    }
}

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
                             const unsigned destinosMasFrecuentes[])
{
    /* cabezera */
    f << "Viajes  Origen --> Destino" << endl;
    f << "----------------------------------------------------"
      << "----------------------------------------------------" << endl;

    Estacion estaciones[NUM_ESTACIONES];
    leerEstaciones(FICHERO_ESTACIONES, estaciones);

    for (unsigned i = 0; i < NUM_ESTACIONES; ++i) {
        const auto& estacion = estaciones[i];
        const auto& destinoMasFrecuente = destinosMasFrecuentes[i];
        const auto& numViajes = viajes[i][destinoMasFrecuente];
        const auto& estacionDestinoMasFrecuente = estaciones[destinoMasFrecuente];

        f << " " << left << setw(6) << numViajes << " "
          << i+1 << "-" << estacion.nombre << "  -->  "
          << estacionDestinoMasFrecuente.identificador << "-" 
          << estacionDestinoMasFrecuente.nombre
          << endl;
    }
}
