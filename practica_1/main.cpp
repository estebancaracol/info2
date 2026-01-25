#include <iostream>
#include <cstdlib>

using namespace std;

int ejemplo1(){

    int a = 0, b = 0, c = 0;

    cout << "Ingrese el numero A: " << endl;
    cin  >> a;
    cout << "Ingrese el numero B: " << endl;
    cin >> b;

    while (b == 0){
        cout << "Ingrese un numero diferente de 0: " << endl;
        cin >> b;
    }

    c =  a % b;
    cout << "El residuo de la division " << a << "/" << b << " es " << c << endl;
    return 0;
}

int ejemplo2(){

    int n = 0;

    cout << "Ingrese un numero N: " << endl;
    cin >> n;

    if (n % 2 == 0){
        cout << n << " es par" << endl;
    } else {
        cout << n << " es impar" << endl;
    }
    return 0;
}

int ejemplo3(){

    int p = 0, s = 0;

    cout << "Ingrese el  primer numero P: " << endl;
    cin  >> p;
    cout << "Ingrese el segundo numero S: " << endl;
    cin >> s;

    if (p > s){
        cout << "El numero mayor es: " << p << endl;
    } else if ( s > p){
        cout << "El numero mayor es: " << s << endl;
    } else {
        cout << "Ambos numeros son iguales" << endl;
    }
    return 0;
}

int ejemplo4(){

    int p = 0, s = 0;

    cout << "Ingrese el  primer numero P: " << endl;
    cin  >> p;
    cout << "Ingrese el segundo numero S: " << endl;
    cin >> s;

    if (p < s){
        cout << "El numero menor es: " << p << endl;
    } else if ( s < p){
        cout << "El numero menor es: " << s << endl;
    } else {
        cout << "Ambos numeros son iguales" << endl;
    }
    return 0;
}

int  ejemplo5(){

    int a = 0 , b = 0, division = 0, residuo = 0;

    cout << "Ingrese el numero A: " << endl;
    cin >> a;

    cout << "Ingrese el numero B: " << endl;
    cin >> b;

    division = (a / b);
    residuo = (a % b);

    if (residuo * 2 >= b){
        division++;
    }
    cout << "El resultado de la division:\n" << a << "/" << b << " = " << division << endl;
    return 0;
}

int ejemplo6(){

    int a = 0, b = 0, resultado = 1;

    cout << "Ingrese el numero A: " << endl;
    cin >> a;

    cout << "Ingrese el numero B: " << endl;
    cin >> b;

    for (int i = 0; i < b;  i++){
        resultado = resultado * a;
    }

    cout << "El resultado de la potencia:\n" << a << "^" << b<< " = " << resultado << endl;
    return 0;
}

int ejemplo7(){

    int n = 0, suma = 0;

    cout << "Ingrese un numero N: " << endl;
    cin >> n;

    for (int i = 0; i <= n; i++){
        suma = suma + i;
    }

    cout << "El suma desde 0 hasta " << n  << " es :" << suma << endl;
    return 0;
}

int ejemplo8(){

    int n = 0, factorial = 1;

    cout << "Ingrese un numero N: " << endl;
    cin >> n;

    for (int i = 1; i <= n; i++){
        factorial = factorial * i;
    }
    cout << "El resultado de la factorial de: \n" << n << "!=" << factorial << endl;
    return 0;
}

int ejemplo9(){

    float n = 0, PI = 3.1416, perimetro = 0, area = 0;

    cout << "Ingrese un numero N (Radio del circulo): " << endl;
    cin >> n;

    perimetro = 2 * PI * n;
    area = PI * n * n;

    cout << " El perimetro y el area del circulo es : \nPerimetro:" << perimetro << " Area: " << area <<endl;
    return 0;
}

int ejemplo10(){

    int n = 0;

    cout <<"Ingrese el valor de N: ";
    cin >> n;

    cout << "Los multiplos de " << n << " menores de 100: " <<endl;

    for (int i = 1; i <= 100; i++){
        if (i % n == 0){
            cout << i << endl;
        }
    }
    return 0;
}

int ejemplo11(){

    int n = 0;

    cout <<"Ingresa el valor de N: ";
    cin >> n;

    cout <<"La tabla de multiplicar del " << n << ":" << endl;

    for (int i = 1; i <= 10; i++){
        cout << i << "x" << n << "=" << i*n << endl;
    }
    return 0;
}

int ejemplo12(){

    int n = 0, potencia = 0;

    cout <<"Ingresa el valor de N: ";
    cin >> n;

    for (int i = 1; i <= 5; i++){
        potencia = 1;
        for (int j = 1; j <= i; j++){
            potencia = potencia * n;
        }
        cout << n << "^" << i << "=" << potencia << endl;
    }
    return 0;
}

int ejemplo13(){

    int n = 0;

    cout <<"Ingresa el valor de N: ";
    cin >> n;

    cout <<"Los divisores de " << n << " son:" << endl;

    for (int i = 1; i <= n; i++){
        if (n % i == 0){
            cout << i << endl;
        }
    }
    return 0;
}

