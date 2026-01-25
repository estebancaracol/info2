// enrutador.h
#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

using namespace std;

class Enrutador {
public:
    Enrutador() : nombre("") {}
    Enrutador(const string& nombre);

    void agregarConexion(const string& destino, int costo);
    void removerConexion(const string& destino);
    void actualizarTabla(const string& destino, int costo);
    void limpiarTabla();

    string obtenerNombre() const;
    const map<string, int>& obtenerConexiones() const;
    const map<string, int>& obtenerTabla() const;

private:
    string nombre;
    map<string, int> conexionesDirectas;
    map<string, int> tablaEnrutamiento;
};

#endif // ENRUTADOR_H
