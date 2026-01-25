// red.cpp
#include "red.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

void Red::agregarEnrutador(const string& nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = Enrutador(nombre);  // Construccion explicita
        cout << "Enrutador " << nombre << " agregado a la red.\n";
    } else {
        cerr << "Error: Enrutador " << nombre << " ya existe.\n";
    }
}

void Red::agregarEnrutadorConAutoConexiones() {
    // Generar nombre automatico secuencial
    string nuevoEnrutador;

    if (enrutadores.empty()) {
        nuevoEnrutador = "A";
    } else {
        // Encontrar el siguiente nombre disponible
        char ultimo = 'A';
        for (const auto& par : enrutadores) {
            if (par.first.size() == 1 && par.first[0] >= ultimo) {
                ultimo = par.first[0] + 1;
            }
        }

        if (ultimo <= 'Z') {
            nuevoEnrutador = string(1, ultimo);
        } else {
            // Si pasamos de Z, usar AA, AB, etc.
            int count = enrutadores.size();
            nuevoEnrutador = "A";
            char second = 'A' + (count % 26);
            nuevoEnrutador += second;
        }
    }

    // Verificar que no exista (por si acaso)
    if (enrutadores.find(nuevoEnrutador) != enrutadores.end()) {
        cerr << "Error: El enrutador generado automaticamente ya existe.\n";
        return;
    }

    // Agregar el nuevo enrutador
    agregarEnrutador(nuevoEnrutador);
    cout << "Enrutador " << nuevoEnrutador << " agregado exitosamente.\n";

    // Si hay otros enrutadores, ofrecer conexiones
    if (enrutadores.size() > 1) {
        bool agregarMasConexiones = true;

        while (agregarMasConexiones) {
            // Mostrar lista numerada de enrutadores disponibles
            cout << "\nEnrutadores disponibles para conectar:\n";
            int index = 1;
            vector<string> enrutadoresDisponibles;

            for (const auto& [nombre, _] : enrutadores) {
                if (nombre != nuevoEnrutador) {
                    cout << index << ". " << nombre << "\n";
                    enrutadoresDisponibles.push_back(nombre);
                    index++;
                }
            }

            cout << "0. Finalizar conexiones\n";
            cout << "Seleccione un enrutador para conectar: ";

            // Leer seleccion del usuario
            int seleccion;
            cin >> seleccion;

            // Validar entrada
            if (seleccion == 0) {
                agregarMasConexiones = false;
                cout << "Finalizando conexiones...\n";
            }
            else if (seleccion < 1 || seleccion > enrutadoresDisponibles.size()) {
                cerr << "Error: Seleccion invalida. Intente nuevamente.\n";
            }
            else {
                string destino = enrutadoresDisponibles[seleccion - 1];
                int costo;

                cout << "Ingrese el costo del enlace entre " << nuevoEnrutador << " y " << destino << ": ";
                cin >> costo;

                if (cin.fail() || costo <= 0) {
                    cerr << "Error: El costo debe ser un numero positivo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    agregarEnlace(nuevoEnrutador, destino, costo);
                    cout << "Enlace agregado exitosamente.\n";
                }
            }
        }
    }

    // Actualizar todo
    calcularTablasEnrutamiento();
    guardarRed("enlaces_red.txt");
    guardarMatrizEnArchivo("matriz_enrutamiento.txt");

    cout << "Red actualizada correctamente.\n";
}

