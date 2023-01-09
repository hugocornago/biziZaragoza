/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de implementación del módulo principal que implementa el trabajo
 *          obligatorio de Programación 1 del curso 2022-23.
\*********************************************************************************************/
#include "estacion.hpp"
#include "usuarios.hpp"
#include "usos-usuario.hpp"
#include "nombres-ficheros.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "uso.hpp"
using namespace std;

const string NOMBRE_FICHERO_USUARIOS {"datos/usuarios.csv"};

/* Pre: ---
 * Post: Imprime al usuario una lista de los posibles fichero que 
 *       estan disponibles para el programa y pregunta cual quiere elegir.
 *       La función devuelve una string con la ruta relativa correspondiente al fichero.
 */
string selectorDeFichero() {
    cout << "Elección de ficheros de usos y usuarios. Opciones disponibles: " << endl;
    cout << "16: octubre 2016 a marzo 2017" << endl;
    cout << "17: marzo 2017 a agosto 2017" << endl;
    cout << "t1: datos para pruebas (10 líneas)" << endl;
    cout << "t2: datos para pruebas (2000 líneas)" << endl;
    cout << "Introduzca una opción: ";

    string opcion;
    // getline(cin, opcion);
    cin >> opcion;

    /* Ruta relavtiva */
    string ruta_fichero = "datos/usos-" + opcion + ".csv";

    return ruta_fichero;
}

/* Pre: ---
 * Post: Cambia el fichero <fichero> dependiendo de la salida
 *       de la función selectorDeFichero().
 *       La función modifica la componente <nombre> y <f> del parametro <fichero>.
 */
bool ordenFichero(string& nombreFichero) {
    const auto& nombre_fichero = selectorDeFichero();

    ifstream fichero_abierto {nombre_fichero};
    if (!fichero_abierto.is_open()) {
        cerr << "No se ha podido leer el fichero \"" << nombre_fichero << "\"" << endl;
        return false;
    }

    nombreFichero = nombre_fichero;
    cout << "El fichero \"" << nombreFichero << "\" existe y ha sido seleccionado." << endl;
    return true;
}

/* Pre: ---
 * Post: Imprime en pantalla la estadistica de los usuarios.
 */
void imprimirEstadisticas(unsigned estadistica[][NUM_GENEROS]) 
{
    /* cabezera */
    cout << "Distribución de los usuarios" << endl
         << setw(7) << "|" << setw(6) << "M" << setw(7) << "F" << endl
         << "------+----------------" << endl;
    for (unsigned i = 0; i < NUM_EDADES; ++i) {
        cout << left << setw(6) << RANGO_EDADES[i] << "|"
             << right << setw(7) << estadistica[i][0]
             << right << setw(7) << estadistica[i][1]
             << endl;
    }
}

/* Pre: ---
 * Post: Imprime en pantalla usuarios y sus usos.
 */
void imprimirUsuarios(UsosUsuario usuarios[], const unsigned numUsuarios) 
{
    cout << "Número usuarios distintos: " << numUsuarios << endl << endl;

    /* cabezera */
    cout << right << setw(10) << "Usuario "
         << right << setw(9) << "Traslados "
         << right << setw(10) << "Circular "
         << right << setw(9) << "Total" << endl;
    cout << "========= ========= ========= =========" << endl;

    for (unsigned i = 0; i < numUsuarios; ++i) {
        const auto& usuario = usuarios[i];
        cout << right << setw(9) << usuario.identificador
             << right << setw(10) << usuario.usosTransporte
             << right << setw(10) << usuario.usosCirculares
             << right << setw(10) << numUsosTotales(usuario)
             << endl;
    }
}
/* Pre: <fichero> debe estar incializado y su componente <f> debe apuntar a un
 *      fichero abierto con permisos de lectura.
 * Post: Devuelve "true" si ha podido obtener el numero de usos
 *       En cualquier otro caso, devuelve "false".
 */