int ejemplo14(){

    for (int i = 1; i <= 50; i++){
        cout << i << " " << 51 - i << endl;
    }
    return 0;
}

int ejemplo15(){

    int numero = 0, suma = 0;

    do {
        cout << "Ingrese un numero(0 para terminar): ";
        cin >> numero;

        suma = suma + numero;
    } while (numero != 0);

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}

int ejemplo16(){

    int numero = 0, suma = 0, contador = 0;
    float promedio;

    do {
        cout << "Ingrese un numero(0 para terminar): ";
        cin >> numero;

        if (numero != 0) {
            suma = suma + numero;
            contador++;
        }
    } while (numero != 0);

    if (contador > 0){
        promedio = (suma/contador);
        cout << "El promedio es: " << promedio << endl;
    } else{
        cout << "No se ingresaron numeros para calcular el promedio" << endl;
    }
    return 0;
}

int ejemplo17(){

    int numero = 0, max = 0;

    do{
        cout << "Ingrese un numero(0 para terminar): ";
        cin >> numero;

        if (numero != 0){
            if (numero > max){
                max = numero;
            }
        }
    }while (numero != 0);

    if (max != 0){
        cout << "El numero mayor fue: " << max << endl;
    }else{
        cout << "No se ingresaron numeros validos" << endl;
    }
    return 0;
}

int ejemplo18(){

    int n = 0;
    bool esCuadradoPerfecto = false;

    cout << "Ingresa el valor de N: ";
    cin >> n;

    for (int i = 1; i * 1 <= n; i++){
        if (i * i == n){
            esCuadradoPerfecto = true;
            break;
        }
    }

    if (esCuadradoPerfecto){
        cout << n << " es cuadrado perfecto" << endl;
    } else {
        cout << n << " NO es un cuadrado perfecto" << endl;
    }
    return 0;
}

int ejemplo19(){

    int n = 0;
    bool esPrimo = true;

    cout << "Ingresa el valor de N: ";
    cin >> n;

    if (n <= 1) {
        esPrimo = false;
    }else {
        for (int i = 2; i * i <= n; i++){
            if (n % i == 0){
                esPrimo = false;
                break;
            }
        }
    }

    if (esPrimo){
        cout << n << " es un numero primo" << endl;
    }else {
        cout << n << " No es un numero primo" << endl;
    }
    return 0;
}

int ejemplo20(){

    int n = 0, original = 0, invertido = 0, residuo = 0;

    cout << "Ingresa el valor de N: ";
    cin >> n;

    original = n;

    while (n != 0) {
        residuo = n % 10;
        invertido = invertido * 10 + residuo;
        n = n / 10;
    }

    if (original == invertido){
        cout << original << " es un numero palindromo" << endl;
    }else {
        cout << original << " No es un numero palindromo" << endl;
    }
    return 0;
}

int ejemplo21(){

    char c = ' ';

    cout << "Ingresa un caracter: ";
    cin >> c;

    if (c >= 'A' && c <= 'Z'){
        c = c + ('a' - 'A');
        cout << "Letra convertida: " << c << endl;
    }
    else if (c >= 'a' && c <= 'z'){
        c = c - ('a' - 'A');
        cout << "El letra convertida: " << c << endl;
    }
    else {
        cout << "El caracter ingresado no es una letra" << endl;
    }
    return 0;
}

int ejemplo22(){

    int  total_segundos = 0, horas = 0, minutos = 0, segundos = 0;

    cout << "Ingrese la cantidad de segundos: ";
    cin >> total_segundos;

    horas = total_segundos / 3600;
    minutos = (total_segundos % 3600) / 60;
    segundos = total_segundos % 60;

    cout <<"El resultado en formato de horas:minutos:segundos es:" << endl;
    cout << horas << ":" << minutos << ":" << segundos << endl;
    return 0;
}

int ejemplo23(){

    int a = 0, b = 0, mcm = 0;

    cout <<"Ingrese el primer numero A: " << endl;
    cin >> a;

    cout <<"Ingrese el segundo numero B: " << endl;
    cin >> b;

    mcm = (a > b) ? a : b;

    while (true){
        if (mcm % a == 0 && mcm % b == 0){
            cout << "El MCM de " << a << " y " << b << " es: " << mcm << endl;
            break;
        }
        mcm++;
    }
    return 0;
}