void Red::removerEnrutador() {
    // Mostrar lista de enrutadores disponibles
    if (enrutadores.empty()) {
        cerr << "Error: No hay enrutadores en la red.\n";
        return;
    }

    cout << "\nEnrutadores disponibles para eliminar:\n";
    int index = 1;
    vector<string> enrutadoresLista;

    // Crear lista numerada
    for (const auto& [nombre, _] : enrutadores) {
        cout << index << ". " << nombre << "\n";
        enrutadoresLista.push_back(nombre);
        index++;
    }

    // Opcion para cancelar
    cout << "0. Cancelar\n";
    cout << "Seleccione el enrutador a eliminar: ";

    // Leer seleccion del usuario
    int seleccion;
    cin >> seleccion;

    // Validar entrada
    if (seleccion == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (seleccion < 1 || seleccion > enrutadoresLista.size()) {
        cerr << "Error: Seleccion invalida.\n";
        return;
    }

    // Obtener nombre del enrutador seleccionado
    const string& nombre = enrutadoresLista[seleccion - 1];

    // Confirmar eliminacion
    cout << "Esta seguro que desea eliminar el enrutador " << nombre << "? (s/n): ";
    char confirmacion;
    cin >> confirmacion;

    if (tolower(confirmacion) != 's') {
        cout << "Operacion cancelada.\n";
        return;
    }

    // Proceder con la eliminacion
    if (enrutadores.erase(nombre)) {
        // Eliminar conexiones relacionadas
        for (auto& [_, enrutador] : enrutadores) {
            enrutador.removerConexion(nombre);
        }

        cout << "Enrutador " << nombre << " eliminado exitosamente.\n";

        // Actualizar todo
        calcularTablasEnrutamiento();
        guardarRed("enalaces_red.txt");
        guardarMatrizEnArchivo("matriz_enrutamiento.txt");
    } else {
        cerr << "Error: No se pudo eliminar el enrutador " << nombre << "\n";
    }
}

void Red::AEnlace() {
    // Verificar que hay al menos 2 enrutadores para crear enlaces
    if (enrutadores.size() < 2) {
        cerr << "Error: Se necesitan al menos 2 enrutadores para crear enlaces.\n";
        return;
    }

    bool agregarMasEnlaces = true;

    while (agregarMasEnlaces) {
        // Mostrar lista numerada de enrutadores disponibles para origen
        cout << "\nSeleccione el enrutador ORIGEN:\n";
        int index = 1;
        vector<string> enrutadoresLista;

        for (const auto& [nombre, _] : enrutadores) {
            cout << index << ". " << nombre << "\n";
            enrutadoresLista.push_back(nombre);
            index++;
        }

        cout << "0. Finalizar\n";
        cout << "Seleccione una opcion: ";

        // Leer seleccion del usuario para origen
        int seleccionOrigen;
        cin >> seleccionOrigen;

        // Validar entrada
        if (seleccionOrigen == 0) {
            agregarMasEnlaces = false;
            cout << "Finalizando...\n";
            break;
        }
        else if (seleccionOrigen < 1 || seleccionOrigen > enrutadoresLista.size()) {
            cerr << "Error: Seleccion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string origen = enrutadoresLista[seleccionOrigen - 1];

        // Mostrar lista numerada de enrutadores disponibles para destino (excluyendo el origen)
        cout << "\nSeleccione el enrutador DESTINO:\n";
        index = 1;
        vector<string> destinosDisponibles;

        for (const auto& [nombre, _] : enrutadores) {
            if (nombre != origen) {
                cout << index << ". " << nombre << "\n";
                destinosDisponibles.push_back(nombre);
                index++;
            }
        }

        cout << "0. Cancelar\n";
        cout << "Seleccione una opcion: ";

        // Leer seleccion del usuario para destino
        int seleccionDestino;
        cin >> seleccionDestino;

        // Validar entrada
        if (seleccionDestino == 0) {
            cout << "Operacion cancelada.\n";
            continue;
        }
        else if (seleccionDestino < 1 || seleccionDestino > destinosDisponibles.size()) {
            cerr << "Error: Seleccion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string destino = destinosDisponibles[seleccionDestino - 1];

        // Solicitar costo del enlace
        int costo;
        cout << "Ingrese el costo del enlace entre " << origen << " y " << destino << ": ";
        cin >> costo;

        if (cin.fail() || costo <= 0) {
            cerr << "Error: El costo debe ser un numero positivo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Agregar el enlace
        agregarEnlace(origen, destino, costo);
        cout << "Enlace agregado exitosamente.\n";

        // Preguntar si desea agregar mas enlaces
        char respuesta;
        cout << "\nDesea agregar otro enlace? (s/n): ";
        cin >> respuesta;

        if (respuesta != 's' && respuesta != 'S') {
            agregarMasEnlaces = false;
        }
    }

    // Actualizar todo
    calcularTablasEnrutamiento();
    guardarRed("enlaces_red.txt");
    guardarMatrizEnArchivo("matriz_enrutamiento.txt");

    cout << "Red actualizada correctamente.\n";
}

void Red::REnlace() {
    // Verificar que hay al menos 1 enlace en la red
    bool existenEnlaces = false;
    for (const auto& [origen, enrutador] : enrutadores) {
        if (!enrutador.obtenerConexiones().empty()) {
            existenEnlaces = true;
            break;
        }
    }

    if (!existenEnlaces) {
        cerr << "Error: No hay enlaces en la red para eliminar.\n";
        return;
    }

    bool eliminarMasEnlaces = true;

    while (eliminarMasEnlaces) {
        // Mostrar lista numerada de todos los enlaces existentes
        cout << "\nEnlaces existentes en la red:\n";
        int index = 1;
        vector<pair<string, string>> listaEnlaces;

        // Recorrer todos los enrutadores y sus conexiones
        for (const auto& [origen, enrutador] : enrutadores) {
            for (const auto& [destino, costo] : enrutador.obtenerConexiones()) {
                // Evitar mostrar duplicados (A-B y B-A)
                bool yaListado = false;
                for (const auto& enlace : listaEnlaces) {
                    if ((enlace.first == destino && enlace.second == origen)) {
                        yaListado = true;
                        break;
                    }
                }

                if (!yaListado) {
                    cout << index << ". " << origen << " <-> " << destino
                              << " (Costo: " << costo << ")\n";
                    listaEnlaces.emplace_back(origen, destino);
                    index++;
                }
            }
        }

        cout << "0. Finalizar\n";
        cout << "Seleccione el enlace a eliminar: ";

        // Leer seleccion del usuario
        int seleccion;
        cin >> seleccion;

        // Validar entrada
        if (seleccion == 0) {
            eliminarMasEnlaces = false;
            cout << "Finalizando...\n";
            break;
        }
        else if (seleccion < 1 || seleccion > listaEnlaces.size()) {
            cerr << "Error: Seleccion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Obtener el enlace seleccionado
        auto enlaceAEliminar = listaEnlaces[seleccion - 1];
        string origen = enlaceAEliminar.first;
        string destino = enlaceAEliminar.second;

        // Eliminar el enlace en ambas direcciones
        if (enrutadores.count(origen) && enrutadores.count(destino)) {
            enrutadores.at(origen).removerConexion(destino);
            enrutadores.at(destino).removerConexion(origen);
            cout << "Enlace entre " << origen << " y " << destino << " eliminado exitosamente.\n";
        } else {
            cerr << "Error: Uno de los enrutadores del enlace ya no existe.\n";
        }

        // Preguntar si desea eliminar mas enlaces
        char respuesta;
        cout << "\n¿Desea eliminar otro enlace? (s/n): ";
        cin >> respuesta;

        if (respuesta != 's' && respuesta != 'S') {
            eliminarMasEnlaces = false;
        }
    }

    // Actualizar todo
    calcularTablasEnrutamiento();
    guardarRed("enlaces_red.txt");
    guardarMatrizEnArchivo("matriz_enrutamiento.txt");

    cout << "Red actualizada correctamente.\n";
}

void Red::consultarCostoEnvio() const {
    if (enrutadores.empty()) {
        cerr << "Error: No hay enrutadores en la red.\n";
        return;
    }

    // Mostrar lista de enrutadores origen
    cout << "\nSeleccione el enrutador de origen:\n";
    int index = 1;
    vector<string> listaEnrutadores;

    for (const auto& [nombre, _] : enrutadores) {
        cout << index << ". " << nombre << "\n";
        listaEnrutadores.push_back(nombre);
        index++;
    }

    cout << "0. Cancelar\n";
    cout << "Seleccione una opcion: ";

    int seleccionOrigen;
    cin >> seleccionOrigen;

    if (seleccionOrigen == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (seleccionOrigen < 1 || seleccionOrigen > listaEnrutadores.size()) {
        cerr << "Error: Seleccion invalida.\n";
        return;
    }

    string origen = listaEnrutadores[seleccionOrigen - 1];

    // Mostrar lista de enrutadores destino (excluyendo el origen)
    cout << "\nSeleccione el enrutador de destino (0 para cancelar):\n";
    index = 1;
    vector<string> listaDestinos;

    for (const auto& [nombre, _] : enrutadores) {
        if (nombre != origen) {
            cout << index << ". " << nombre << "\n";
            listaDestinos.push_back(nombre);
            index++;
        }
    }

    cout << "0. Cancelar\n";
    cout << "Seleccione una opcion: ";

    int seleccionDestino;
    cin >> seleccionDestino;

    if (seleccionDestino == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (seleccionDestino < 1 || seleccionDestino > listaDestinos.size()) {
        cerr << "Error: Seleccion invalida.\n";
        return;
    }

    string destino = listaDestinos[seleccionDestino - 1];

    const auto& tabla = enrutadores.at(origen).obtenerTabla();
    auto it = tabla.find(destino);

    if (it != tabla.end()) {
        cout << "\nEl costo de envio desde " << origen << " hasta " << destino
             << " es: " << it->second << "\n";
    } else {
        cout << "\nNo existe ruta disponible desde " << origen << " hasta " << destino << ".\n";
    }
}

void Red::consultarCaminoOptimo() const {
    if (enrutadores.empty()) {
        cerr << "Error: No hay enrutadores en la red.\n";
        return;
    }

    // Mostrar lista de enrutadores origen
    cout << "\nSeleccione el enrutador de origen:\n";
    int index = 1;
    vector<string> listaEnrutadores;

    for (const auto& [nombre, _] : enrutadores) {
        cout << index << ". " << nombre << "\n";
        listaEnrutadores.push_back(nombre);
        index++;
    }

    cout << "0. Cancelar\n";
    cout << "Seleccione una opcion: ";

    int seleccionOrigen;
    cin >> seleccionOrigen;

    if (seleccionOrigen == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (seleccionOrigen < 1 || seleccionOrigen > listaEnrutadores.size()) {
        cerr << "Error: Seleccion invalida.\n";
        return;
    }

    string origen = listaEnrutadores[seleccionOrigen - 1];

    // Mostrar lista de enrutadores destino (excluyendo el origen)
    cout << "\nSeleccione el enrutador de destino (0 para cancelar):\n";
    index = 1;
    vector<string> listaDestinos;

    for (const auto& [nombre, _] : enrutadores) {
        if (nombre != origen) {
            cout << index << ". " << nombre << "\n";
            listaDestinos.push_back(nombre);
            index++;
        }
    }

    cout << "0. Cancelar\n";
    cout << "Seleccione una opcion: ";

    int seleccionDestino;
    cin >> seleccionDestino;

    if (seleccionDestino == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (seleccionDestino < 1 || seleccionDestino > listaDestinos.size()) {
        cerr << "Error: Seleccion invalida.\n";
        return;
    }

    string destino = listaDestinos[seleccionDestino - 1];

    // Calcular camino optimo
    const int INF = numeric_limits<int>::max();
    map<string, int> dist;
    map<string, string> prev;
    set<pair<int, string>> cola;

    // Inicializacion
    for (const auto& [nombre, _] : enrutadores) {
        dist[nombre] = INF;
    }
    dist[origen] = 0;
    cola.insert({0, origen});

    // Algoritmo Dijkstra
    while (!cola.empty()) {
        auto [d, u] = *cola.begin();
        cola.erase(cola.begin());

        const auto& conexiones = enrutadores.at(u).obtenerConexiones();
        for (const auto& [v, costo] : conexiones) {
            if (dist[u] + costo < dist[v]) {
                cola.erase({dist[v], v});
                dist[v] = dist[u] + costo;
                prev[v] = u;
                cola.insert({dist[v], v});
            }
        }
    }

    // Reconstruir camino
    if (dist[destino] == INF) {
        cout << "\nNo existe ruta disponible desde " << origen << " hasta " << destino << ".\n";
        return;
    }

    vector<string> camino;
    for (string at = destino; at != ""; at = prev.count(at) ? prev[at] : "") {
        camino.push_back(at);
    }
    reverse(camino.begin(), camino.end());

    // Mostrar resultados
    cout << "\nCamino optimo desde " << origen << " hasta " << destino << ":\n";
    cout << "Costo total: " << dist[destino] << endl;
    cout << "Ruta: ";

    for (size_t i = 0; i < camino.size(); ++i) {
        if (i != 0) cout << " -> ";
        cout << camino[i];
    }
    cout << endl;
}

void Red::generarRedAleatoria(int cantidadEnrutadores, int maxCosto, const string& archivoRespaldo) {
    // Limpiar enrutadores existentes
    enrutadores.clear();

    // Validar parametros
    if (cantidadEnrutadores < 2) {
        cerr << "Error: La red debe tener al menos 2 enrutadores.\n";
        return;
    }

    if (maxCosto <= 0) {
        cerr << "Error: El costo maximo debe ser positivo.\n";
        return;
    }

    // Inicializar semilla aleatoria
    srand(static_cast<unsigned int>(time(nullptr)));

    // Crear enrutadores con identificadores A, B, ..., Z, AA, AB, ...
    vector<string> ids;
    for (int i = 0; i < cantidadEnrutadores; ++i) {
        string id;
        if (i < 26) {
            id = string(1, 'A' + i);
        } else {
            id = string(1, 'A' + (i / 26 - 1)) + string(1, 'A' + (i % 26));
        }
        agregarEnrutador(id);
        ids.push_back(id);  // Guardamos los nombres para facil acceso
    }

    // Asegurar conectividad minima (cada enrutador debe estar conectado al menos a uno anterior)
    for (int i = 1; i < cantidadEnrutadores; ++i) {
        int enrutadorAnterior = rand() % i;
        int costo = rand() % maxCosto + 1;
        agregarEnlace(ids[enrutadorAnterior], ids[i], costo);
    }

    // Conexiones adicionales aleatorias
    int conexionesAdicionales = static_cast<int>(cantidadEnrutadores * 1.5);
    for (int i = 0; i < conexionesAdicionales; ++i) {
        int origenIdx = rand() % cantidadEnrutadores;
        int destinoIdx = rand() % cantidadEnrutadores;

        if (origenIdx != destinoIdx) {
            const string& origen = ids[origenIdx];
            const string& destino = ids[destinoIdx];

            if (enrutadores[origen].obtenerConexiones().count(destino) == 0) {
                int costo = rand() % maxCosto + 1;
                agregarEnlace(origen, destino, costo);
            }
        }
    }

    // Calcular tablas de enrutamiento y respaldar informacion
    calcularTablasEnrutamiento();
    guardarRed(archivoRespaldo);
    guardarMatrizEnArchivo("matriz_enrutamiento_respaldo.txt");

    cout << "Red generada y respaldada correctamente.\n";
}

void Red::guardarRed(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    // 1. Escribe enrutadores
    bool first = true;
    for (const auto& [nombre, _] : enrutadores) {
        if (!first) archivo << ",";
        archivo << nombre;
        first = false;
    }
    archivo << "\n";

    // 2. Escribe conexiones evitando duplicados
    set<pair<string, string>> conexionesGuardadas;

    for (const auto& [origen, enrutador] : enrutadores) {
        for (const auto& [destino, costo] : enrutador.obtenerConexiones()) {
            // Verificar si la conexion inversa ya fue guardada
            if (conexionesGuardadas.find({destino, origen}) == conexionesGuardadas.end()) {
                archivo << origen << "->" << destino << ":" << origen << "-" << destino << ";" << costo << "\n";
                conexionesGuardadas.insert({origen, destino});
            }
        }
    }

    archivo.close();
    cout << "Red guardada correctamente en " << nombreArchivo << endl;
}


void Red::agregarEnlace(const string& origen, const string& destino, int costo) {
    if (origen == destino) return;

    // Verificar existencia primero
    if (enrutadores.count(origen) == 0 || enrutadores.count(destino) == 0) {
        cerr << "Error: Enrutador no existe.\n";
        return;
    }

    // Acceder directamente ya que sabemos que existen
    enrutadores.at(origen).agregarConexion(destino, costo);
    enrutadores.at(destino).agregarConexion(origen, costo);

    cout << "Enlace agregado entre " << origen << " y " << destino
              << " con costo " << costo << ".\n";
}

void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    // Leer primera linea con los enrutadores
    string linea;
    if (getline(archivo, linea)) {
        istringstream ss(linea);
        string enrutador;

        while (getline(ss, enrutador, ',')) {
            // Limpiar espacios en blanco
            enrutador.erase(remove_if(enrutador.begin(), enrutador.end(), ::isspace), enrutador.end());
            if (!enrutador.empty()) {
                agregarEnrutador(enrutador);
            }
        }
    }

    // Leer el resto de las lineas con los enlaces
    while (getline(archivo, linea)) {
        // Dividir la linea en partes
        size_t separadorFlecha = linea.find("->");
        size_t separadorDosPuntos = linea.find(":");
        size_t separadorPuntoComa = linea.find(";");

        if (separadorFlecha == string::npos ||
            separadorDosPuntos == string::npos ||
            separadorPuntoComa == string::npos) {
            continue;
        }

        string origen = linea.substr(0, separadorFlecha);
        string destino = linea.substr(separadorFlecha + 2, separadorDosPuntos - (separadorFlecha + 2));
        string camino = linea.substr(separadorDosPuntos + 1, separadorPuntoComa - (separadorDosPuntos + 1));
        int costo = stoi(linea.substr(separadorPuntoComa + 1));

        // Solo procesar enlaces directos (formato "A-B" o "A->B:A-B;costo")
        if (camino == (origen + "-" + destino)) {
            agregarEnlace(origen, destino, costo);
        }
    }

    archivo.close();
}

void Red::dijkstra(const string& origen) {
    const int INF = numeric_limits<int>::max();
    map<string, int> dist;
    map<string, string> prev;
    set<pair<int, string>> cola;

    // Inicializacion
    for (const auto& [nombre, _] : enrutadores) {
        dist[nombre] = INF;
    }
    dist[origen] = 0;
    cola.insert({0, origen});

    while (!cola.empty()) {
        auto [d, u] = *cola.begin();
        cola.erase(cola.begin());

        // Obtener conexiones desde el enrutador
        const auto& conexiones = enrutadores.at(u).obtenerConexiones();

        for (const auto& [v, costo] : conexiones) {
            if (dist[u] + costo < dist[v]) {
                cola.erase({dist[v], v});
                dist[v] = dist[u] + costo;
                prev[v] = u;
                cola.insert({dist[v], v});
            }
        }
    }

    // Actualizar tabla de enrutamiento
    enrutadores.at(origen).limpiarTabla();
    for (const auto& [destino, costo] : dist) {
        if (destino != origen && costo < INF) {
            enrutadores.at(origen).actualizarTabla(destino, costo);
        }
    }
}

void Red::calcularTablasEnrutamiento() {
    for (const auto& [nombre, _] : enrutadores) {
        dijkstra(nombre);
    }
}

void Red::mostrarTablas() const {
    cout << "\nTabla de Enrutamiento (Matriz de Costos):\n\t";
    // Encabezado
    for (const auto& [nombre, _] : enrutadores) {
        cout << nombre << '\t';
    }
    cout << '\n';

    // Filas
    for (const auto& [nombreOrigen, enrutador] : enrutadores) {
        cout << nombreOrigen << '\t';
        for (const auto& [nombreDestino, _] : enrutadores) {
            if (nombreOrigen == nombreDestino) {
                cout << "0\t";
            } else {
                const auto& tabla = enrutador.obtenerTabla();
                auto it = tabla.find(nombreDestino);
                if (it != tabla.end()) {
                    cout << it->second << '\t';
                } else {
                    cout << "-\t";
                }
            }
        }
        cout << '\n';
    }
}

void Red::guardarMatrizEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    // Encabezado con los nombres de los enrutadores
    archivo << "0\t";
    for (const auto& [nombre, _] : enrutadores) {
        archivo << nombre << '\t';
    }
    archivo << '\n';

    // Filas con los costos
    for (const auto& [nombreOrigen, enrutador] : enrutadores) {
        archivo << nombreOrigen << '\t';

        for (const auto& [nombreDestino, _] : enrutadores) {
            if (nombreOrigen == nombreDestino) {
                archivo << "0\t";  // Costo a si mismo siempre es 0
            } else {
                const auto& tabla = enrutador.obtenerTabla();
                auto it = tabla.find(nombreDestino);
                archivo << (it != tabla.end() ? to_string(it->second) : "-") << '\t';
            }
        }
        archivo << '\n';
    }

    archivo.close();
    cout << "\nMatriz de enrutamiento actualizada y guardada en " << nombreArchivo << endl;
}
