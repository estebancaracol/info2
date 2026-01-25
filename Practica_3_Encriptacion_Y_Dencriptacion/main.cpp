#include <iostream>
#include <fstream>
#include <string>

#include "metodos.h"
#include "cajero.h"
#include "auxiliares.h"
#include "procesamiento.h"

using namespace std;

int main() {
    while (true) {
        int opcion = mostrarMenuPrincipal();

        switch (opcion) {
        case 1: { // Acceso como administrador
            cin.ignore();
            if (validarAccesoAdministrador()) {
                // Admin menu
                int opcionAdmin;
                do {
                    opcionAdmin = mostrarMenuAdministrador();

                    switch (opcionAdmin) {
                    case 1: // Registrar nuevo usuario
                        registrarUsuario();
                        break;
                    case 2: // Cambiar clave de administrador
                        cambiarClaveAdministrador();
                        break;
                    case 3: // Volver al menu principal
                        cout << "Volviendo al menu principal...\n";
                        break;
                    default:
                        cout << "Opcion no valida.\n";
                    }
                } while (opcionAdmin != 3);
            }
            break;
        }
        case 2: { // Acceso como usuario
            Usuario DatosUsuario;
            string usuario;
            cout << "Ingrese su usuario (Cedula): ";
            cin >> usuario;

            if (usuarioExistente(usuario, DatosUsuario)) {
                menuUsuario(DatosUsuario);
            } else {
                cout << "Usuario no encontrado.\n";
            }
            break;
        }
        case 3: // Codificar texto
            procesarCodificacion();
            break;
        case 4: // Decodificar texto
            procesarDecodificacion();
            break;
        case 5: // Salir
            cout << "Saliendo del sistema...\n";
            return 0;
        default:
            cout << "Opcion no valida. Intente nuevamente.\n";
        }
    }
    return 0;
}
