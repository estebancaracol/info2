#include <iostream>

using namespace std;

int ejercicio_1() {
    char caracter = ' ';

    cout << "Ingrese un caracter: ";
    cin >> caracter;

    if (caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u' || caracter == 'A' || caracter == 'E' || caracter == 'I' || caracter == 'O' || caracter == 'U'){
        cout << caracter << " es una vocal." << endl;
    } else {
        cout << caracter << " es una consonante." << endl;
    }
    return 0;
}

int ejercicio_3() {
    int dia = 0, mes = 0, diasEnMes = 0;

    cout << "Ingrese el mes: ";
    cin >> mes;

    cout << "Ingrese el dia: ";
    cin >> dia;

    if (mes < 1 || mes > 12) {
        cout << mes << " es un mes invalido." << endl;
        return 0;
    }

    switch (mes) {
    case 2:
        diasEnMes = 28;
        break;
    case 4: case 6: case 9: case 11:
        diasEnMes = 30;
        break;
    default:
        diasEnMes = 31;
        break;
    }

    if (dia < 1 || dia > diasEnMes) {
        if (mes == 2 && dia == 29) {
            cout << "29/2 es valida en bisiesto." << endl;
            return 0;
        }
        cout << dia << "/" << mes << " es una fecha invalida." << endl;
        return 0;
    }

    cout << dia << "/" << mes << " es una fecha valida." << endl;
    return 0;
}

void ejercicio_5(){
    int n = 0;

    cout << "Ingrese un numero impar: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Ingrese un numero impar" << endl;
        return;
    }

    // Parte superior
    for (int i = 1; i <= n; i += 2) {
        for (int j = 0; j < (n - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }

    // Parte inferior
    for (int i = n - 2; i >= 1; i -= 2) {
        for (int j = 0; j < (n - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }
}

int ejercicio_7(){
    int n = 0, suma = 0, temp = 0, a = 1, b = 1;

    cout << "Ingrese un numero para la suma de Fibonacci: ";
    cin >> n;

    while (b < n){
        if (b % 2 == 0){
            suma += b;
        }
        temp = a + b;
        a = b;
        b = temp;
    }
    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}

int ejercicio_9() {
    int n = 0, suma = 0, temp = 0, digito = 0, potencia = 0;

    cout << "Ingrese un numero para la suma de las potencias: ";
    cin >> n;

    temp = n;

    while (temp > 0) {
        digito = temp % 10;
        temp /= 10;

        potencia = 1;
        for (int i = 0; i < digito; i++) {
            potencia *= digito;
        }

        suma += potencia;
    }

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}

int ejercicio_11() {
    int n = 0, mcm = 1;

    cout << "Ingrese un numero: ";
    cin >> n;

    for (int i = 2; i <= n; i++) {
        int a = mcm, b = i, temp = 0;

        // Calcular el Maximo Comun Divisor (MCD) usando el algoritmo de Euclides
        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }

        mcm = (mcm * i) / a;
    }

    cout << "El minimo comun multiplo es: " << mcm << endl;
    return 0;
}

int ejercicio_13() {
    int n = 0, suma = 0;

    cout << "Ingrese un numero: ";
    cin >> n;

    for (int i = 2; i < n; i++) {
        bool esPrimo = true;

        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                esPrimo = false;
                break;
            }
        }

        if (esPrimo) {
            suma += i;
        }
    }

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}

/*
int ejercicio_15() {
    int n;
    cout << "Ingrese un numero impar para la espiral: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Debe ingresar un numero impar." << endl;
        return 0;
    }

    int x = n / 2, y = n / 2;  // Posicion inicial (centro)
    int valor = 1, paso = 1;   // Numero actual y pasos

    cout << "Espiral generada:" << endl;

    while (valor <= n * n) {
        // Mover a la derecha
        for (int i = 0; i < paso && valor <= n * n; i++) {
            y++;
            cout << "Valor " << valor++ << " en (" << x << "," << y << ")\n";
        }

        // Mover hacia abajo
        for (int i = 0; i < paso && valor <= n * n; i++) {
            x++;
            cout << "Valor " << valor++ << " en (" << x << "," << y << ")\n";
        }
        paso++;  // Incrementar pasos

        // Mover a la izquierda
        for (int i = 0; i < paso && valor <= n * n; i++) {
            y--;
            cout << "Valor " << valor++ << " en (" << x << "," << y << ")\n";
        }

        // Mover hacia arriba
        for (int i = 0; i < paso && valor <= n * n; i++) {
            x--;
            cout << "Valor " << valor++ << " en (" << x << "," << y << ")\n";
        }
        paso++;  // Incrementar pasos
    }

    return 0;
}
*/

int ejercicio_15() {
    int n;
    cout << "Ingrese un numero impar para la espiral: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Debe ingresar un numero impar." << endl;
        return 0;
    }

    int matriz[n][n];  // Matriz para la espiral
    int x = n / 2, y = n / 2;  // Centro de la matriz
    int valor = 1, paso = 1;

    matriz[x][y] = valor++;  // Ubicar el 1 en el centro

    while (valor <= n * n) {
        // Mover a la derecha
        for (int i = 0; i < paso && valor <= n * n; i++) matriz[x][++y] = valor++;
        // Mover hacia abajo
        for (int i = 0; i < paso && valor <= n * n; i++) matriz[++x][y] = valor++;
        paso++;  // Incrementar pasos

        // Mover a la izquierda
        for (int i = 0; i < paso && valor <= n * n; i++) matriz[x][--y] = valor++;
        // Mover hacia arriba
        for (int i = 0; i < paso && valor <= n * n; i++) matriz[--x][y] = valor++;
        paso++;  // Incrementar pasos
    }

    // Calcular la suma de las diagonales
    int sumaDiagonal = 0;
    for (int i = 0; i < n; i++) {
        sumaDiagonal += matriz[i][i];           // Diagonal principal
        sumaDiagonal += matriz[i][n - 1 - i];   // Diagonal secundaria
    }
    sumaDiagonal -= matriz[n / 2][n / 2];  // Restar el centro porque se cuenta dos veces

    // Imprimir la matriz en forma de espiral
    cout << "Espiral generada:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "En una espiral de " << n << "x" << n << ", la suma es: " << sumaDiagonal << endl;
    return 0;
}

int ejercicio_17() {
    int k = 0;
    cout << "Ingrese el numero k de divisores: ";
    cin >> k;

    int n = 1, Tn = 1;

    while (true) {
        int divisores = 0;

        // Contar divisores de Tn
        for (int i = 1; i * i <= Tn; i++) {
            if (Tn % i == 0) {
                divisores++; // Contamos i como divisor
                if (i != Tn / i) {
                    divisores++; // Contamos Tn/i si es distinto
                }
            }
        }

        if (divisores > k) {
            cout << "El numero es: " << Tn << " que tiene " << divisores << " divisores." << endl;
            return 0;
        }

        n++;
        Tn = n * (n + 1) / 2; // Calculamos el siguiente número triangular
    }
}


int main()
{
    int x = 0;

    while(true){
        cout << "Ingrese el numero del ejercicio (1-17, solo los impares): ";
        cin >> x;

        switch (x) {
        case 1:
            ejercicio_1();
            break;
        case 3:
            ejercicio_3();
            break;
        case 5:
            ejercicio_5();
            break;
        case 7:
            ejercicio_7();
            break;
        case 9:
            ejercicio_9();
            break;
        case 11:
            ejercicio_11();
            break;
        case 13:
            ejercicio_13();
            break;
        case 15:
            ejercicio_15();
            break;
        case 17:
            ejercicio_17();
            break;
        default:
            break;
        }
    }
}
