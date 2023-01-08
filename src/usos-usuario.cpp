/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de interfaz «usos-usuario.hpp» de un módulo para trabajar con registros que
 *          permiten contabilizar el número de usos que cada usuario hace del sistema Bizi.
\*********************************************************************************************/

#include "usos-usuario.hpp"
#include "uso.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

/*
 * Pre:  ---
 * Post: Devuelve el número total de usos del sistema Bizi correspondiente a «usuario».
 */
unsigned numUsosTotales(const UsosUsuario usuario)
{
    return usuario.usosCirculares + usuario.usosTransporte;
}


/*
 * Pre:  «nombreFicheroUsos» contiene la ruta y nombre de un fichero de texto con información
 *       sobre usos del sistema Bizi Zaragoza y con el formato establecido en el enunciado.
 *       El vector «usuarios» tiene al menos tantas componentes como número de usuarios
 *       distintos aparecen  en el fichero de nombre «nombreFicheroUsos». El valor del
 *       parámetro «numUsuarios» no está definido.
 * Post: Si se puede leer del fichero «nombreFicheroUsos», el vector «usuarios» almacena, en
 *       sus primeras «numUsuarios» componentes, la información relativa a identificadores de
 *       usuario y número de usos (entre estaciones distintas y entre la misma estación)
 *       extraída del fichero «nombreFicheroUsos» de acuerdo con las consideraciones
 *       establecidas en el enunciado. No es necesario que los registros del vector estén
 *       ordenados por ningún criterio en concreto. Devuelve «true» si el fichero puede ser
 *       leído sin problemas y «false» en caso contrario.
 */
bool obtenerUsosPorUsuario(const string nombreFicheroUsos,
                           UsosUsuario usuarios[], unsigned& numUsuarios)
{
    ifstream ficheroUsos {nombreFicheroUsos};
    if (ficheroUsos.is_open()) {
        string linea;

        // ignorar cabezera
        getline(ficheroUsos, linea); 

        // empezamos con 0 usuarios
        numUsuarios = 0;

        UsoBizi uso;
        while (leerUso(ficheroUsos, uso)) {
            for (unsigned i = 0; i < numUsuarios+1; ++i) {
                cout << i << endl;
                auto& usuario = usuarios[i];
                if (usuario.identificador == -1) {
                    /* Si aun no hay un usuario definido en esta posición, lo añadimos */
                    usuario.identificador = uso.identificador;
                    numUsuarios++;
                }

                if (uso.identificador == usuario.identificador) {
                    if (uso.estacionRetira == uso.estacionDevuelve) {
                        usuario.usosCirculares++;
                    }
                    else {
                        usuario.usosTransporte++;
                    }
                    break;
                }
            }
        }

        ficheroUsos.close();
        return true;
    }
    return false;
}

/*
 * Pre:  numUsuarios > 0; numOrdenar > 0
 * Post: El vector usuarios[0..numUsuarios-1] es una permutación de los datos iniciales del
 *       vector, de forma que los «numOrdenar» primeros son los usuarios de mayor número de
 *       usos y están ordenados por número de usos decreciente.
 */
void ordenar(UsosUsuario usuarios[], const unsigned numUsuarios, 
             const unsigned numOrdenar)
{
    
    /* crear una copia de usuarios */
    UsosUsuario usuariosCopia[numUsuarios];
    for (unsigned i = 0; i < numUsuarios; ++i) {
        usuariosCopia[i] = usuarios[i];
    }

    for (unsigned i = 0; i < numOrdenar; ++i) {
        unsigned mayorPosicion = 0;
        unsigned mayorTransportes = 0;
        for (unsigned j = 0; j < numUsuarios; ++j) {
            auto& usuario = usuariosCopia[j];
            const auto& usosTotales = numUsosTotales(usuario);
            if (usosTotales > mayorTransportes) {
                mayorTransportes = usosTotales;
                mayorPosicion = j;
            }
        }

        /* asegurarnos de hacer una copia del usuario */
        auto mayorUsuario = usuariosCopia[mayorPosicion];
        /* guardarla en una nueva array */
        usuarios[i] = mayorUsuario;

        /* eliminar el usuario con la mayor posicion de usuarios */
        usuariosCopia[mayorPosicion].usosTransporte = 0;
        usuariosCopia[mayorPosicion].usosCirculares = 0;
    }
}
