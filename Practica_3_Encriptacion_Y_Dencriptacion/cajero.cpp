#include "cajero.h"
#include "metodos.h"
#include "auxiliares.h"
#include "procesamiento.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

bool validarAccesoAdministrador() {
    // Solicitar clave al usuario
    string password;
    cout << "Ingrese la clave de administrador: ";
    getline(cin, password);

    // Leer la password encriptada del archivo
    string nombreArchivo = "sudo.txt";
    string passwordEncriptada = leerArchivo(nombreArchivo);

    // Eliminar posibles saltos de linea del archivo
    passwordEncriptada.erase(remove(passwordEncriptada.begin(), passwordEncriptada.end(), '\n'), passwordEncriptada.end());

    if (passwordEncriptada.empty()) {
        cerr << "Error: No se pudo leer la clave encriptada o el archivo esta vacio." << endl;
        return false;
    }

    // Desencriptar la password almacenada
    string passwordAlmacenada = desencriptar(passwordEncriptada, password);

    // Comparar las contraseñas
    if (!passwordAlmacenada.empty() && password == passwordAlmacenada) {
        cout << "Acceso concedido como administrador." << endl;
        return true;
    } else {
        cout << "Acceso denegado, clave incorrecta." << endl;
        return false;
    }
}
void cambiarClaveAdministrador() {
    // Limpiar el buffer de entrada primero
    cin.ignore(1000, '\n');

    string nuevaClave;
    bool claveValida = false;

    while (!claveValida) {
        cout << "\n--- CAMBIO DE CLAVE ADMINISTRADOR ---\n";
        cout << "Ingrese la nueva clave: ";
        getline(cin, nuevaClave);

        if (nuevaClave.empty()) {
            cout << "Error: La clave no puede estar vacia.\n";
        } else {
            claveValida = true;
        }
    }

    // Eliminar archivo existente
    remove("sudo.txt");

    // Encriptar y guardar nueva clave
    encriptar(nuevaClave, "sudo.txt");

    cout << "Clave administrativa actualizada con exito.\n";
}

