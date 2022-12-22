/*********************************************************************************************\
 * Programación 1. Trabajo obligatorio
 * Autores: Jaime Alonso y Hugo Cornago
 * Ultima revisión: ¡¡¡!!!
 * Resumen: Fichero de implementación del módulo principal que implementa el trabajo
 *          obligatorio de Programación 1 del curso 2022-23.
\*********************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* Estructura de datos que almacenara información basica sobre
 * un fichero (su nombre), y un puntero a la lectura del mismo con el fin de
 * minimizar el numero de aperturas del fichero.
 */
struct Fichero {
    string nombre;
    ifstream* f;
};

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
    cin >> opcion;
    string fichero = "datos/usos-" + opcion + ".csv";

    return fichero;
}

/* Pre: ---
 * Post: Cambia el fichero <fichero> dependiendo de la salida
 *       de la función selectorDeFichero().
 *       La función modifica la componente <nombre> y <f> del parametro <fichero>.
 */
bool ordenFichero(Fichero& fichero) {
    const auto& nombre_fichero = selectorDeFichero();
    ifstream fichero_abierto {nombre_fichero};
    if (!fichero_abierto.is_open()) {
        cerr << "No se ha podido leer el fichero \"" << nombre_fichero << "\"" << endl;
        return false;
    }

    fichero.nombre = nombre_fichero;
    fichero.f = &fichero_abierto;

    cout << "El fichero \"" << fichero.nombre << "\" existe y ha sido seleccionado." << endl;
    return true;
}

/* Pre: ---
 * Post: Imprime en pantalla información sobre los usos del fichero
 *       selecionado por el usuario.
 */
void pantallaUsos(const Fichero& fichero) {
    cout << "Orden: usos" << endl;
    cout << "Fichero de usos seleccionado actualmente: " << fichero.nombre << "." << endl;
    cout << "Número de usos como traslado: " << endl;
    cout << "Número de usos circulares: " << endl;
    cout << "Número total de usos: " << endl;
    cout << "Orden: " << endl;
}

/* Pre: <fichero> debe estar incializado y su componente <f> debe apuntar a un
 *      fichero abierto con permisos de lectura.
 * Post: Devuelve "true" si ha podido obtener el numero de usos de ...
 *       En cualquier otro caso, devuelve "false".
 */
bool ordenUsos(Fichero& fichero) {
    throw logic_error("Función aun no implementada!");
}

/* Pre: ---
 * Post: Ejecuta la orden "ESTADISTICAS".
 */
bool ordenEstadisticas(Fichero& fichero) {
    throw logic_error("Función aun no implementada!");
}
/* Pre: ---
 * Post: Ejecuta la orden "USUARIO".
 */
bool ordenUsuario(Fichero& fichero, std::string args) {
    throw logic_error("Función aun no implementada!");
}
/* Pre: ---
 * Post: Ejecuta la orden "MAYORES".
 */
bool ordenMayores(Fichero& fichero, std::string args) {
    throw logic_error("Función aun no implementada!");
}
/* Pre: ---
 * Post: Ejecuta la orden "INFORME".
 */
bool ordenInforme(Fichero& fichero, std::string args) {
    throw logic_error("Función aun no implementada!");
}
/* Pre: ---
 * Post: Ejecuta la orden "DESTINOS".
 */
bool ordenDestinos(Fichero& fichero, std::string args) {
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
    cout << "ESTADISTICAS:" << setw(9) << "Informa la distribución por edades y géneros de los usuarios." << endl;
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
    cout << endl;
}

/* Pre: ---
 * Post: 
 *       Devuelve "true" si el usuario a dado la orden "FIN".
 *       Devuelve "false" en cualquier otro caso.
 */
bool ejecutarOrden(const string& orden, Fichero& fichero) {
    if (orden == "AYUDA") {
        imprimirOrdenesDisponibles();
    } else if (orden == "FICHERO") {
        while (!ordenFichero(fichero));
    } else if (orden == "USOS") {
        ordenUsos(fichero);
    } else if (orden == "ESTADISTICAS") {
        ordenEstadisticas(fichero);
    } else if (orden == "USUARIO") {
        string args;
        cin >> args;
        ordenUsuario(fichero, args);
    } else if (orden == "MAYORES") {
        string args;
        cin >> args;
        ordenMayores(fichero, args);
    } else if (orden == "INFORME") {
        string args;
        cin >> args;
        ordenInforme(fichero, args);
    } else if (orden == "DESTINOS") {
        string args;
        cin >> args;
        ordenDestinos(fichero, args);
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
bool elejirOrden(Fichero& fichero) {
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

    return ejecutarOrden(orden, fichero);
}


int main(){
    Fichero f;
    bool parar {false};

    while (!ordenFichero(f)) {
        cout << endl;
    };
    cout << endl;

    imprimirOrdenesDisponibles();
    while (!parar) {
        if (elejirOrden(f)) {
            /* elejirOrden devuelve true cuando el usuario ha decidido salir del programa.
             * En ese caso, saldremos del bucle. */
            parar = true;
        }
        cout << endl;
    }
    return 0;
}
