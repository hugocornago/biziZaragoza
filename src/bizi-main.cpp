/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: 10-01-2023
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
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "uso.hpp"
using namespace std;


/* 
 * Pre: ---
 * Post: Imprime en pantalla el fichero en la ruta <ruta>
 */
void imprimirFichero(const string& ruta)
{
    ifstream fichero {ruta};
    string linea;
    while (getline(fichero, linea)) {
        cout << linea << endl;
    }
}
/* Pre: ---
 * Post: Imprime al usuario una lista de los posibles fichero que 
 *       estan disponibles para el programa y pregunta cual quiere elegir.
 *       La función devuelve una string con la ruta relativa correspondiente al fichero.
 */
string selectorDeFichero() {
    cout << "Elección de ficheros de usos y usuarios. Opciones disponibles: " << endl;
    imprimirFichero(FICHERO_OPCIONES);
    cout << "Introduzca una opción: ";

    string opcion;
    cin >> opcion;

    /* Ruta relativa */
    string rutaFichero = construirNombreFicheroUsos(opcion);
    return rutaFichero;
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
        cerr << "No se ha podido leer el fichero \"" << nombre_fichero << "\"" << endl << endl;
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
void imprimirUsuarios(UsosUsuario usuarios[], const unsigned numUsuariosAMostrar,
                      const unsigned numUsuariosTotal)
{
    cout << "Número usuarios distintos: " << numUsuariosTotal << endl << endl;

    /* cabezera */
    cout << right << setw(10) << "Usuario "
         << right << setw(9) << "Traslados "
         << right << setw(10) << "Circular "
         << right << setw(9) << "Total" << endl;
    cout << "========= ========= ========= =========" << endl;

    for (unsigned i = 0; i < numUsuariosAMostrar; ++i) {
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
bool ordenEstadisticas()
{
    /* Inicializar estadisticas a 0 */
    unsigned estadisticas[NUM_EDADES][NUM_GENEROS] = {};
    if (!obtenerEstadisticas(FICHERO_USUARIOS, estadisticas)) return false;
    imprimirEstadisticas(estadisticas);
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "USUARIO".
 */
bool ordenUsuario(const string& usuarioABuscar) {
    string genero, rangoEdad;
    unsigned IDUsuario = stoi(usuarioABuscar);
    if (buscarUsuario(FICHERO_USUARIOS, IDUsuario, genero, rangoEdad)) {
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
             << FICHERO_USUARIOS << "\"." << endl;
    }
    return true;
}
/* Pre: ---
 * Post: Ejecuta la orden "MAYORES".
 */
bool ordenMayores(const string& nombreFichero, std::string args) {
    unsigned numeroDeUsuariosAMostrar = stoi(args);
    unsigned numUsuariosMAX = obtenerNumeroDeUsuarios(FICHERO_USUARIOS);
    if (numUsuariosMAX == 0) {
        cerr << "No se ha podido leer el fichero usuarios \"" << FICHERO_USUARIOS << "\". (o no existen usuarios en el mismo)"
             << endl;
        return false;
    }
    UsosUsuario usuarios[numUsuariosMAX];

    unsigned numUsuarios;
    if (!obtenerUsosPorUsuario(nombreFichero, usuarios, numUsuarios)) {
        cerr << "No se ha podido leer el fichero de ordenes \"" << nombreFichero << "\"." << endl;
        return false;
    };

    if (numeroDeUsuariosAMostrar > numUsuarios) {
        numeroDeUsuariosAMostrar = numUsuarios;
    }
    ordenar(usuarios, numUsuarios, numeroDeUsuariosAMostrar);
    imprimirUsuarios(usuarios, numeroDeUsuariosAMostrar, numUsuarios);
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
    cout << "Informe \"" << nombreFicheroAEscribir << "\" creado correctamente." << endl;
    return true;
}

/* Pre: ---
 * Post: Ejecuta la orden "DESTINOS".
 */
bool ordenDestinos(const string& nombreFichero, const string& nombreFicheroAEscribir) {
    ostream* flujo;
    bool escribirEnPantalla = nombreFicheroAEscribir.empty();
    
    if (escribirEnPantalla) {
        /* Escribirlo en pantalla */
        flujo = &cout;
    } else {
        /* Escribrilo en un fichero */
        flujo = new ofstream(nombreFicheroAEscribir);
        if (flujo->bad()) {
            cerr << "No se ha podido escribir en el fichero \"" << nombreFicheroAEscribir
                 << "\"." << endl; 
            return false;
        }
    }

    unsigned viajes[NUM_ESTACIONES][NUM_ESTACIONES] = {};
    if (!contarViajesOrigenDestino(nombreFichero, viajes)) {
        cerr << "No se ha podido leer el fichero \"" << nombreFichero
             << "\"." << endl; 
        return false;
    }

    unsigned destinosMasFrecuentes[NUM_ESTACIONES] = {};
    calcularDestinosMasFrecuentes(viajes, destinosMasFrecuentes);

    escribirInformeDestinos(*flujo, viajes, destinosMasFrecuentes);

    if (!escribirEnPantalla) {
        cout << "Informe \"" << nombreFicheroAEscribir << "\" creado correctamente." << endl;
    }
    return true;
}

/* Pre: ---
 * Post: 
 *       Devuelve "true" si el usuario a dado la orden "FIN".
 *       Devuelve "false" en cualquier otro caso.
 */
bool ejecutarOrden(const string& orden, string& nombreFichero) {
    if (orden == "AYUDA") {
        cout << endl;
        imprimirFichero(FICHERO_AYUDA);
    } else if (orden == "FICHERO") {
        /* mientras que no se haya podido leer correctamente un fichero
         * repetir la ordenFichero */
        while (!ordenFichero(nombreFichero));
    } else if (orden == "USOS") {
        ordenUsos(nombreFichero);
    } else if (orden == "ESTADISTICAS") {
        if(!ordenEstadisticas()) {
            cerr << "No se ha podido leer el fichero usuarios \"" << FICHERO_USUARIOS << "\"."  << endl;
        };
    } else if (orden == "USUARIO") {
        string usuario;
        cin >> usuario;
        ordenUsuario(usuario);
    } else if (orden == "MAYORES") {
        string numeroMayores;
        cin >> numeroMayores;
        ordenMayores(nombreFichero, numeroMayores);
    } else if (orden == "INFORME") {
        string nombreFicheroInforme;
        cin >> nombreFicheroInforme;
        ordenInforme(nombreFichero, nombreFicheroInforme);
    } else if (orden == "DESTINOS") {
        string nombreFicheroAEscribir;
        cout << "Escriba el nombre del fichero del informe" << endl
             << "(presione solo ENTRAR para escribirlo en la pantalla): ";

        /* ignorar el salto de linea */
        cin.ignore();

        getline(cin, nombreFicheroAEscribir);
        ordenDestinos(nombreFichero, nombreFicheroAEscribir);
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

    imprimirFichero(FICHERO_AYUDA);
    while (!elejirOrden(nombreFichero));

    return 0;
}
