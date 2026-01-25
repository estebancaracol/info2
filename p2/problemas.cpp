#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

#include "problemas.h"

using namespace std;

int convertirCadenaAEntero(char cadena[]) {
    int resultado = 0;
    int i = 0;

    // Recorremos cada caracter hasta encontrar el fin de la cadena '\0'
    while (cadena[i] != '\0') {
        // Convertimos el caracter a numero restando '0' (codigo ASCII)
        resultado = resultado * 10 + (cadena[i] - '0');
        i++;
    }

    return resultado;
}

void convertirAMayusculas(char cadena[]) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] >= 'a' && cadena[i] <= 'z') {
            cadena[i] = cadena[i] - ('a' - 'A');  // o simplemente: cadena[i] -= 32;
        }
        i++;
    }
}

void separarTextoYNumeros(char original[], char texto[], char numeros[]) {
    int i = 0, j = 0, k = 0;

    while (original[i] != '\0') {
        if (original[i] >= '0' && original[i] <= '9') {
            numeros[j++] = original[i];
        } else {
            texto[k++] = original[i];
        }
        i++;
    }

    // Finalizamos ambas cadenas con el caracter nulo
    numeros[j] = '\0';
    texto[k] = '\0';
}

bool esCuadradoMagico(int matriz[MAX][MAX], int n) {
    int sumaObjetivo = 0;

    // Suma de la primera fila como referencia
    for (int j = 0; j < n; j++) {
        sumaObjetivo += matriz[0][j];
    }

    // Verificar filas
    for (int i = 1; i < n; i++) {
        int sumaFila = 0;
        for (int j = 0; j < n; j++) {
            sumaFila += matriz[i][j];
        }
        if (sumaFila != sumaObjetivo) return false;
    }

    // Verificar columnas
    for (int j = 0; j < n; j++) {
        int sumaColumna = 0;
        for (int i = 0; i < n; i++) {
            sumaColumna += matriz[i][j];
        }
        if (sumaColumna != sumaObjetivo) return false;
    }

    // Verificar diagonal principal
    int sumaDiagonal1 = 0;
    for (int i = 0; i < n; i++) {
        sumaDiagonal1 += matriz[i][i];
    }
    if (sumaDiagonal1 != sumaObjetivo) return false;

    // Verificar diagonal secundaria
    int sumaDiagonal2 = 0;
    for (int i = 0; i < n; i++) {
        sumaDiagonal2 += matriz[i][n - i - 1];
    }
    if (sumaDiagonal2 != sumaObjetivo) return false;

    // Verificar que no se repitan los numeros
    bool usados[MAX * MAX] = {false};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num = matriz[i][j];
            if (num < 1 || num > n * n || usados[num - 1]) return false;
            usados[num - 1] = true;
        }
    }

    return true;
}

void imprimirMatriz(int matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "/t";
        }
        cout << endl;
    }
}

void llenarMatriz(int matriz[TAM][TAM]) {
    int valor = 1;
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            matriz[i][j] = valor++;
}

void imprimirMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j)
            cout << matriz[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void rotar90(int original[TAM][TAM], int rotada[TAM][TAM]) {
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            rotada[j][TAM - 1 - i] = original[i][j];
}

void rotar180(int original[TAM][TAM], int rotada[TAM][TAM]) {
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            rotada[TAM - 1 - i][TAM - 1 - j] = original[i][j];
}

void rotar270(int original[TAM][TAM], int rotada[TAM][TAM]) {
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            rotada[TAM - 1 - j][i] = original[i][j];
}

int calcularCaminos(int n) {
    double resultado = 1.0;

    for (int i = 1; i <= n; i++) {
        resultado *= (n + i);
        resultado /= i;

        cout << "Paso " << i << ": ";
        cout << "Multiplico por " << (n + i) << ", divido por " << i;
        cout << " -> resultado = " << resultado << endl;
    }

    return (int)(resultado + 0.5);
}

void imprimirMalla(int n) {
    cout << "Malla de " << n << " x " << n << ":\n";

    for (int fila = 0; fila <= n; fila++) {
        for (int col = 0; col <= n; col++) {
            cout << "[";
            cout << setw(1) << fila << "," << setw(1) << col;
            cout << "] ";
        }
        cout << endl << endl;
    }
}

int factorial(int n) {
    int resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

// Funcion que retorna el n-esimo numero lexicografico
string encontrarPermutacion(int n) {
    int digitos[10];
    bool usado[10] = {false}; // marca si un digito ya fue usado
    for (int i = 0; i < 10; i++) digitos[i] = i;

    string resultado = "";
    n--; // Convertimos de 1-based a 0-based

    for (int i = 9; i >= 0; i--) {
        int fact = factorial(i);
        int bloque = n / fact;
        n = n % fact;

        // Buscar el bloque-esimo numero no usado
        int contador = -1;
        for (int j = 0; j < 10; j++) {
            if (!usado[j]) contador++;
            if (contador == bloque) {
                resultado += to_string(j);
                usado[j] = true;
                break;
            }
        }
    }

    return resultado;
}
