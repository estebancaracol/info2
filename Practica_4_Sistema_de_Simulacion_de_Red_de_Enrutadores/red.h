// red.h
#ifndef RED_H
#define RED_H

#include <map>
#include <string>
#include "enrutador.h"

using namespace std;

class Red {
public:
    void agregarEnrutador(const string& nombre);
    void agregarEnrutadorConAutoConexiones();
    void removerEnrutador();
    void AEnlace();
    void REnlace();
    void consultarCostoEnvio() const;
    void consultarCaminoOptimo() const;
    void generarRedAleatoria(int cantidadEnrutadores, int maxCosto, const string& archivoRespaldo);
    void agregarEnlace(const string& origen, const string& destino, int costo);
    void removerEnlace(const string& origen, const string& destino);
    void cargarDesdeArchivo(const string& nombreArchivo);
    void guardarRed(const string& nombreArchivo) const;
    void calcularTablasEnrutamiento();
    void mostrarTablas() const;
    void guardarMatrizEnArchivo(const string& nombreArchivo) const;

private:
    void dijkstra(const string& origen);
    map<string, Enrutador> enrutadores;
};

#endif // RED_H