int ejemplo24(){

    int n = 0;

    cout <<"Ingresa el numero entero para el formar el cuadrado: ";
    cin >> n;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1){
                cout << "+";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

int ejemplo25(){

    int n = 0, contador = 0;

    cout <<"Ingresa el valor de N: ";
    cin >> n;

    if (n == 0){
        contador = 1;
    } else {
        while(n != 0){
            n = n / 10;
            contador++;
        }
    }
    cout << "El numero tiene " << contador << " digitos." << endl;
    return 0;
}

int ejemplo26(){

    int a = 0, b = 0, c = 0;

    cout <<"Ingresa el valor del lado A: ";
    cin >> a;

    cout <<"Ingresa el valor del lado B: ";
    cin >> b;

    cout <<"Ingresa el valor del lado C: ";
    cin >> c;

    if (a + b > c && a + c > b && b + c > a){
        if (a == b && b == c){
            cout << "Se forma un triangulo equilatero" << endl;
        }else if (a == b || a == c || b == c) {
            cout << "Se forma un triangulo isosceles" << endl;
        }else {
            cout << "Se forma un triangulo escaleno" << endl;
        }
    }else {
        cout << "Las longitudes ingresadas no forman un triangulo" << endl;
    }
    return 0;
}

int ejemplo27(){

    double num1 = 0.0, num2 = 0.0, resultado = 0.0;
    char operacion = ' ';

    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese la operacion (+, -, *, /): ";
    cin >> operacion;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;

    switch (operacion) {
    case '+':
        resultado = num1 + num2;
        cout << num1 << " + " << num2 << " = " << resultado << endl;
        break;
    case '-':
        resultado = num1 - num2;
        cout << num1 << " - " << num2 << " = " << resultado << endl;
        break;
    case '*':
        resultado = num1 * num2;
        cout << num1 << " * " << num2 << " = " << resultado << endl;
        break;
    case '/':
        if (num2 != 0) {
            resultado = num1 / num2;
            cout << num1 << " / " << num2 << " = " << resultado << endl;
        } else {
            cout << "Error: Division por cero no permitida" << endl;
        }
        break;
    default:
        cout << "Operacion no valida" << endl;
    }
    return 0;
}

int ejemplo28(){

    int numTerminos = 0;
    double pi = 0.0;

    cout << "Ingrese el numero de terminos para aproximar pi: ";
    cin >> numTerminos;

    for (int i = 0; i < numTerminos; i++) {
        if (i % 2 == 0) {
            pi += 4.0 / (2 * i + 1);
        } else {
            pi -= 4.0 / (2 * i + 1);
        }
    }
    cout << "El valor aproximado de pi usando " << numTerminos << " terminos es: " << pi << endl;
    return 0;
}

int ejemplo29(){

    int min = 0, max = 100, intento = 0, intentos = 0;
    char respuesta = ' ';

    cout << "Piensa en un numero entre 0 y 100. Voy a intentar adivinarlo" << endl;

    while (true) {
        intento = (min + max) / 2;
        cout << "Es tu numero " << intento << " (Responde con '>', '<' o '='): ";
        cin >> respuesta;

        intentos++;

        if (respuesta == '=') {
            cout << "Adivine Tu numero es " << intento << ". Me tomo " << intentos << " intentos." << endl;
            break;
        } else if (respuesta == '>') {
            min = intento + 1;
        } else if (respuesta == '<') {
            max = intento - 1;
        } else {
            cout << "Entrada no valida. Por favor, usa '>', '<' o '='." << endl;
        }
    }
    return 0;
}

int ejemplo30(){

    srand(time(0));
    //srand(12345);
    int numeroSecreto = rand() % 101, intento = 0, intentos = 0;

    cout << "He generado un numero entre 0 y 100. Intenta adivinarlo" << endl;

    do {
        cout << "Ingresa tu numero: ";
        cin >> intento;
        intentos++;

        if (intento > numeroSecreto) {
            cout << "El numero es menor" << endl;
        } else if (intento < numeroSecreto) {
            cout << "El numero es mayor" << endl;
        } else {
            cout << "Felicidades Adivinaste el numero en " << intentos << " intentos." << endl;
        }
    } while (intento != numeroSecreto);

    return 0;
}

int main() {

    int x = 0;

    while(true){

        cout << "Ingrese el numero del ejercicio: " << endl;
        cin >> x;

        switch (x) {
        case 1 :
            ejemplo1();
            break;

        case 2 :
            ejemplo2();
            break;

        case 3 :
            ejemplo3();
            break;

        case 4 :
            ejemplo4();
            break;

        case 5 :
            ejemplo5();
            break;

        case 6 :
            ejemplo6();
            break;

        case 7 :
            ejemplo7();
            break;

        case 8 :
            ejemplo8();
            break;

        case 9 :
            ejemplo9();
            break;

        case 10:
            ejemplo10();
            break;

        case 11:
            ejemplo11();
            break;

        case 12:
            ejemplo12();
            break;

        case 13:
            ejemplo13();
            break;

        case 14:
            ejemplo14();
            break;

        case 15:
            ejemplo15();
            break;

        case 16:
            ejemplo16();
            break;

        case 17:
            ejemplo17();
            break;

        case 18:
            ejemplo18();
            break;

        case 19:
            ejemplo19();
            break;

        case 20:
            ejemplo20();
            break;

        case 21:
            ejemplo21();
            break;

        case 22:
            ejemplo22();
            break;

        case 23:
            ejemplo23();
            break;

        case 24:
            ejemplo24();
            break;

        case 25:
            ejemplo25();
            break;

        case 26:
            ejemplo26();
            break;

        case 27:
            ejemplo27();
            break;

        case 28:
            ejemplo28();
            break;

        case 29:
            ejemplo29();
            break;

        case 30:
            ejemplo30();
            break;
        }
    }
    return 0;
}
