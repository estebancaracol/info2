#ifndef PROBLEMAS_H
#define PROBLEMAS_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 10;
const int TAM = 5;

int convertirCadenaAEntero(char cadena[]);
void convertirAMayusculas(char cadena[]);
void separarTextoYNumeros(char original[], char texto[], char numeros[]);
bool esCuadradoMagico(int matriz[MAX][MAX], int n);
void imprimirMatriz(int matriz[MAX][MAX], int n);
void llenarMatriz(int matriz[TAM][TAM]);
void imprimirMatriz(int matriz[TAM][TAM]);
void rotar90(int original[TAM][TAM], int rotada[TAM][TAM]);
void rotar180(int original[TAM][TAM], int rotada[TAM][TAM]);
void rotar270(int original[TAM][TAM], int rotada[TAM][TAM]);
int calcularCaminos(int n);
void imprimirMalla(int n);
int factorial(int n);
string encontrarPermutacion(int n);

#endif // PROBLEMAS_H


