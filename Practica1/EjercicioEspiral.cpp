/*#include <iostream>

using namespace std;

void generarEspiral(int n) {
    int x = n / 2, y = n / 2; // Posición inicial en el centro
    int num = 1;

    int dx = 1, dy = 0; // Dirección inicial (derecha)
    int pasos = 1, cambio = 0; // Pasos por nivel y cambios de dirección

    // Imprimir número inicial
    for (int fila = 0; fila < n; fila++) {
        for (int columna = 0; columna < n; columna++) {
            if (fila == x && columna == y)
                cout << num << "\t";
            else
                cout << ".\t"; // Se imprime un espacio vacío
        }
        cout << endl;
    }

    cout << endl;

    num++;

    while (num <= n * n) {
        for (int i = 0; i < pasos; i++) {
            x += dy;
            y += dx;

            // Imprimir la matriz con el nuevo número en su posición correcta
            for (int fila = 0; fila < n; fila++) {
                for (int columna = 0; columna < n; columna++) {
                    if (fila == x && columna == y)
                        cout << num << "\t";
                    else
                        cout << ".\t"; // Se imprime un espacio vacío
                }
                cout << endl;
            }

            cout << endl;
            num++;

            if (num > n * n) return; // Terminar si llegamos al último número
        }

        // Cambiar dirección
        int temp = dx;
        dx = -dy;
        dy = temp;

        cambio++;

        // Cada dos cambios de dirección, incrementamos los pasos
        if (cambio % 2 == 0)
            pasos++;
    }
}

int main() {
    int n;
    cout << "Ingrese un numero impar para la espiral: ";
    cin >> n;

    if (n % 2 == 0 || n < 1) {
        cout << "Por favor, ingrese un numero impar positivo.\n";
        return 1;
    }

    generarEspiral(n);
    return 0;
}
*/

/*#include <iostream>

using namespace std;

void generarEspiral(int n) {
    int x = n / 2, y = n / 2; // Centro de la espiral
    int num = 1;

    int dx = 1, dy = 0; // Dirección inicial (derecha)
    int pasos = 1, cambio = 0;

    // Generar todos los números y recordar sus posiciones
    for (int i = 1; i < n * n; i++) {
        x += dy;
        y += dx;

        // Cambiar dirección cuando se completa un segmento
        if (--pasos == 0) {
            int temp = dx;
            dx = -dy;
            dy = temp;

            cambio++;
            pasos = (cambio % 2 == 0) ? (cambio / 2) + 1 : cambio / 2 + 1;
        }
    }

    // Imprimir la espiral completa sin usar arreglos
    for (int fila = 0; fila < n; fila++) {
        for (int columna = 0; columna < n; columna++) {
            int x_calc = n / 2, y_calc = n / 2; // Centro
            int dx_calc = 1, dy_calc = 0;
            int pasos_calc = 1, cambio_calc = 0;
            int num_calc = 1;

            // Recorrer la espiral hasta la posición actual
            while (!(fila == x_calc && columna == y_calc)) {
                x_calc += dy_calc;
                y_calc += dx_calc;
                num_calc++;

                // Cambiar dirección si se completa un segmento
                if (--pasos_calc == 0) {
                    int temp = dx_calc;
                    dx_calc = -dy_calc;
                    dy_calc = temp;

                    cambio_calc++;
                    pasos_calc = (cambio_calc % 2 == 0) ? (cambio_calc / 2) + 1 : cambio_calc / 2 + 1;
                }
            }
            cout << num_calc << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese un número impar para la espiral: ";
    cin >> n;

    if (n % 2 == 0 || n < 1) {
        cout << "Por favor, ingrese un número impar positivo.\n";
        return 1;
    }

    generarEspiral(n);
    return 0;
}
*/

#include <iostream>
#include <thread> // Para la función sleep_for
#include <chrono> // Para definir el tiempo de espera

using namespace std;

void generarEspiral(int n) {
    int x = n / 2, y = n / 2; // Posición central de la espiral
    int num = 1;

    int dx = 1, dy = 0; // Dirección inicial (derecha)
    int pasos = 1, cambio = 0;

    // Imprimir la matriz vacía antes de empezar
    for (int i = 1; i <= n * n; i++) {
        // Limpiar pantalla (Windows: CLS, Linux/Mac: clear)

        // Imprimir la matriz actualizada
        for (int fila = 0; fila < n; fila++) {
            for (int columna = 0; columna < n; columna++) {
                if (fila == x && columna == y)
                    cout << num << "\t"; // Imprimir el número actual
                else
                    cout << ".\t"; // Espacio vacío
            }
            cout << endl;
        }

        // Pequeña pausa para visualizar el proceso
        this_thread::sleep_for(chrono::milliseconds(300));

        // Avanzar en la espiral
        if (num >= n * n) break; // Detener si se llenó la matriz

        x += dy;
        y += dx;
        num++;

        // Cambiar dirección cuando se completan los pasos actuales
        if (--pasos == 0) {
            int temp = dx;
            dx = -dy;
            dy = temp;

            cambio++;
            pasos = (cambio % 2 == 0) ? (cambio / 2) + 1 : cambio / 2 + 1;
        }
    }

    // Imprimir la matriz final con todos los números
    for (int fila = 0; fila < n; fila++) {
        for (int columna = 0; columna < n; columna++) {
            // Recorrer la espiral para encontrar el número correspondiente
            int x_calc = n / 2, y_calc = n / 2;
            int dx_calc = 1, dy_calc = 0;
            int pasos_calc = 1, cambio_calc = 0;
            int num_calc = 1;

            while (!(fila == x_calc && columna == y_calc)) {
                x_calc += dy_calc;
                y_calc += dx_calc;
                num_calc++;

                if (--pasos_calc == 0) {
                    int temp = dx_calc;
                    dx_calc = -dy_calc;
                    dy_calc = temp;
                    cambio_calc++;
                    pasos_calc = (cambio_calc % 2 == 0) ? (cambio_calc / 2) + 1 : cambio_calc / 2 + 1;
                }
            }
            cout << num_calc << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese un numero impar para la espiral: ";
    cin >> n;

    if (n % 2 == 0 || n < 1) {
        cout << "Por favor, ingrese un numero impar positivo.\n";
        return 1;
    }

    generarEspiral(n);
    return 0;
}


