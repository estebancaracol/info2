#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include "metodos.h"
#include "auxiliares.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void procesarCodificacion();
void procesarDecodificacion();
string encriptar(const string& aCodificar, const string& nombreArchivo);
string desencriptar(const string& encriptada, const string& desencriptado);
string desencriptarAutoNumerico(const string& encriptada);

#endif // PROCESAMIENTO_H
