#include <iostream>
#include <climits> // Para sizeof y CHAR_BIT

using namespace std;

// Funcion para mostrar la representacion binaria de un numero
void mostrarBinario(int num) {
    int bits = sizeof(int) * CHAR_BIT;
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((num >> i) & 1);
        if (i % 4 == 0) cout << " "; // Espaciado cada 4 bits
    }
    cout << endl;
}

int main() {
    int num, opcion, n;

    cout << "Ingrese un numero entero: ";
    cin >> num;

    while (true) {
        cout << "\n=================================\n";
        cout << "Numero actual: " << num << endl;
        cout << "Representacion binaria:\n";
        mostrarBinario(num);
        cout << "=================================\n";

        cout << "\nMenu de opciones:\n"
             << "1. Obtener LSB y MSB\n"
             << "2. Obtener el n-esimo bit\n"
             << "3. Poner a 1 el n-esimo bit\n"
             << "4. Contar bits de valor 0\n"
             << "5. Completar el n-esimo bit\n"
             << "6. Determinar el bit mas a la derecha con valor 1\n"
             << "7. Completar todos los bits\n"
             << "8. Determinar si el numero es par o impar\n"
             << "9. Salir del programa\n"
             << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: { // Obtener LSB y MSB
            int lsb = num & 1;
            int msb = (num >> (sizeof(int) * CHAR_BIT - 1)) & 1;
            cout << "\n=================================\n";
            cout << "LSB: " << lsb << "\nMSB: " << msb << endl;
            cout << "=================================\n";
            break;
        }
        case 2: { // Obtener el n-esimo bit
            cout << "\n=================================\n";
            cout << "Ingrese el indice del bit (0-31): ";
            cin >> n;
            int bit = (num >> n) & 1;
            cout << "El bit en la posicion " << n << " es: " << bit << endl;
            cout << "=================================\n";
            break;
        }
        case 3: { // Poner a 1 el n-esimo bit
            cout << "\n=================================\n";
            cout << "Ingrese el indice del bit a modificar (0-31): ";
            cin >> n;
            num |= (1 << n);
            cout << "Numero modificado: " << num << endl;
            cout << "=================================\n";
            break;
        }
        case 4: { // Contar bits de valor 0
            int count = 0, totalBits = sizeof(int) * CHAR_BIT;
            for (int i = 0; i < totalBits; i++) {
                if (((num >> i) & 1) == 0)
                    count++;
            }
            cout << "\n=================================\n";
            cout << "Cantidad de bits en 0: " << count << endl;
            cout << "=================================\n";
            break;
        }
        case 5: { // Completar el n-esimo bit (igual a poner a 1)
            cout << "\n=================================\n";
            cout << "Ingrese el indice del bit a completar (0-31): ";
            cin >> n;
            num |= (1 << n);
            cout << "Numero modificado: " << num << endl;
            cout << "=================================\n";
            break;
        }
        case 6: { // Determinar el bit mas a la derecha con valor 1
            int rightmostBit = num & -num;
            cout << "\n=================================\n";
            cout << "Bit mas a la derecha con valor 1: " << rightmostBit << endl;
            cout << "=================================\n";
            break;
        }
        case 7: { // Completar todos los bits
            num = ~0;
            cout << "\n=================================\n";
            cout << "Numero modificado: " << num << endl;
            cout << "=================================\n";
            break;
        }
        case 8: { // Determinar si el numero es par o impar
            if (num & 1){
                cout << "\n=================================\n";
                cout << "El numero es impar.\n";
            }else
                cout << "El numero es par.\n";
                cout << "=================================\n";
            break;
        }
        case 9: // Salir del programa
            cout << "Saliendo del programa...\n";
            return 0;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    }

    return 0;
}

