// enrutador.cpp
#include "enrutador.h"
#include <iostream>

using namespace std;

Enrutador::Enrutador(const string& nombre) : nombre(nombre) {}

void Enrutador::agregarConexion(const string& destino, int costo) {
    conexionesDirectas[destino] = costo;
}

void Enrutador::removerConexion(const string& destino) {
    conexionesDirectas.erase(destino);
}

void Enrutador::actualizarTabla(const string& destino, int costo) {
    tablaEnrutamiento[destino] = costo;
}

string Enrutador::obtenerNombre() const {
    return nombre;
}

const map<string, int>& Enrutador::obtenerConexiones() const {
    return conexionesDirectas;
}

const map<string, int>& Enrutador::obtenerTabla() const {
    return tablaEnrutamiento;
}

void Enrutador::limpiarTabla() {
    tablaEnrutamiento.clear();
}
