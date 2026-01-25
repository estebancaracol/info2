#include <iostream>
#include <cstdlib>
#include "problemas.h"

using namespace std;

int problema2(){
    const int SIZE = 200;
    char letras[SIZE];
    int conteo[26] = {0}; // Arreglo para contar las letras de 'A' a 'Z'

    srand(time(0)); // Inicializar la semilla aleatoria

    // Generar el arreglo de letras aleatorias
    for (int i = 0; i < SIZE; i++) {
        letras[i] = 'A' + rand() % 26; // Genera una letra entre 'A' y 'Z'
        conteo[letras[i] - 'A']++; // Contar la letra generada
    }

    // Imprimir el arreglo de letras
    for (int i = 0; i < SIZE; i++) {
        cout << letras[i];
    }

    // Imprimir la cantidad de repeticiones de cada letra
    for (int i = 0; i < 26; i++) {
        if (conteo[i] > 0) {
            cout << " " << endl;
            cout << char('A' + i) << ": " << conteo[i] << endl;
        }
    }

    return 0;
}

int main()
{
    int x = 0;

    while(true){
        cout << "\nIngrese el numero del ejercicio: " << endl;
        cin >> x;
        cin.ignore();

        switch (x) {
        case 2:
            problema2();
            break;
        case 4:{
            char cadena[100];

            cout << "Ingrese una cadena numerica: ";
            cin >> cadena;

            int numero = convertirCadenaAEntero(cadena);
            cout << "El numero convertido es: " << numero << endl;
            break;
        }
        case 6:{
            char cadena1[100];

            cout << "Ingrese una cadena: ";
            cin.getline(cadena1, 100);  // Permite espacios y guiones

            cout << "Original: " << cadena1 << endl;

            convertirAMayusculas(cadena1);

            cout << "En mayuscula: " << cadena1 << endl;
            break;
        }
        case 8:{
            char cadena2[100];
            char soloTexto[100];
            char soloNumeros[100];

            cout << "Ingrese una cadena con letras y numeros: ";
            cin.getline(cadena2, 100);

            separarTextoYNumeros(cadena2, soloTexto, soloNumeros);

            cout << "Original: " << cadena2 << endl;
            cout << "Texto: " << soloTexto << " Numero: " << soloNumeros << endl;
            break;
        }
        case 12:{
            int n = 0;
            int matriz[MAX][MAX];

            cout << "Ingrese el dimension de la matriz cuadrada (n x n): ";
            cin >> n;

            while (n <= 0 || n > MAX) {
                cout << "Por favor, ingrese un valor valido entre 1 y " << MAX << ": ";
                cin >> n;
            }

            cout << "Ingrese los elementos de la matriz:" << endl;
            for (int i = 0; i < n; i++) {
                cout << "Fila " << i + 1 << " ";
                for (int j = 0; j < n; j++) {
                    if (j > 0) cout << ", ";
                    cin >> matriz[i][j];
                    //cout << matriz[i][j];
                }
                cout << " " << endl;
            }

            cout << "Matriz ingresada:" << endl;
            imprimirMatriz(matriz, n);

            if (esCuadradoMagico(matriz, n)) {
                cout << "La matriz es un CUADRADO MAGICO." << endl;
            } else {
                cout << "La matriz NO es un cuadrado magico." << endl;
            }
            break;
        }
        case 14:{
            int original[TAM][TAM];
            int matriz90[TAM][TAM], matriz180[TAM][TAM], matriz270[TAM][TAM];

            llenarMatriz(original);

            cout << "Matriz Original:\n";
            imprimirMatriz(original);

            rotar90(original, matriz90);
            cout << "Matriz Rotada 90 grados:\n";
            imprimirMatriz(matriz90);

            rotar180(original, matriz180);
            cout << "Matriz Rotada 180 grados:\n";
            imprimirMatriz(matriz180);

            rotar270(original, matriz270);
            cout << "Matriz Rotada 270 grados:\n";
            imprimirMatriz(matriz270);
            break;
        }
        case 16:{
            int n;
            cout << "Ingrese el dimension de la malla (n): ";
            cin >> n;

            imprimirMalla(n);

            int caminos = calcularCaminos(n);
            cout << "\nEl total de caminos desde [0, 0] hasta [" << n << ", " << n << "]: ";
            cout << caminos << endl;
            break;
        }
        case 18:{
            int n;
            cout << "Ingrese el valor de n: ";
            cin >> n;

            string permutacion = encontrarPermutacion(n);
            cout << "La permutacion numero " << n << " es: " << permutacion << endl;
        }
        }
    }
}