bool ordenUsos(const string& nombreFichero) {
    unsigned int usosTransporte, usosCirculares, usosTotales;
    if (!contarUsos(nombreFichero, usosTransporte, usosCirculares)) return false;

    usosTotales = usosCirculares + usosTransporte;
    pantallaUsos(nombreFichero, usosTransporte, usosCirculares, usosTotales);
    return true;
}

/* Pre: ---
 * Post: Ejecuta la orden "ESTADISTICAS".
 */
bool ordenEstadisticas(const string& nombreFichero)
{
    /* Inicializar estadisticas a 0 */
    unsigned estadisticas[NUM_EDADES][NUM_GENEROS] = {};
    if (!obtenerEstadisticas(NOMBRE_FICHERO_USUARIOS, estadisticas)) return false;
    imprimirEstadisticas(estadisticas);
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "USUARIO".
 */
bool ordenUsuario(const string& nombreFichero, const string& usuarioABuscar) {
    string genero, rangoEdad;
    unsigned IDUsuario = stoi(usuarioABuscar);
    if (buscarUsuario(NOMBRE_FICHERO_USUARIOS, IDUsuario, genero, rangoEdad)) {
        if (genero == "M") {
            cout << "El usuario " << IDUsuario << " está en el rango de edad \""
                 << rangoEdad << "\"." << endl;
        } else if (genero == "F") {
            cout << "La usuaria " << IDUsuario << " está en el rango de edad \""
                 << rangoEdad << "\"." << endl;
        } else {
            cout << "El/la usuario/a " << IDUsuario << " está en el rango de edad \""
                 << rangoEdad << "\"." << endl;
        }
    } else {
        cout << "El/la usuario/a " << IDUsuario << " no aparece en el fichero \""
             << NOMBRE_FICHERO_USUARIOS << "\"." << endl;
    }
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "MAYORES".
 */
bool ordenMayores(const string& nombreFichero, std::string args) {
    unsigned numeroDeUsuariosAMostrar = stoi(args);
    unsigned numUsuariosMAX = obtenerNumeroDeUsuarios(NOMBRE_FICHERO_USUARIOS);
    UsosUsuario usuarios[numUsuariosMAX];

    unsigned numUsuarios;
    obtenerUsosPorUsuario(nombreFichero, usuarios, numUsuarios);
    if (numeroDeUsuariosAMostrar > numUsuarios) {
        numeroDeUsuariosAMostrar = numUsuarios;
    }
    ordenar(usuarios, numUsuarios, numeroDeUsuariosAMostrar);
    imprimirUsuarios(usuarios, numeroDeUsuariosAMostrar);
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "INFORME".
 */
bool ordenInforme(const string& nombreFichero, std::string nombreFicheroAEscribir) {
    Estacion estaciones[NUM_ESTACIONES];
    if (!leerEstaciones(FICHERO_ESTACIONES, estaciones)) {
        cerr << "No se ha podido leer las estaciones de \"" << FICHERO_ESTACIONES
             << "\"." << endl; 
        return false;
    };
    if (!contarUsosEstaciones(nombreFichero, estaciones)) {
        cerr << "No se ha podido leer los usos del fichero \"" << nombreFichero
             << "\"." << endl; 
        return false;
    };

    ordenarPorUso(estaciones);

    if (!escribirInformeEstaciones(nombreFicheroAEscribir, estaciones)) {
        cerr << "No se ha podido escribir el informe en la ruta \"" << nombreFicheroAEscribir
             << "\"." << endl; 
        return false;
    };
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "DESTINOS".
 */
bool ordenDestinos(const string& nombreFichero, std::string args) {
    throw logic_error("Función aun no implementada!");
}

/* Pre: ---
 * Post: Imprime en pantalla las posibles ordenes que estan
 *       implementadas y puede usar el usuario.
 */
void imprimirOrdenesDisponibles () {
    cout << "ÓRDENES DISPONIBLES" << endl;
    cout << "===================" << endl;
    cout << "AYUDA: " << setw(9) << "Muestra esta pantalla de ayuda." << endl;
    cout << "FICHERO: Permite modificar la selección del fichero de usos a utilizar." << endl;
    cout << "USOS: " << setw(9) << "Escribe en la pantalla el número de usos de traslado y circulares." << endl;
    cout << "ESTADISTICAS: " << setw(9) << "Informa la distribución por edades y géneros de los usuarios." << endl;
    cout << "USUARIO <id-usuario>: Informa acerca del número de usos realizados por el"
         << "usuario especificado." << endl;
    cout << "MAYORES <n>: " << setw(9) << "Escribe en la pantalla el número de usuarios distintos y los"
         << "<n> usuarios que más usos han hecho del sistema." << endl;
    cout << "INFORME <nombre-fichero>: Escribe en el fichero especificado un informe con el" << endl;
    cout << "número de usos de las estaciones, según el fichero seleccionado." << endl;
    cout << "DESTINOS: <nombre-fichero>: " << setw(9) << "Escribe en el fichero especificado un informe en"
         << "el que, para cada estación dada, se indica la estación a la que más."
         << "se ha viajado desde ella." << endl;
    cout << "FIN: " << setw(9) << "Termina la ejecución de este programa." << endl;
}

/* Pre: ---
 * Post: 
 *       Devuelve "true" si el usuario a dado la orden "FIN".
 *       Devuelve "false" en cualquier otro caso.
 */
bool ejecutarOrden(const string& orden, string& nombreFichero) {
    if (orden == "AYUDA") {
        imprimirOrdenesDisponibles();
    } else if (orden == "FICHERO") {
        while (!ordenFichero(nombreFichero));
    } else if (orden == "USOS") {
        ordenUsos(nombreFichero);
    } else if (orden == "ESTADISTICAS") {
        if(!ordenEstadisticas(nombreFichero)) {
            cerr << "ERROR";
        };
    } else if (orden == "USUARIO") {
        string usuario;
        cin >> usuario;
        ordenUsuario(nombreFichero, usuario);
    } else if (orden == "MAYORES") {
        string args;
        cin >> args;
        ordenMayores(nombreFichero, args);
    } else if (orden == "INFORME") {
        string args;
        cin >> args;
        ordenInforme(nombreFichero, args);
    } else if (orden == "DESTINOS") {
        string args;
        cin >> args;
        ordenDestinos(nombreFichero, args);
    } else if (orden == "FIN") {
        return true;
    } else {
        /* No existe la orden que el usuario a solicitado */
        cerr << "Orden \"" << orden << "\" desconocida." << endl;
    }

    return false;
}

/* Pre: ---
 * Post: Función intermedia que se encarga de pedir al usuario una orden,
 *       almacenarla en una variable, convertir cada caracter en su mayuscula correspondiente
 *       y llamar a la función ejectuarOrden con esa orden y el <fichero> proporcionado.
 *       Devuelve la salida de la función ejectuarOrden.
 */
bool elejirOrden(string& nombreFichero) {
    cout << endl;
    cout << "Orden: ";
    string orden;
    // getline(cin, orden);
    cin >> orden;

    /* Con el fin de optimizar el programa, hemos optado por la funcion std::transform
     * que ejecuta una instruccion en cada caracter de la string order.
     */
    transform(orden.begin(), orden.end(), orden.begin(),
        /* Esta función lambda hace uso de std::toupper, aunque como tiene muchos overloads,
         * dejamos que el compilador elija el mejor de ellos. */
        [](unsigned char c){ return toupper(c); });

    return ejecutarOrden(orden, nombreFichero);
}


int main(){
    string nombreFichero;

    while (!ordenFichero(nombreFichero)) {
        cout << endl;
    };
    cout << endl;

    imprimirOrdenesDisponibles();
    while (!elejirOrden(nombreFichero));

    std::cout << "Adios!" << std::endl;
    return 0;
}
