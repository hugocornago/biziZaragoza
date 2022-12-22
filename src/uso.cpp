
#include "uso.hpp"

/* Pre: <fichero> debe estar incializado y su componente <f> debe apuntar a un
 *      fichero abierto con permisos de lectura.
 * Post: Devuelve "true" si ha podido obtener el numero de usos de ...
 *       En cualquier otro caso, devuelve "false".
 */
bool ordenUsos(Fichero& fichero) {
    string numTraslados;   
    string numCirculares;
    int numTotalUsos;
    ifstream fichero_abierto {fichero.nombre};
    if (!fichero_abierto.is_open()){
        string cabecera;
        getline(fichero_abierto, cabecera);
        string uso;
        while (getline(fichero_abierto, uso)){
            // TODO
            // numTotalUsos++;
            // if(getline(fichero_abierto, numTraslados))
            break;
        }
     }
     
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
bool leerUso(istream& fichero, UsoBizi& uso) {
    ordenFichero(Fichero& fichero);
    ofstream f(fichero);
    if (f.is_open(fichero)) {

    }
    else{
        cerr << "No se ha podido abrir el fichero" << endl;
    }

}

*
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