void registrarUsuario() {
    Usuario nuevo;
    string nombreArchivo = "usuarios.txt";

    cout << "\nREGISTRO DE NUEVO USUARIO\n";

    // Validacion y registro de cedula
    bool cedulaValida = false;
    while (!cedulaValida) {
        try {
            cout << "Ingrese la cedula (10 digitos): ";
            cin >> nuevo.cedula;

            if (nuevo.cedula.length() != 10) {
                throw invalid_argument("La cedula debe tener exactamente 10 digitos.");
            }

            if (!esNumerico(nuevo.cedula)) {
                throw invalid_argument("La cedula solo puede contener numeros.");
            }

            if (BuscarUsuario(nuevo.cedula)) {
                throw invalid_argument("La cedula ya esta registrada.");
            }

            // Encriptar y guardar inmediatamente
            encriptar(nuevo.cedula, nombreArchivo);
            cedulaValida = true;

        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Validacion y registro de clave
    bool claveValida = false;
    while (!claveValida) {
        try {
            cout << "Ingrese la clave (4 digitos): ";
            cin >> nuevo.clave;

            if (nuevo.clave.length() != 4) {
                throw invalid_argument("La clave debe tener exactamente 4 digitos.");
            }

            if (!esNumerico(nuevo.clave)) {
                throw invalid_argument("La clave solo puede contener numeros.");
            }

            // Encriptar y guardar inmediatamente
            encriptar(nuevo.clave, nombreArchivo);
            claveValida = true;

        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Validacion y registro de saldo
    bool saldoValido = false;
    while (!saldoValido) {
        try {
            cout << "Ingrese el saldo inicial (COP, use - para deudas): ";
            if (!(cin >> nuevo.saldo)) {
                throw invalid_argument("Debe ingresar un valor numerico valido.");
            }

            // Formatear el saldo con 2 decimales
            ostringstream oss;
            oss << fixed << setprecision(2);
            oss << nuevo.saldo;
            string saldoFormateado = oss.str();

            // Encriptar y guardar inmediatamente
            // Encriptar y guardar con simbolo $ identificador
            string saldoStr = "$" + saldoFormateado;
            encriptar(saldoStr, nombreArchivo);
            saldoValido = true;

        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << "Usuario registrado exitosamente!\n";
}

bool BuscarUsuario(const string& usuarioBuscar) {
    string nombreArchivo = "usuarios.txt";
    string contenido = leerArchivo(nombreArchivo);

    istringstream stream(contenido);
    string lineausuario, lineaClave, lineaSaldo;

    while (getline(stream, lineausuario)) {
        // Intentar desencriptar el usuario actual
        string usuarioDesencriptado = desencriptar(lineausuario, usuarioBuscar);

        if (usuarioDesencriptado == usuarioBuscar) {
            return true;  // Usuario encontrado
        }

        // Saltar las siguientes dos lineas (clave y saldo)
        if (!getline(stream, lineaClave) || !getline(stream, lineaSaldo)) {
            cerr << "Error: archivo incompleto." << endl;
            break;
        }
    }

    return false;  // Usuario no encontrado
}

bool usuarioExistente(const string& usuarioBuscar, Usuario& DatosUsuario) {

    string nombreArchivo = "usuarios.txt";
    string contenido = leerArchivo(nombreArchivo);

    istringstream stream(contenido);
    string lineausuario, lineaClave, lineaSaldo;

    while (getline(stream, lineausuario)) {
        //cout << "\n";
        //cout << "Usuario: " << lineausuario << endl;

        if (!getline(stream, lineaClave)) {
            cerr << "Error: archivo incompleto, falta clave para el usuario." << endl;
            break;
        }
        //cout << "Clave: " << lineaClave << endl;

        if (!getline(stream, lineaSaldo)) {
            cerr << "Error: archivo incompleto, falta saldo para el usuario." << endl;
            break;
        }
        //cout << "Saldo: " << lineaSaldo << endl;

        // Separador para mejor legibilidad
        //cout << "---------------------" << endl;

        string usuarioDesencriptado = desencriptar(lineausuario, usuarioBuscar);

        //cout << usuarioDesencriptado << " / " << usuarioBuscar << endl;

        if (usuarioDesencriptado == usuarioBuscar) {
            string claveDesencriptada = desencriptarAutoNumerico(lineaClave);
            string saldoDesencriptado = desencriptarAutoNumerico(lineaSaldo);

            // cout << "Usuario: " << usuarioDesencriptado << endl;
            // cout << "Clave: " << claveDesencriptada << endl;
            // cout << "Saldo: $" << saldoDesencriptado << endl;

            if (!claveDesencriptada.empty() && !saldoDesencriptado.empty()) {
                DatosUsuario.cedula = usuarioDesencriptado;
                DatosUsuario.clave = claveDesencriptada;
                DatosUsuario.saldo = stof(saldoDesencriptado);
                return true;
            }
        }
    }
    return false;
}

void consultarSaldo(const Usuario& DatosUsuario) {
    cout << "Su saldo actual es: $" << fixed << setprecision(2)
    << DatosUsuario.saldo << " COP\n";
}

void retirarDinero(Usuario& DatosUsuario) {
    const double COSTO_TRANSACCION = 1000.0;

    try {
        // Solicitar monto a retirar
        cout << "\nRETIRO DE DINERO\n";
        cout << "Saldo disponible: $" << fixed << setprecision(2) << DatosUsuario.saldo << " COP\n";
        cout << "Costo por transaccion: $" << COSTO_TRANSACCION << " COP\n";
        cout << "Ingrese el monto a retirar: $";

        double monto;
        if (!(cin >> monto)) {
            throw runtime_error("Entrada invalida. Debe ingresar un valor numerico.");
        }

        // Validar monto positivo
        if (monto <= 0) {
            throw invalid_argument("El monto debe ser mayor a cero.");
        }

        // Calcular total a descontar (monto + costo)
        double totalDescuento = monto + COSTO_TRANSACCION;

        // Verificar fondos suficientes
        if (DatosUsuario.saldo < totalDescuento) {
            ostringstream errorMsg;
            errorMsg << "Fondos insuficientes. Necesita $" << totalDescuento << " (incluye costo de transaccion).";
            throw runtime_error(errorMsg.str());
        }

        // Realizar el retiro
        DatosUsuario.saldo -= totalDescuento;

        // Actualizar archivo
        if (!actualizarUsuario(DatosUsuario)) {
            throw runtime_error("Error al actualizar los datos. El retiro no se completo.");
        }

        registrarTransaccion(DatosUsuario.cedula, monto, DatosUsuario.saldo);

        // Mostrar confirmacion
        cout << "\nRETIRO EXITOSO\n";
        cout << "Monto retirado: $" << monto << " COP\n";
        cout << "Costo de transaccion: $" << COSTO_TRANSACCION << " COP\n";
        cout << "Nuevo saldo: $" << DatosUsuario.saldo << " COP\n";

    } catch (const invalid_argument& e) {
        cerr << "\nERROR: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    } catch (const runtime_error& e) {
        cerr << "\nERROR: " << e.what() << endl;
    } catch (...) {
        cerr << "\nERROR inesperado durante el retiro." << endl;
    }
}

bool actualizarUsuario(const Usuario& DatosUsuario) {
    string nombreArchivo = "usuarios.txt";
    string tempFile = "temp_usuarios.txt";

    try {
        ifstream archivoOriginal(nombreArchivo);
        ofstream archivoTemp(tempFile);

        if (!archivoOriginal.is_open() || !archivoTemp.is_open()) {
            throw runtime_error("No se pudo abrir los archivos necesarios.");
        }

        string lineausuario, lineaClave, lineaSaldo;
        bool usuarioEncontrado = false;

        while (getline(archivoOriginal, lineausuario)) {
            if (!getline(archivoOriginal, lineaClave) || !getline(archivoOriginal, lineaSaldo)) {
                cerr << "Advertencia: Formato de archivo incorrecto." << endl;
                continue;
            }

            string usuarioDesencriptado = desencriptar(lineausuario, DatosUsuario.cedula);

            if (usuarioDesencriptado == DatosUsuario.cedula) {
                // Escribir datos actualizados encriptados
                archivoTemp << encriptar(DatosUsuario.cedula, "") << endl;
                archivoTemp << encriptar(DatosUsuario.clave, "") << endl;
                archivoTemp << encriptar(to_string(DatosUsuario.saldo), "") << endl;
                usuarioEncontrado = true;
            } else {
                // Conservar datos sin cambios
                archivoTemp << lineausuario << endl;
                archivoTemp << lineaClave << endl;
                archivoTemp << lineaSaldo << endl;
            }
        }

        archivoOriginal.close();
        archivoTemp.close();

        if (!usuarioEncontrado) {
            remove(tempFile.c_str());
            throw runtime_error("Usuario no encontrado en archivo.");
        }

        // Reemplazar archivo original
        if (remove(nombreArchivo.c_str()) != 0 || rename(tempFile.c_str(), nombreArchivo.c_str()) != 0) {
            throw runtime_error("Error al actualizar archivo de usuarios.");
        }

        return true;

    } catch (const exception& e) {
        cerr << "Error al actualizar usuario: " << e.what() << endl;
        return false;
    }
}

// funcion auxiliar registrar transacciones
void registrarTransaccion(const string& cedula, double monto, double saldoRestante) {
    string nombreArchivo = "historial_" + cedula + ".txt";
    ofstream archivo(nombreArchivo, ios::app); // Modo append

    if (archivo.is_open()) {
        // Obtener fecha y hora actual
        time_t ahora = time(nullptr);
        tm* tiempoLocal = localtime(&ahora);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tiempoLocal);
        string fechaHora(buffer);

        // Generar ID de transaccion unico (timestamp + random)
        srand(time(nullptr));
        string idTransaccion = to_string(ahora) + "_" + to_string(rand() % 1000);

        // Formatear valores con precision
        string saldoInicialStr = "$" + to_string(saldoRestante + monto + 1000);
        string montoStr = "$" + to_string(monto);
        string costoStr = "$1000.00";
        string saldoFinalStr = "$" + to_string(saldoRestante);

        // Guardar en archivo con formato
        archivo << "ID: " << idTransaccion << endl;
        archivo << "Saldo inicial: " << encriptar(saldoInicialStr, cedula) << endl;
        archivo << "Retiro: " << encriptar(montoStr, cedula) << endl;
        archivo << "Costo transaccion: " << encriptar(costoStr, cedula) << endl;
        archivo << "Saldo final: " << encriptar(saldoFinalStr, cedula) << endl;
        archivo << "Fecha: " << fechaHora << endl;
        archivo << "---" << endl; // Separador entre transacciones

        archivo.close();
    } else {
        cerr << "Error al registrar la transaccion en el historial." << endl;
    }
}

//funcion para consultar historial
void consultarHistorial(const Usuario& DatosUsuario) {
    string nombreArchivo = "historial_" + DatosUsuario.cedula + ".txt";

    try {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw runtime_error("No se encontro historial de transacciones.");
        }

        cout << "\nHISTORIAL DE TRANSACCIONES\n";
        cout << "---------------------------\n";

        string linea;
        int numTransaccion = 1;
        bool tieneTransacciones = false;
        bool nuevaTransaccion = true;
        string idTransaccion;

        while (getline(archivo, linea)) {
            if (linea == "---") {
                // Fin de transaccion
                cout << "---------------------------" << endl;
                numTransaccion++;
                nuevaTransaccion = true;
                continue;
            }

            size_t pos = linea.find(": ");
            if (pos != string::npos) {
                string tipo = linea.substr(0, pos + 2);
                string valor = linea.substr(pos + 2);

                if (nuevaTransaccion) {
                    // Es la primera linea de una nueva transaccion (el ID)
                    if (tipo == "ID: ") {
                        idTransaccion = valor;
                        cout << numTransaccion << ". Transaccion ID: " << idTransaccion << endl;
                        nuevaTransaccion = false;
                        tieneTransacciones = true;
                        continue;
                    }
                }

                // Procesar valores numericos (solo los que necesitan formato monetario)
                if (tipo.find("Saldo") != string::npos ||
                    tipo.find("Retiro") != string::npos ||
                    tipo.find("Costo") != string::npos) {
                    valor = desencriptarAutoNumerico(valor);

                    try {
                        double valorNumerico = stod(valor);
                        // Formatear con 2 decimales, $ y COP
                        ostringstream oss;
                        oss << fixed << setprecision(2) << "$" << valorNumerico << " COP";
                        valor = oss.str();
                    } catch (...) {
                        // Si hay error en la conversion, mostrar el valor original
                    }
                }
                // La fecha se muestra tal cual sin formateo numerico

                cout << "   " << tipo << valor << endl;
            }
        }

        if (!tieneTransacciones) {
            cout << "No hay transacciones registradas.\n";
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Error al consultar historial: " << e.what() << endl;
    }
}

void menuUsuario(Usuario& DatosUsuario) {
    string claveIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "Ingrese su clave (" << intentos << " intentos restantes): ";
        cin >> claveIngresada;

        if (claveIngresada == DatosUsuario.clave) {
            // Aplicar costo de acceso
            DatosUsuario.saldo -= 1000;
            actualizarUsuario(DatosUsuario);

            int opcionUsuario;
            do {
                opcionUsuario = mostrarMenuUsuario();

                switch (opcionUsuario) {
                case 1: consultarSaldo(DatosUsuario); break;
                case 2: retirarDinero(DatosUsuario); break;
                case 3: consultarHistorial(DatosUsuario); break;
                case 4: cout << "Saliendo...\n"; break;
                default: cerr << "Opcion invalida.\n";
                }
            } while (opcionUsuario != 3);
            return;
        } else {
            intentos--;
            if (intentos > 0) {
                cerr << "Clave incorrecta. Intente nuevamente.\n";
            }
        }
    }
    cerr << "Demasiados intentos fallidos. Acceso denegado.\n";
}
