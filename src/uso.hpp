﻿/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Hugo Cornago y Jaime Alonso
 * Ultima revisión: 10-01-2023
 * Resumen: Fichero de interfaz «usos.hpp» de un módulo para trabajar con
 *          registros que representan usos del sistema Bizi Zaragoza.
\*********************************************************************************************/

#pragma once

#include <istream>
#include <vector>
using namespace std;

struct UsoBizi {
    int identificador;
    int estacionRetira;
    int estacionDevuelve;
};

/*
 * Pre:  El flujo «f» está asociado con un fichero de texto con el formato de usos del sistema
 *       Bizi establecido en el enunciado y en disposición de leer desde el principio de una
 *       línea distinta a la de la cabecera.
 * Post: Intenta leer la línea mencionada en la precondición y, si esta línea existe, almacena
 *       en los campos del parámetro «uso» el identificador del usuario al que corresponde el
 *       uso Bizi de la línea leída y los códigos de las estaciones de retirada y devolución de
 *       la bicicleta. Devuelve «true» si no se han terminado los datos del fichero en el
 *       intento de lectura descrito y y «false» en caso contrario.
 */
bool leerUso(istream& fichero, UsoBizi& uso);


/*
 * Pre:  La cadena de caracteres «nombreFicheroUsos» representa la ruta de acceso y el nombre
 *       de un fichero de texto con el formato de usos del sistema Bizi establecido en el
 *       enunciado.
 * Post: Si el fichero de nombre «nombreFicheroUsos» se puede abrir y leer correctamente,
 *       «traslados» es el número de usos entre estaciones distintas del sistema Bizi Zaragoza
 *       contenidos en el fichero de nombre «nombreFicheroUsos» y «usosCirculares» es el número
 *       de usos contenidos en dicho fichero que tienen como origen y destino la misma 
 *      estación.  En ese caso, devuelve «true» y en el caso contrario, «false».
 */
bool contarUsos(const string nombreFicheroUsos, unsigned& traslados, unsigned& usosCirculares);

/* Pre: ---
 * Post: Imprime en pantalla información sobre los usos del fichero
 *       selecionado por el usuario.
 */
void pantallaUsos(const string nombreFichero, const unsigned long numeroUsosTraslado,
                  const unsigned long numeroUsosCirculares, const unsigned long numeroTotalUsos);
