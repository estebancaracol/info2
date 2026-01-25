#include "Escena.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "VentanaPersonalizada.h"
#include "VentanaRecords.h"
#include "SistemaRecords.h"

#include <QRandomGenerator>
#include <QCoreApplication>
#include <QApplication>
#include <QTimer>

Escena::Escena(QObject *parent) : QGraphicsScene(parent), puerta(nullptr), puertaVisible(false) {
    setSceneRect(0, 0, 920, 570);
    inicializarPanelInfo();
    inicializarEstadoDelJuego();
    configurarTemporizador();
}

void Escena::sumarPuntos(int cantidad) {
    puntuacion += cantidad;
    qDebug() << "[DEBUG] Sumar puntos:" << cantidad << "Total:" << puntuacion;
    if (panelInfo) panelInfo->actualizarPuntuacion(puntuacion);

    mostrarTextoTemporal(QString("+%1 puntos").arg(cantidad), 1000);
}

void Escena::crearMapa() {
    int DimensionBloque = 40;
    int alturaPanelInfo = 50;
    int anchoEscena = 920;
    int altoEscena = 570;

    setSceneRect(0, 0, anchoEscena, altoEscena);
    setBackgroundBrush(QBrush(Qt::darkGreen));

    int columnas = anchoEscena / DimensionBloque;
    int filas = (altoEscena - alturaPanelInfo) / DimensionBloque;

    // Crear paredes del borde
    for (int x = 0; x < columnas; ++x) {
        Pared *paredSuperior = new Pared();
        paredSuperior->setPos(x * DimensionBloque, alturaPanelInfo);
        addItem(paredSuperior);

        Pared *paredInferior = new Pared();
        paredInferior->setPos(x * DimensionBloque, altoEscena - DimensionBloque);
        addItem(paredInferior);
    }

    for (int y = 1; y < filas - 1; ++y) {
        Pared *paredIzquierda = new Pared();
        paredIzquierda->setPos(0, alturaPanelInfo + y * DimensionBloque);
        addItem(paredIzquierda);

        Pared *paredDerecha = new Pared();
        paredDerecha->setPos(anchoEscena - DimensionBloque, alturaPanelInfo + y * DimensionBloque);
        addItem(paredDerecha);
    }

    // Crear bloques indestructibles en patrón tipo rejilla
    for (int i = 2; i < columnas - 1; i += 2) {
        for (int j = 2; j < filas - 1; j += 2) {
            Pared *bloqueFijo = new Pared();
            bloqueFijo->setPos(i * DimensionBloque, alturaPanelInfo + j * DimensionBloque);
            addItem(bloqueFijo);
        }
    }

    // Crear ladrillos en espacios libres, dejando zona de inicio despejada
    for (int i = 1; i < columnas - 1; ++i) {
        for (int j = 1; j < filas - 1; ++j) {
            int x = i * DimensionBloque;
            int y = alturaPanelInfo + j * DimensionBloque;

            // Zona de inicio despejada (arriba a la izquierda)
            if ((i <= 2 && j <= 2)) continue;

            // No colocar si ya hay un bloque fijo en esta posición
            QList<QGraphicsItem*> existentes = items(QRectF(x, y, DimensionBloque, DimensionBloque));
            bool ocupado = false;
            for (QGraphicsItem* item : existentes) {
                if (dynamic_cast<Pared*>(item)) {
                    ocupado = true;
                    break;
                }
            }
            if (ocupado) continue;

            // Probabilidad de crear ladrillo (más moderado)
            if (rand() % 100 < 50) {
                Ladrillo* ladrillo = new Ladrillo();
                ladrillo->setPos(x, y);
                addItem(ladrillo);
                ladrillos.append(ladrillo);
            }
        }
    }

    // Crear puerta aleatoria en uno de los ladrillos
    crearPuertaAleatoria();
}

void Escena::inicializarPanelInfo() {
    panelInfo = new PanelInfo();
    addItem(panelInfo);
    panelInfo->setPos(0, 0);
    panelInfo->setZValue(10);
}

