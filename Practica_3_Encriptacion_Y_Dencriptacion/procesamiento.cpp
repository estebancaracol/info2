#include "procesamiento.h"
#include "metodos.h"
#include "auxiliares.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Funcion para procesar codificacion
void procesarCodificacion() {
    string nombreArchivo, texto;
    int n, metodo;

    cout << "\nDigite el nombre del archivo para guardar (sin extension): ";
    cin >> nombreArchivo;
    nombreArchivo += ".txt";

    cout << "Ingrese el dimension del bloque (n): ";
    cin >> n;

    cout << "Ingrese el texto a codificar: ";
    cin.ignore();
    getline(cin, texto);

    metodo = mostrarMenuMetodos();
    while (metodo < 1 || metodo > 2) {
        if (metodo == 3) return;
        cout << "Opcion no valida. Intente nuevamente.\n";
        metodo = mostrarMenuMetodos();
    }

    string resultado;
    if (metodo == 1) {
        resultado = codificarMetodo1(texto, n);
    } else {
        resultado = codificarMetodo2(texto, n);
    }

    cout << "codificado" << resultado << endl;

    escribirArchivo(nombreArchivo, resultado);
    cout << "Texto codificado con exito y guardado en " << nombreArchivo << endl;
}

void procesarDecodificacion() {
    const size_t FIN = string::npos;
    string nombreArchivo;
    int n, metodo;

    cout << "\nDigite el nombre del archivo a decodificar (sin extension): ";
    cin >> nombreArchivo;
    nombreArchivo += ".txt";

    cout << "Ingrese el dimension del bloque (n): ";
    cin >> n;

    string contenidoCodificado = leerArchivo(nombreArchivo);
    if (contenidoCodificado.empty()) {
        return;
    }

    metodo = mostrarMenuMetodos();
    while (metodo < 1 || metodo > 2) {
        if (metodo == 3) return;
        cout << "Opcion no valida. Intente nuevamente.\n";
        metodo = mostrarMenuMetodos();
    }

    cout << "\nTexto decodificado:\n";
    string resultadoCompleto;

    // Procesar linea por linea
    size_t inicio = 0;
    size_t fin = contenidoCodificado.find('\n');

    while (inicio != FIN) {
        string lineaCodificada = contenidoCodificado.substr(inicio, (fin == FIN) ? FIN : fin - inicio);

        // Verifica que la linea no este vacia
        if (!lineaCodificada.empty()) {
            string lineaDecodificada;
            if (metodo == 1) {
                lineaDecodificada = decodificarMetodo1(lineaCodificada, n);
            } else {
                lineaDecodificada = decodificarMetodo2(lineaCodificada, n);
            }

            cout << lineaDecodificada << endl;
            if (!resultadoCompleto.empty()) {
                resultadoCompleto += "\n";
            }
            resultadoCompleto += lineaDecodificada;
        }

        inicio = (fin == FIN) ? fin : fin + 1;
        fin = contenidoCodificado.find('\n', inicio);
    }

    // Preguntar si desea guardar el resultado
    char guardar;
    cout << "\nDesea guardar el resultado en un archivo? (s/n): ";
    cin >> guardar;

    if (guardar == 's' || guardar == 'S') {
        cout << "Digite el nombre del archivo para guardar (sin extension): ";
        cin >> nombreArchivo;
        nombreArchivo += ".txt";
        escribirArchivo(nombreArchivo, resultadoCompleto);
        cout << "Resultado guardado en " << nombreArchivo << endl;
    }
}

// Encripta la clave (solo retorna el texto codificado)
string encriptar(const string& aCodificar, const string& nombreArchivo) {
    int n = generarRandom(4, 9);       // n entre 4 y 9
    int metodo = generarRandom(1, 2);  // Método 1 o 2

    string codificado;
    if (metodo == 1) {
        codificado = codificarMetodo1(aCodificar, n);
    } else {
        codificado = codificarMetodo2(aCodificar, n);
    }

    //cout << "n " << n << " Acodificar " << aCodificar << " codificado " << codificado << " metodo " << metodo << endl;

    escribirArchivo(nombreArchivo, codificado);

    return codificado;  // Solo retorna el texto codificado
}

// Desencripta probando n (4-9) y ambos métodos

string desencriptar(const string& encriptada, const string& desencriptado) {
    for (int n = 4; n <= 9; ++n) {
        for (int metodo = 1; metodo <= 2; ++metodo) {
            string decodificado = (metodo == 1) ? decodificarMetodo1(encriptada, n) : decodificarMetodo2(encriptada, n);

            if (decodificado == desencriptado) {
                return decodificado; // Retorna solo el valor desencriptado
            }
        }
    }
    return ""; // Retorna vacío si no coincide
}

string desencriptarAutoNumerico(const string& encriptada) {
    for (int n = 4; n <= 9; ++n) {
        for (int metodo = 1; metodo <= 2; ++metodo) {
            string decodificado = (metodo == 1) ? decodificarMetodo1(encriptada, n) : decodificarMetodo2(encriptada, n);

            // Primera verificación: numero puro (incluyendo decimales)
            if (esNumerico(decodificado)) {
                return decodificado;
            }

            //cout << decodificado << endl;

            // Segunda verificación: numero con simbolo $ (para saldos)
            if (!decodificado.empty() && decodificado[0] == '$' &&
                esNumerico(decodificado.substr(1))) {
                return decodificado.substr(1);
            }
        }
    }
    return ""; // No se encontró un resultado numérico válido
}
