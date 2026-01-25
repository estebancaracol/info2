#ifndef CAJERO_H
#define CAJERO_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

#include "metodos.h"
#include "auxiliares.h"
#include "procesamiento.h"

using namespace std;

struct Usuario {
    string cedula;
    string clave;
    float saldo;
};

bool validarAccesoAdministrador();
void cambiarClaveAdministrador();
void registrarUsuario();
void consultarSaldo(const Usuario& DatosUsuario);
void retirarDinero(Usuario& DatosUsuario);
bool actualizarUsuario(const Usuario& DatosUsuario);
void menuUsuario(Usuario& DatosUsuario);
bool usuarioExistente(const string& usuarioBuscar, Usuario& DatosUsuario);
bool BuscarUsuario(const string& usuarioBuscar);
void registrarTransaccion(const string& cedula, double monto, double saldoRestante);
void consultarHistorial(const Usuario& DatosUsuario);

#endif // CAJERO_H