void Escena::inicializarPersonajes() {
    jugador = new Jugador();
    QPointF posicionInicialJugador(40, 90);
    jugador->setPos(posicionInicialJugador);
    jugador->setPosicionInicial(posicionInicialJugador); // Establecer posición inicial para respawn
    addItem(jugador);

    // Conectar señales del jugador
    connect(jugador, &Jugador::jugadorMurio, this, &Escena::alJugadorMurio);
    connect(jugador, &Jugador::bombaColocada, this, &Escena::alBombaColocada);
    // connect(jugador, &Jugador::enemigoDestruido, this, [=]() {
    //     sumarPuntos(100);
    //     verificarCondicionesVictoria();
    // });
    // connect(jugador, &Jugador::ladrilloDestruido, this, [=]() {
    //     sumarPuntos(10);
    //     verificarCondicionesVictoria();
    // });
    connect(jugador, &Jugador::enemigoDestruido, this, &Escena::verificarCondicionesVictoria);
    connect(jugador, &Jugador::ladrilloDestruido, this, &Escena::verificarCondicionesVictoria);

    QRandomGenerator* generadorAleatorio = QRandomGenerator::global();
    int alturaPanelInfo = 50;
    int tamañoCuadricula = 40;
    int intentos = 0;
    int maxIntentos = 100;
    int cantidad = 6;

    enemigos.clear();

    for (int i = 0; i < cantidad && intentos < maxIntentos; i++) {
        bool posicionEncontrada = false;
        QPointF posicionEnemigo;

        // Intentar encontrar una posición válida para el enemigo
        while (!posicionEncontrada && intentos < maxIntentos) {
            // Posiciones solo en la cuadrícula (múltiplos de 40)
            int cuadriculaX = generadorAleatorio->bounded(1, 19); // De 1 a 18 para evitar bordes
            int cuadriculaY = generadorAleatorio->bounded(2, 13); // De 2 a 12 para evitar bordes

            int x = cuadriculaX * tamañoCuadricula;
            int y = cuadriculaY * tamañoCuadricula + alturaPanelInfo;

            posicionEnemigo = QPointF(x, y);
            intentos++;

            // Verificar que no esté muy cerca del jugador (zona de inicio)
            if (cuadriculaX <= 3 && cuadriculaY <= 3) {
                continue; // Evitar zona de inicio del jugador
            }

            // Verificar que la posición esté libre de paredes y ladrillos
            QRectF rectanguloEnemigo(posicionEnemigo.x(), posicionEnemigo.y(), tamañoCuadricula, tamañoCuadricula);
            QList<QGraphicsItem*> elementosEnArea = items(rectanguloEnemigo);

            bool areaLibre = true;
            for (QGraphicsItem* elemento : elementosEnArea) {
                if (dynamic_cast<Pared*>(elemento) || dynamic_cast<Ladrillo*>(elemento) || dynamic_cast<Enemigo*>(elemento)) {
                    areaLibre = false;
                    break;
                }
            }

            if (areaLibre) {
                posicionEncontrada = true;
            }
        }

        if (posicionEncontrada) {
            Enemigo* enemigo = new Enemigo();
            addItem(enemigo);
            enemigo->setPos(posicionEnemigo);
            enemigo->iniciarMovimiento();
        }
    }
}

void Escena::inicializarEstadoDelJuego() {
    tiempoJuego = configuracion.limiteTiempo;

    if (nivelActual == 1) {
        puntuacion = 0;
        vidas = VIDAS_INICIALES;
    }

    juegoIniciado = true;
    JuegoTerminado = false;
    NivelCompleto = false;

    // Actualizar la información en el panel
    panelInfo->actualizarTiempo(tiempoJuego);
    panelInfo->actualizarPuntuacion(puntuacion);
    panelInfo->actualizarVidas(vidas);
    panelInfo->actualizarNivel(nivelActual);
}

// void Escena::configurarTemporizador() {
//     //bool victoria;

//     temporizadorJuego = new QTimer(this);

//     connect(temporizadorJuego, &QTimer::timeout, this, [=]() {
//         if (--tiempoJuego >= 0) {
//             panelInfo->actualizarTiempo(tiempoJuego);
//         } else {
//             temporizadorJuego->stop();
//             temporizadorJuego->stop();

