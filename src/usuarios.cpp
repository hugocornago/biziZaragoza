/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: 10-01-2023
 * Resumen: Fichero de interfaz «usuarios.hpp» de un módulo para trabajar con el fichero de 
 *          usuarios del sistema Bizi Zaragoza.
\*********************************************************************************************/

#include "usuarios.hpp" 
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

/*
 * Pre: <fichero> debe ser un flujo abierto que siga la sintaxis de un fichero usuarios (sin cabezera)
 * Post: Devuelve true is ha podido una linea del flujo y guarda en <usuario> los datos del siguiente
 *       usuario en el flujo.
 */
bool leerUsuario(istream& fichero, Usuario& usuario) {
    string IDUsuario;
    if (getline(fichero, IDUsuario, DELIMITADOR_USUARIOS)) {
        string genero;
        getline(fichero, genero, DELIMITADOR_USUARIOS);
        string rangoEdad;
        getline(fichero, rangoEdad);

        usuario.identificador = stoi(IDUsuario);
        usuario.genero = genero;
        usuario.rangoEdad = rangoEdad;
        return true;
    }

    return false;
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
    Usuario usuario;
    while (leerUsuario(fichero, usuario)) {
        auto indice_edad = indiceRangoEdad(usuario.rangoEdad);
        auto indice_genero = indiceGenero(usuario.genero);

        /* Si tiene un genero especificado, contabilizarlo en la estadistica */
        if (indice_genero != -1) {
            estadisticas[indice_edad][indice_genero]++;
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
    for (unsigned i = 0; i < NUM_EDADES; i++) {
        if (rangoEdad == RANGO_EDADES[i]) {
            return i;
        }
    }
    return 0;
}    

/*
 * Pre: ---
 * Post: Devuelve el numero de usuarios en el fichero <nombreFicheroUsuarios>.
 */
unsigned obtenerNumeroDeUsuarios(const string& nombreFicheroUsuarios) {
    ifstream fichero {nombreFicheroUsuarios};

    /* ignorar la cabezera */
    string linea;
    getline(fichero, linea);

    unsigned numeroDeUsuarios {0};

    Usuario usuario;
    while (leerUsuario(fichero, usuario)) {
        numeroDeUsuarios++;
    }

    return numeroDeUsuarios;
}
/*
 * Pre:  ---
 * Post: Si el valor del parámetro «genero» es uno de los valores válidos según la regla 
 *       <género> establecida en el enunciado ("M" o "F"), devuelve, respectivamente, 0 o 1.
 *       En caso contrario, devuelve -1.
 */
int indiceGenero(const string genero) {
    if (genero.empty()) return -1;
    switch (genero.at(0)) {
    case 'M': return 0;
    case 'F': return 1;
    default:  return -1;
    }
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
        getline(ficheroUsuarios, linea); // ignorar la cabezera

        Usuario usuario;
        while (leerUsuario(ficheroUsuarios, usuario)) {
            if (usuario.identificador == idUsuario) {
                genero = usuario.genero;
                rangoEdad = usuario.rangoEdad;

                ficheroUsuarios.close();
                return true;
            } else if (usuario.identificador > idUsuario) {
                /* Como los usuarios del fichero <nombreFicheroUsuarios> estan en
                   orden creciente, podemos concluir que no existe el usuario. */ 
                ficheroUsuarios.close();
                return false;
            }
        }
    }

    return false;
}
