#include <iostream>
#include <string>
#include <limits>
#include "red.h"

using namespace std;

void mostrarMenu() {
    cout << "\n-------MENU-------\n";
    cout << "1. Agregar enrutador\n";
    cout << "2. Remover enrutador\n";
    cout << "3. Agregar enlace\n";
    cout << "4. Remover enlace\n";
    cout << "5. Mostrar tabla de enrutamiento\n";
    cout << "6. Consultar costo de envio\n";
    cout << "7. Consultar camino optimo\n";
    cout << "8. Generar red aleatoria\n";
    cout << "9. Guardar copia\n";
    cout << "10. Salir sin guardar\n";
    cout << "Seleccione una opcion: ";
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Red red;
    int opcion;
    string nombreArchivo;

    // Pedir nombre del archivo al inicio
    cout << "Ingrese el nombre del archivo de la red (ej: enlaces_red.txt): ";
    getline(cin, nombreArchivo);

    cout << "=======================" << endl;
    cout << "CARGANDO RED DE ROUTERS" << endl;
    cout << "=======================" << endl;

    // Cargar datos iniciales
    red.cargarDesdeArchivo(nombreArchivo);
    red.calcularTablasEnrutamiento();

    do {
        mostrarMenu();
        cin >> opcion;
        limpiarBuffer();

        switch(opcion) {
        case 1: // Agregar enrutador
            red.agregarEnrutadorConAutoConexiones();
            break;

        case 2: // Remover enrutador
            red.removerEnrutador();
            break;

        case 3: // Agregar Enlace
            red.AEnlace();
            break;

        case 4: // Remover Enlace
            red.REnlace();
            break;

        case 5: // Mostrar tablas
            red.mostrarTablas();
            break;

        case 6: // Consultar costo
            red.consultarCostoEnvio();
            break;

        case 7: // Consultar camino óptimo
            red.consultarCaminoOptimo();
            break;

        case 8: // Generar red aleatoria
            int cantidad, maxCosto;

            cout << "Cantidad de enrutadores: ";
            cin >> cantidad;
            cout << "Costo maximo: ";
            cin >> maxCosto;

            red.generarRedAleatoria(cantidad, maxCosto, "enlaces_respaldo.txt");
            cout << "Red aleatoria generada\n";
            break;

        case 9: // Guardar copia
        {
            string nombreCopia;
            cout << "Ingrese el nombre para el archivo de copia (ej: copia_red.txt): ";
            getline(cin, nombreCopia);
            red.guardarRed(nombreCopia);
            cout << "Red guardada como '" << nombreCopia << "'. Saliendo...\n";
            //opcion = 10; // Para salir del bucle
        }
        break;

        case 10: // Salir sin guardar
            cout << "Saliendo sin guardar cambios...\n";
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 10);

    return 0;
}