//             VentanaPersonalizada *dialogo = new VentanaPersonalizada(
//                 "¡GAME OVER!", {"Volver al menú", "Reintentar", "Salir"});

//             // // Verificar si es un nuevo record
//             // SistemaRecords* sistema = SistemaRecords::getInstance();
//             // bool esNuevoRecord = sistema->esNuevoRecord(puntuacion);

//             // qDebug() << "[ESCENA] ¿Es nuevo record?" << esNuevoRecord;

//             // // La ventana de records decidirá internamente si mostrar o no el formulario de nuevo record
//             // if (puntuacion > 0) { // Solo si hay alguna puntuación
//             //     int tiempoTotal = configuracion.limiteTiempo - tiempoJuego;

//             //     VentanaRecords *ventanaRecord;
//             //     if (esNuevoRecord) {
//             //         // Crear ventana en modo "nuevo record"
//             //         ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);
//             //     } else {
//             //         // Crear ventana en modo "solo mostrar records" pero permitir guardar
//             //         ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);
//             //     }

//             //     connect(ventanaRecord, &QDialog::finished, this, [=]() {
//             //         // Después de la ventana de records, mostrar opciones
//             //         mostrarOpcionesFinJuego(victoria);
//             //         ventanaRecord->deleteLater();
//             //     });

//             //     ventanaRecord->show();
//             // }

//             connect(dialogo, &VentanaPersonalizada::opcionSeleccionada, this, [=](const QString &opcion) {
//                 if (opcion == "Volver al menú") emit volverAlMenu();
//                 else if (opcion == "Reintentar") reiniciarNivel();
//                 else if (opcion == "Salir") qApp->quit();
//             });

//             dialogo->show();
//         }
//     });

//     temporizadorJuego->start(1000);  // Cada 1 segundo
// }

void Escena::configurarTemporizador() {
    temporizadorJuego = new QTimer(this);

    connect(temporizadorJuego, &QTimer::timeout, this, [=]() {
        if (--tiempoJuego >= 0) {
            panelInfo->actualizarTiempo(tiempoJuego);
        } else {
            temporizadorJuego->stop();

            int tiempoTotal = configuracion.limiteTiempo;
            if (puntuacion > 0) {
                // Verificar si es nuevo récord
                SistemaRecords* sistema = SistemaRecords::getInstance();
                bool esNuevoRecord = sistema->esNuevoRecord(puntuacion);
                qDebug() << "[ESCENA] ¿Es nuevo record?" << esNuevoRecord;

                // Crear y mostrar ventana de récords
                VentanaRecords *ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);

                connect(ventanaRecord, &QDialog::finished, this, [=]() {
                    // Después de cerrar la ventana de récords, mostrar opciones
                    mostrarDialogoOpcionesFinJuego();
                    ventanaRecord->deleteLater();
                });

                ventanaRecord->show();
            } else {
                // Si no hay puntuación, mostrar directamente el diálogo de opciones
                mostrarDialogoOpcionesFinJuego();
            }
        }
    });

    temporizadorJuego->start(1000);  // Cada 1 segundo
}

void Escena::mostrarDialogoOpcionesFinJuego() {
    VentanaPersonalizada *dialogo = new VentanaPersonalizada(
        "¡GAME OVER!", {"Volver al menú", "Reintentar", "Salir"});

    connect(dialogo, &VentanaPersonalizada::opcionSeleccionada, this, [=](const QString &opcion) {
        if (opcion == "Volver al menú") emit volverAlMenu();
        else if (opcion == "Reintentar") reiniciarNivel();
        else if (opcion == "Salir") qApp->quit();
    });

    dialogo->show();
}


void Escena::mostrarTextoTemporal(const QString& mensaje, int duracionMs) {
    QGraphicsTextItem* texto = new QGraphicsTextItem(mensaje);
    QFont fuente("Press Start 2P", 20);  // Usa la fuente que prefieras
    texto->setFont(fuente);
    texto->setDefaultTextColor(Qt::white);
    texto->setZValue(100);
    texto->setPos(40, 235);  // Ajusta posición según diseño

    addItem(texto);

    QTimer::singleShot(duracionMs, this, [=]() {
        removeItem(texto);
        delete texto;
    });
}

