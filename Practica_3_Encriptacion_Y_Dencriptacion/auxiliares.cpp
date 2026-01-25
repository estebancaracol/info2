#include "auxiliares.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Funcion para mostrar el menu Principal
int mostrarMenuPrincipal() {
    int opcion;
    cout << "\nMENU PRINCIPAL\n";
    cout << "---------------------------\n";
    cout << "1. Acceso como administrador\n";
    cout << "2. Acceso como usuario\n";
    cout << "3. Codificar texto\n";
    cout << "4. Decodificar texto\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    return opcion;
}

// Nueva funcion para mostrar menu de Administrador
int mostrarMenuAdministrador() {
    int opcion;
    cout << "\nMENU ADMINISTRADOR\n";
    cout << "---------------------------\n";
    cout << "1. Registrar nuevo usuario\n";
    cout << "2. Cambiar clave de administrador\n";
    cout << "3. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    return opcion;
}

// Funcion para mostrar el menu de Metodos
int mostrarMenuMetodos() {
    int opcion;
    cout << "\nSELECCIONE METODO\n";
    cout << "---------------------------\n";
    cout << "1. Metodo 1 (Inversion condicional)\n";
    cout << "2. Metodo 2 (Desplazamiento rotativo)\n";
    cout << "3. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    return opcion;
}

//Funcion para mostrar menu de Usuarios
int mostrarMenuUsuario() {
    int opcion;
    cout << "\nMENU USUARIO\n";
    cout << "---------------------------\n";
    cout << "1. Consultar saldo\n";
    cout << "2. Retirar dinero\n";
    cout << "3. Consultar historial de transacciones\n";
    cout << "4. Volver al menu principal\n";
    //cout << "Se ha cobrado $1000 COP por el acceso\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    return opcion;
}

// Funcion para leer el contenido de un archivo
string leerArchivo(const string& nombreArchivo) {
    ifstream archivo;
    string contenido;

    archivo.open(nombreArchivo);
    if (archivo.fail()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return "";  // Retorna string vacio en caso de error
    }

    // Leer todo el contenido linea por linea
    string linea;
    while (getline(archivo, linea)) {
        contenido += linea;
        // Si el archivo tiene multiples lineas, añade un salto de linea
        if (!archivo.eof()) {
            contenido += "\n";
        }
    }

    archivo.close();
    return contenido;
}

// Funcion para escribir en un archivo
void escribirArchivo(const string& nombreArchivo, const string& contenido) {
    // Abre el archivo en modo append (añadir al final)
    ofstream archivo(nombreArchivo, ios::app);

    if (!archivo) {
        //cerr << "Error al abrir/crear el archivo: " << nombreArchivo << endl;
        return;
    }

    // Escribe el contenido seguido de un salto de linea
    archivo << contenido << endl;
}

// Funcion para convertir un caracter a binario (8 bits)
string charABinario(char c) {
    string binario;
    for (int i = 7; i >= 0; --i) {
        binario += ((c >> i) & 1) ? '1' : '0';
    }
    return binario;
}

// Funcion para convertir binario (8 bits) a caracter
char binarioAChar(const string& binario) {
    char c = 0;
    for (int i = 0; i < 8; ++i) {
        if (binario[i] == '1') {
            c |= (1 << (7 - i));
        }
    }
    return c;
}

// Funcion para generar un numero aleatorio entre min y max
int generarRandom(int min, int max) {
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        srand(time(nullptr));
        semillaInicializada = true;
    }
    return min + rand() % (max - min + 1);
}

// Funcion para verificar si una cadena contiene solo digitos
bool esNumerico(const string& str) {
    bool puntoEncontrado = false;
    for (char const &c : str) {
        if (isdigit(c) == 0) {
            if (c == '.' && !puntoEncontrado) {
                puntoEncontrado = true;
            } else if (c == '-' && &c == &str[0]) {
                // Permite signo negativo al inicio
                continue;
            } else {
                return false;
            }
        }
    }
    return !str.empty();
}

