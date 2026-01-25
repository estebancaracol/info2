#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int mostrarMenuPrincipal();
int mostrarMenuAdministrador();
int mostrarMenuMetodos();
int mostrarMenuUsuario();
void escribirArchivo(const string& nombreArchivo, const string& contenido);
string leerArchivo(const string& nombreArchivo);
string charABinario(char c);
char binarioAChar(const string& binario);
int generarRandom(int min, int max);
bool esNumerico(const string& str);

#endif // AUXILIARES_H