void Escena::reiniciarNivel() {
    enemigos.clear();
    ladrillos.clear();
    puerta = nullptr;
    puertaVisible = false;

    clear();
    crearMapa();
    inicializarPanelInfo();
    inicializarPersonajes();

    tiempoJuego = configuracion.limiteTiempo;

    // Solo reiniciar puntuación y vidas si no es reinicio de victoria
    if (nivelActual == 1 && !NivelCompleto) {
        puntuacion = 0;
        vidas = VIDAS_INICIALES;
    }

    juegoIniciado = true;
    JuegoTerminado = false;
    NivelCompleto = false;

    panelInfo->actualizarTiempo(tiempoJuego);
    panelInfo->actualizarPuntuacion(puntuacion);
    panelInfo->actualizarVidas(vidas);
    panelInfo->actualizarNivel(nivelActual);

    temporizadorJuego->start(1000);
}

// void Escena::reiniciarNivel() {
//     // Limpiar listas
//     enemigos.clear();
//     ladrillos.clear();
//     puerta = nullptr;
//     puertaVisible = false;

//     // Limpiar la escena y volver a cargar
//     clear();
//     crearMapa();
//     inicializarPanelInfo();
//     inicializarPersonajes();

//     // Reiniciar estado del juego
//     tiempoJuego = configuracion.limiteTiempo;
//     if (nivelActual == 1) {
//         puntuacion = 0;
//         vidas = VIDAS_INICIALES;
//     }

//     juegoIniciado = true;
//     JuegoTerminado = false;
//     NivelCompleto = false;

//     panelInfo->actualizarTiempo(tiempoJuego);
//     panelInfo->actualizarPuntuacion(puntuacion);
//     panelInfo->actualizarVidas(vidas);
//     panelInfo->actualizarNivel(nivelActual);
//     temporizadorJuego->start(1000);
// }

// Métodos de manejo de entrada
void Escena::manejarTeclaPresionada(int tecla) {
    if (jugador && !JuegoTerminado) {
        if (tecla == Qt::Key_Space) {
            jugador->colocarBomba();
        } else {
            jugador->agregarTeclaPresionada(tecla);
        }
    }
}

void Escena::manejarTeclaLiberada(int tecla) {
    if (jugador && !JuegoTerminado) {
        jugador->quitarTeclaPresionada(tecla);
    }
}

// Métodos de gestión de la puerta
void Escena::crearPuertaAleatoria() {

    puertaLiberada = false;

    if (ladrillos.isEmpty()) return;

    // Seleccionar un ladrillo aleatorio
    int indiceAleatorio = QRandomGenerator::global()->bounded(ladrillos.size());
    Ladrillo* ladrilloSeleccionado = ladrillos[indiceAleatorio];
    posicionPuerta = ladrilloSeleccionado->pos();

    // Crear puerta (inicialmente oculta)
    puerta = new QGraphicsPixmapItem();
    puerta->setPixmap(QPixmap(":/images/door.png").scaled(40, 40));
    puerta->setPos(posicionPuerta);
    puerta->setVisible(false);
    puerta->setZValue(5);
    addItem(puerta);
}

void Escena::mostrarPuerta() {
    qDebug() << "[DEBUG PUERTA] Intentando mostrar puerta. Visible:" << puertaVisible
             << "| Posición:" << (puerta ? puerta->pos() : QPointF(-1, -1))
             << "| posicionPuerta:" << posicionPuerta;

    if (puerta && !puertaVisible) {
        puerta->setVisible(true);
        puertaVisible = true;
        mostrarTextoTemporal("¡Puerta aparecida! ¡Elimina todos los enemigos!", 2000);
        qDebug() << "[DEBUG PUERTA] Puerta mostrada en:" << puerta->pos();
    }
}


// Métodos de eventos del juego
void Escena::alJugadorMurio() {
    if (vidas > 1) {
        vidas--;
        panelInfo->actualizarVidas(vidas);

        // Asegurar que el jugador esté visible y en la posición correcta
        jugador->setVisible(true);
        jugador->setZValue(1);
        jugador->activarInmunidad(3000);

        mostrarTextoTemporal("¡Has perdido una vida!", 2000);
        qDebug() << "[ESCENA] Jugador perdió una vida. Vidas restantes:" << vidas;
    } else {
        JuegoTerminado = true;
        temporizadorJuego->stop();
        mostrarVentanaGameOver(false);
        qDebug() << "[ESCENA] Game Over - Sin vidas restantes";
    }
}

