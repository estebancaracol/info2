#include "metodos.h"
#include "auxiliares.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Primer metodo de codificacion
string codificarMetodo1(const string& texto, int n) {
    string binarioCompleto;

    // Convertir todo el texto a binario
    for (char c : texto) {
        binarioCompleto += charABinario(c);
    }

    string resultado;
    int longitud = binarioCompleto.length();
    int numGrupos = (longitud + n - 1) / n;
    int unosAnteriores = 0, cerosAnteriores = 0;

    for (int i = 0; i < numGrupos; ++i) {
        int inicio = i * n;
        int fin = min(inicio + n, longitud);
        string grupo = binarioCompleto.substr(inicio, fin - inicio);

        if (i == 0) {
            // Primer grupo: invertir todos los bits
            for (char &bit : grupo) {
                bit = (bit == '0') ? '1' : '0';
            }
        } else {
            // Aplicar reglas segun el grupo anterior
            if (unosAnteriores == cerosAnteriores) {
                // Invertir todos los bits
                for (char &bit : grupo) {
                    bit = (bit == '0') ? '1' : '0';
                }
            } else if (cerosAnteriores > unosAnteriores) {
                // Invertir cada 2 bits
                for (size_t j = 1; j < grupo.size(); j += 2) {
                    grupo[j] = (grupo[j] == '0') ? '1' : '0';
                }
            } else {
                // Invertir cada 3 bits
                for (size_t j = 2; j < grupo.size(); j += 3) {
                    grupo[j] = (grupo[j] == '0') ? '1' : '0';
                }
            }
        }

        // Actualizar conteos para siguiente grupo (del grupo MODIFICADO)
        unosAnteriores = count(grupo.begin(), grupo.end(), '1');
        cerosAnteriores = grupo.length() - unosAnteriores;

        resultado += grupo;
    }

    return resultado;
}

// Segundo metodo de codificacion
string codificarMetodo2(const string& texto, int n) {
    string binarioCompleto;

    // Convertir todo el texto a binario
    for (char c : texto) {
        binarioCompleto += charABinario(c);
    }

    string resultado;
    int longitud = binarioCompleto.length();
    int numGrupos = (longitud + n - 1) / n;

    for (int i = 0; i < numGrupos; ++i) {
        int inicio = i * n;
        int fin = min(inicio + n, longitud);
        string grupo = binarioCompleto.substr(inicio, fin - inicio);

        // Rotacion de bits: ultimo pasa al frente
        if (!grupo.empty()) {
            string rotado;
            rotado += grupo.back();
            rotado += grupo.substr(0, grupo.length() - 1);
            grupo = rotado;
        }

        resultado += grupo;
    }

    return resultado;
}

// Primer metodo de decodificacion (inverso al de codificacion)
string decodificarMetodo1(const string& codificado, int n) {
    string binarioCompleto = codificado;
    string resultado;
    int longitud = binarioCompleto.length();
    int numGrupos = (longitud + n - 1) / n;
    int unosAnteriores = 0, cerosAnteriores = 0;

    for (int i = 0; i < numGrupos; ++i) {
        int inicio = i * n;
        int fin = min(inicio + n, longitud);
        string grupo = binarioCompleto.substr(inicio, fin - inicio);

        if (i == 0) {
            // Invertir todos los bits (misma operacion que en codificacion)
            for (char &bit : grupo) {
                bit = (bit == '0') ? '1' : '0';
            }
            // Para decodificar necesitamos los conteos del grupo original
            string grupoOriginal = binarioCompleto.substr(inicio, fin - inicio);
            unosAnteriores = count(grupoOriginal.begin(), grupoOriginal.end(), '1');
            cerosAnteriores = grupoOriginal.length() - unosAnteriores;
        } else {
            string nuevoGrupo = grupo;

            // Aplicar las mismas transformaciones que en la codificacion
            if (unosAnteriores == cerosAnteriores) {
                for (char &bit : nuevoGrupo) {
                    bit = (bit == '0') ? '1' : '0';
                }
            } else if (cerosAnteriores > unosAnteriores) {
                for (size_t j = 1; j < nuevoGrupo.size(); j += 2) {
                    nuevoGrupo[j] = (nuevoGrupo[j] == '0') ? '1' : '0';
                }
            } else {
                for (size_t j = 2; j < nuevoGrupo.size(); j += 3) {
                    nuevoGrupo[j] = (nuevoGrupo[j] == '0') ? '1' : '0';
                }
            }

            // Actualizar conteos para el proximo grupo (del original no codificado)
            string grupoOriginal = binarioCompleto.substr(inicio, fin - inicio);
            unosAnteriores = count(grupoOriginal.begin(), grupoOriginal.end(), '1');
            cerosAnteriores = grupoOriginal.length() - unosAnteriores;
            grupo = nuevoGrupo;
        }
        resultado += grupo;
    }

    // Convertir el binario decodificado a texto
    string textoOriginal;
    for (size_t i = 0; i < resultado.length(); i += 8) {
        string byteStr = resultado.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0');
        }
        textoOriginal += binarioAChar(byteStr);
    }

    return textoOriginal;
}

// Segundo metodo de decodificacion (inverso al de codificacion)
string decodificarMetodo2(const string& codificado, int n) {
    string binarioCompleto = codificado;
    string resultado;
    int longitud = binarioCompleto.length();
    int numGrupos = (longitud + n - 1) / n;

    for (int i = 0; i < numGrupos; ++i) {
        int inicio = i * n;
        int fin = min(inicio + n, longitud);
        string grupo = binarioCompleto.substr(inicio, fin - inicio);

        // Rotacion inversa: primer bit va al final
        if (!grupo.empty()) {
            string rotado;
            rotado += grupo.substr(1);
            rotado += grupo[0];
            grupo = rotado;
        }
        resultado += grupo;
    }

    // Convertir el binario decodificado a texto
    string textoOriginal;
    for (size_t i = 0; i < resultado.length(); i += 8) {
        string byteStr = resultado.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0');
        }
        textoOriginal += binarioAChar(byteStr);
    }

    return textoOriginal;
}

