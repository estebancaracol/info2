#ifndef METODOS_H
#define METODOS_H

#include <iostream>
#include <fstream>
#include <string>

#include "auxiliares.h"

using namespace std;

string codificarMetodo1(const string& texto, int n);
string codificarMetodo2(const string& texto, int n);
string decodificarMetodo1(const string& codificado, int n);
string decodificarMetodo2(const string& codificado, int n);

#endif // METODOS_H