void Escena::alBombaColocada() {
    // Conectar la última bomba colocada con el sistema de puntos
    QList<QGraphicsItem*> items = this->items();
    for (QGraphicsItem* item : items) {
        Bomba* bomba = dynamic_cast<Bomba*>(item);
        if (bomba) {
            // Verificar si ya está conectada para evitar conexiones múltiples
            disconnect(bomba, &Bomba::explosion, this, &Escena::alBombaExplotada);
            connect(bomba, &Bomba::explosion, this, &Escena::alBombaExplotada);
        }
    }
}

void Escena::alBombaExplotada(const QPointF& centro, int rango) {
    // Llamar a las funciones de destrucción que manejan los puntos
    destruirEnemigosEnExplosion(centro, rango);
    destruirLadrillosEnExplosion(centro, rango);

    // Verificar condiciones después de la explosión
    verificarCondicionesVictoria();

    qDebug() << "[ESCENA] Explosión procesada en:" << centro << "con rango:" << rango;
}

void Escena::verificarCondicionesVictoria() {
    // Verificar colisión con puerta SOLO si ya no hay enemigos
    if (puertaVisible && jugador) {
        int enemigosVivos = 0;
        for (Enemigo* enemigo : enemigos) {
            if (!enemigo->estaMuriendo()) {
                enemigosVivos++;
            }
        }

        if (enemigosVivos == 0) {
            QRectF jugadorRect = jugador->boundingRect().translated(jugador->pos());
            QRectF puertaRect = puerta->boundingRect().translated(puerta->pos());

            if (jugadorRect.intersects(puertaRect)) {
                // Victoria
                JuegoTerminado = true;
                NivelCompleto = true;
                temporizadorJuego->stop();
                puntuacion += tiempoJuego * 10; // Bonus por tiempo restante
                mostrarVentanaGameOver(true);
                qDebug() << "[ESCENA] Victoria: jugador entró a la puerta sin enemigos restantes.";
            }
        } else {
            // Opcional: mensaje si el jugador intenta entrar antes de eliminar enemigos
            QRectF jugadorRect = jugador->boundingRect().translated(jugador->pos());
            QRectF puertaRect = puerta->boundingRect().translated(puerta->pos());

            if (jugadorRect.intersects(puertaRect)) {
                mostrarTextoTemporal("¡Elimina todos los enemigos!", 1500);
                qDebug() << "[ESCENA] Jugador tocó la puerta pero aún hay enemigos.";
            }
        }
    }
}

void Escena::verificarColisionPuerta() {
    if (!puertaVisible || !jugador || jugador->estaMuriendo()) return;

    QRectF jugadorRect = jugador->boundingRect().translated(jugador->pos());
    QRectF puertaRect = puerta->boundingRect().translated(puerta->pos());

    if (jugadorRect.intersects(puertaRect)) {
        // Victoria!
        JuegoTerminado = true;
        NivelCompleto = true;
        temporizadorJuego->stop();
        puntuacion += tiempoJuego * 10;
        mostrarVentanaGameOver(true);
    }
}

// void Escena::mostrarVentanaGameOver(bool victoria) {
//     // BLOQUEAR JUEGO: Pausar todos los timers y deshabilitar input
//     JuegoTerminado = true;

//     // Pausar temporizador principal del juego
//     if (temporizadorJuego) {
//         temporizadorJuego->stop();
//     }

//     // Deshabilitar input del jugador
//     if (jugador) {
//         jugador->setFlag(QGraphicsItem::ItemIsFocusable, false);
//         // Si el jugador tiene timers, también detenerlos
//     }

//     // Pausar movimiento de enemigos
//     for (Enemigo* enemigo : enemigos) {
//         if (enemigo && !enemigo->estaMuriendo()) {
//             // Detener movimiento de enemigos (si tienen timers)
//         }
//     }

//     qDebug() << "[ESCENA] Juego pausado - Game Over mostrado";

