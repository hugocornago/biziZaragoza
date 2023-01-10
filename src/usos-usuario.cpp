/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Hugo Cornago y Jaime Alonso
 * Ultima revisión: 10-01-2023
 * Resumen: Fichero de interfaz «usos-usuario.hpp» de un módulo para trabajar con registros que
 *          permiten contabilizar el número de usos que cada usuario hace del sistema Bizi.
\*********************************************************************************************/

#include "usos-usuario.hpp"
#include "uso.hpp"
#include <fstream>
#include <functional>
#include <ios>
#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <unordered_set>
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

        /* 
         * Dado el gran numero de usuarios existentes en el servicio de BiziZaragoza,
         * hemos optado por usar un hashset que contenga los usuarios que aparecen en el ficheroUsos.
         * Para ello, usamos de hash el identificador hashedo.
         * Y comprobamos que dos usuarios sean iguales, si tienen el mismo identificador.
         * 
         * Esta solución aporta una gran mejora de velocidad al programa (3 veces más rapido)
         * a cambio de un poco de complejidad.
         */
        auto hash = [](const UsosUsuario& usuario) { return std::hash<unsigned>()(usuario.identificador); };
        auto equal = [](const UsosUsuario& usuario1, const UsosUsuario& usuario2) {
            return usuario1.identificador == usuario2.identificador;
        };
        unordered_set<UsosUsuario, decltype(hash), decltype(equal)> usuariosSet(1, hash, equal);

        UsoBizi uso;
        while (leerUso(ficheroUsos, uso)) {
            UsosUsuario usuario;
            usuario.identificador = uso.identificador;
            
            /* Las siguientes lineas comprueban si el usuario ya existe en el hashset,
             * y si es asi, utilizamos el usuario del set en vez del que acabamos de crear */
            auto aux = usuariosSet.find(usuario);
            bool usuarioExiste = aux != usuariosSet.end();
            if (usuarioExiste) {
                usuario = *aux;
                usuariosSet.erase(*aux);
            }

            if (uso.estacionRetira == uso.estacionDevuelve) {
                usuario.usosCirculares++;
            }
            else {
                usuario.usosTransporte++;
            }
            
            usuariosSet.insert(usuario);
        }

        numUsuarios = usuariosSet.size();

        unsigned i = 0;
        for (auto& usuario : usuariosSet) {
            usuarios[i++] = usuario;
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