//     // Verificar si es un nuevo record
//     SistemaRecords* sistema = SistemaRecords::getInstance();
//     bool esNuevoRecord = sistema->esNuevoRecord(puntuacion);

//     if (victoria && esNuevoRecord) {
//         // Mostrar ventana de nuevo record
//         int tiempoTotal = configuracion.limiteTiempo - tiempoJuego;
//         VentanaRecords *ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);

//         connect(ventanaRecord, &QDialog::finished, this, [=]() {
//             // Después de guardar el record, mostrar opciones
//             mostrarOpcionesFinJuego(victoria);
//             ventanaRecord->deleteLater();
//         });

//         ventanaRecord->show();
//     } else {
//         // Mostrar directamente las opciones
//         mostrarOpcionesFinJuego(victoria);
//     }
// }

void Escena::mostrarVentanaGameOver(bool victoria) {
    // BLOQUEAR JUEGO: Pausar todos los timers y deshabilitar input
    JuegoTerminado = true;

    // Pausar temporizador principal del juego
    if (temporizadorJuego) {
        temporizadorJuego->stop();
    }

    // Deshabilitar input del jugador
    if (jugador) {
        jugador->setFlag(QGraphicsItem::ItemIsFocusable, false);
    }

    // Pausar movimiento de enemigos
    for (Enemigo* enemigo : enemigos) {
        if (enemigo && !enemigo->estaMuriendo()) {
            // Detener movimiento de enemigos (si tienen timers)
        }
    }

    qDebug() << "[ESCENA] Juego pausado - Game Over mostrado";
    qDebug() << "[ESCENA] Puntuación final:" << puntuacion << "Nivel:" << nivelActual;

    // Verificar si es un nuevo record
    SistemaRecords* sistema = SistemaRecords::getInstance();
    bool esNuevoRecord = sistema->esNuevoRecord(puntuacion);

    qDebug() << "[ESCENA] ¿Es nuevo record?" << esNuevoRecord;

    // La ventana de records decidirá internamente si mostrar o no el formulario de nuevo record
    if (puntuacion > 0) { // Solo si hay alguna puntuación
        int tiempoTotal = configuracion.limiteTiempo - tiempoJuego;

        VentanaRecords *ventanaRecord;
        if (esNuevoRecord) {
            // Crear ventana en modo "nuevo record"
            ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);
        } else {
            // Crear ventana en modo "solo mostrar records" pero permitir guardar
            ventanaRecord = new VentanaRecords(puntuacion, nivelActual, tiempoTotal, nullptr);
        }

        connect(ventanaRecord, &QDialog::finished, this, [=]() {
            // Después de la ventana de records, mostrar opciones
            mostrarOpcionesFinJuego(victoria);
            ventanaRecord->deleteLater();
        });

        ventanaRecord->show();
    } else {
        // Si no hay puntuación, mostrar directamente las opciones
        mostrarOpcionesFinJuego(victoria);
    }
}

void Escena::mostrarOpcionesFinJuego(bool victoria) {
    QString mensaje = victoria ? "¡VICTORIA!" : "¡GAME OVER!";
    mensaje += QString("\n\nPuntuación Final: %1\nNivel: %2").arg(puntuacion).arg(nivelActual);

    QStringList opciones = {"Volver al menú", "Ver Records", "Reintentar", "Salir"};

    VentanaPersonalizada *dialogo = new VentanaPersonalizada(mensaje, opciones);

    connect(dialogo, &VentanaPersonalizada::opcionSeleccionada, this, [=](const QString &opcion) {
        if (opcion == "Volver al menú") {
            emit volverAlMenu();
        } else if (opcion == "Ver Records") {
            VentanaRecords *ventanaRecords = new VentanaRecords();
            ventanaRecords->exec();
            delete ventanaRecords;
            // Mostrar opciones nuevamente
            mostrarOpcionesFinJuego(victoria);
        } else if (opcion == "Reintentar") {
            reiniciarNivel();
        } else if (opcion == "Salir") {
            qApp->quit();
        }
    });

    //dialogo->show();
    dialogo->exec();
}

// void Escena::destruirEnemigosEnExplosion(const QPointF& centro, int rango) {
//     int gridSize = 40;

//     // Ajustar centro a la cuadrícula
//     int gridX = qRound(centro.x() / gridSize) * gridSize;
//     int gridY = qRound(centro.y() / gridSize) * gridSize;
//     QPointF centroGrid(gridX, gridY);

//     // Direcciones de explosión en cruz
//     QList<QPointF> direcciones = {
//         QPointF(0, 0),          // Centro
//         QPointF(0, -gridSize),  // Arriba
//         QPointF(0, gridSize),   // Abajo
//         QPointF(-gridSize, 0),  // Izquierda
//         QPointF(gridSize, 0)    // Derecha
//     };

//     QList<Enemigo*> enemigosAfectados;

//     // Verificar explosión en cada dirección
//     for (const QPointF& direccion : direcciones) {
//         for (int i = (direccion == QPointF(0, 0) ? 0 : 1); i <= rango; ++i) {
//             QPointF posExplosion = centroGrid + direccion * i;

//             // Verificar límites
//             if (posExplosion.x() < 0 || posExplosion.y() < 50 ||
//                 posExplosion.x() >= 920 || posExplosion.y() >= 570) {
//                 break;
//             }

//             // Buscar enemigos en el área de explosión
//             QRectF areaExplosion(posExplosion, QSizeF(gridSize, gridSize));

//             for (Enemigo* enemigo : enemigos) {
//                 if (enemigo && !enemigo->estaMuriendo() && !enemigosAfectados.contains(enemigo)) {
//                     QRectF areaEnemigo = enemigo->boundingRect().translated(enemigo->pos());

//                     if (areaExplosion.intersects(areaEnemigo)) {
//                         enemigosAfectados.append(enemigo);
//                         enemigo->activarAnimacionMuerte();
//                         puntuacion += 100;
//                         qDebug() << "[ESCENA] Enemigo destruido en explosión. Puntuación actual:" << puntuacion;
//                     }
//                 }
//             }
//         }
//     }

//     // Actualizar puntuación en pantalla
//     panelInfo->actualizarPuntuacion(puntuacion);
// }

void Escena::destruirEnemigosEnExplosion(const QPointF& centro, int rango) {

    //sumarPuntos(100);

    int gridSize = 40;
    int gridX = qRound(centro.x() / gridSize) * gridSize;
    int gridY = qRound(centro.y() / gridSize) * gridSize;
    QPointF centroGrid(gridX, gridY);

    QList<QPointF> direcciones = {
        QPointF(0, 0), QPointF(0, -gridSize), QPointF(0, gridSize),
        QPointF(-gridSize, 0), QPointF(gridSize, 0)
    };

    QList<Enemigo*> enemigosAfectados;

    for (const QPointF& direccion : direcciones) {
        for (int i = (direccion == QPointF(0, 0) ? 0 : 1); i <= rango; ++i) {
            QPointF posExplosion = centroGrid + direccion * i;

            if (posExplosion.x() < 0 || posExplosion.y() < 50 ||
                posExplosion.x() >= 920 || posExplosion.y() >= 570)
                break;

            QRectF areaExplosion(posExplosion, QSizeF(gridSize, gridSize));

            for (Enemigo* enemigo : enemigos) {
                if (enemigo && !enemigo->estaMuriendo() && !enemigosAfectados.contains(enemigo)) {
                    QRectF areaEnemigo = enemigo->boundingRect().translated(enemigo->pos());
                    if (areaExplosion.intersects(areaEnemigo)) {
                        enemigosAfectados.append(enemigo);
                        enemigo->activarAnimacionMuerte();
                        sumarPuntos(100);
                    }
                }
            }
        }
    }
}

// void Escena::destruirLadrillosEnExplosion(const QPointF& centro, int rango) {
//     QList<Ladrillo*> ladrillosAEliminar;
//     int gridSize = 40;

//     // Ajustar centro a cuadrícula
//     int gridX = qRound(centro.x() / gridSize) * gridSize;
//     int gridY = qRound(centro.y() / gridSize) * gridSize;
//     QPointF centroGrid(gridX, gridY);

//     QList<QPointF> direcciones = {
//         QPointF(0, 0),          // Centro
//         QPointF(0, -gridSize),  // Arriba
//         QPointF(0, gridSize),   // Abajo
//         QPointF(-gridSize, 0),  // Izquierda
//         QPointF(gridSize, 0)    // Derecha
//     };

//     for (const QPointF& direccion : direcciones) {
//         for (int i = (direccion == QPointF(0, 0) ? 0 : 1); i <= rango; ++i) {
//             QPointF posExplosion = centroGrid + direccion * i;

//             // Verificar límites del escenario
//             if (posExplosion.x() < 0 || posExplosion.y() < 50 ||
//                 posExplosion.x() >= 920 || posExplosion.y() >= 570) {
//                 break;
//             }

//             bool obstaculo = false;

//             for (Ladrillo* ladrillo : ladrillos) {
//                 if (ladrillo &&
//                     ladrillo->pos() == posExplosion &&
//                     !ladrillosAEliminar.contains(ladrillo)) {

//                     ladrillosAEliminar.append(ladrillo);
//                     qDebug() << "[ESCENA] Ladrillo marcado para eliminación en:" << posExplosion;
//                     obstaculo = true;
//                     break;
//                 }
//             }

//             if (obstaculo && i > 0) break; // Detener propagación si hay ladrillo
//         }
//     }

//     // Verificar si el ladrillo que contiene la puerta fue destruido
//     bool seDestruyoElLadrilloDeLaPuerta = false;

//     for (Ladrillo* ladrillo : ladrillosAEliminar) {
//         if (ladrillo->pos() == posicionPuerta) {
//             seDestruyoElLadrilloDeLaPuerta = true;
//             puertaLiberada = true;
//         }

//         ladrillos.removeOne(ladrillo);
//         removeItem(ladrillo);
//         delete ladrillo;

//         puntuacion += 10;
//         qDebug() << "[ESCENA] Ladrillo eliminado. Puntuación actual:" << puntuacion;
//     }

//     panelInfo->actualizarPuntuacion(puntuacion);

//     if (seDestruyoElLadrilloDeLaPuerta && !puertaVisible) {
//         mostrarPuerta();
//         qDebug() << "[ESCENA] Puerta revelada tras destruir su ladrillo.";
//     }
// }

void Escena::destruirLadrillosEnExplosion(const QPointF& centro, int rango) {

    //sumarPuntos(10);

    QList<Ladrillo*> ladrillosAEliminar;
    int gridSize = 40;
    int gridX = qRound(centro.x() / gridSize) * gridSize;
    int gridY = qRound(centro.y() / gridSize) * gridSize;
    QPointF centroGrid(gridX, gridY);

    QList<QPointF> direcciones = {
        QPointF(0, 0), QPointF(0, -gridSize), QPointF(0, gridSize),
        QPointF(-gridSize, 0), QPointF(gridSize, 0)
    };

    for (const QPointF& direccion : direcciones) {
        for (int i = (direccion == QPointF(0, 0) ? 0 : 1); i <= rango; ++i) {
            QPointF posExplosion = centroGrid + direccion * i;

            if (posExplosion.x() < 0 || posExplosion.y() < 50 ||
                posExplosion.x() >= 920 || posExplosion.y() >= 570)
                break;

            bool obstaculo = false;

            for (Ladrillo* ladrillo : ladrillos) {
                if (ladrillo && ladrillo->pos() == posExplosion && !ladrillosAEliminar.contains(ladrillo)) {
                    ladrillosAEliminar.append(ladrillo);
                    obstaculo = true;
                    break;
                }
            }

            if (obstaculo && i > 0) break;
        }
    }

    bool seDestruyoElLadrilloDeLaPuerta = false;

    for (Ladrillo* ladrillo : ladrillosAEliminar) {
        if (ladrillo->pos() == posicionPuerta) {
            seDestruyoElLadrilloDeLaPuerta = true;
            puertaLiberada = true;
        }

        ladrillos.removeOne(ladrillo);
        removeItem(ladrillo);
        delete ladrillo;

        sumarPuntos(10);
    }

    if (seDestruyoElLadrilloDeLaPuerta && !puertaVisible) {
        mostrarPuerta();
    }
}
