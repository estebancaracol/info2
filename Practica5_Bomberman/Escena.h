#ifndef ESCENA_H
#define ESCENA_H

#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "Pared.h"
#include "Ladrillo.h"
#include "PanelInfo.h"
#include "Jugador.h"
#include "Enemigo.h"

class Escena : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Escena(QObject *parent = nullptr);
    void crearMapa();
    void inicializarPersonajes();
    void mostrarTextoTemporal(const QString& mensaje, int duracionMs);

    // Manejo de entrada
    void manejarTeclaPresionada(int tecla);
    void manejarTeclaLiberada(int tecla);
    void sumarPuntos(int cantidad);

private:
    PanelInfo *panelInfo;
    Jugador *jugador;
    QGraphicsPixmapItem *puerta;
    QPointF posicionPuerta;
    bool puertaVisible;

    QList<Enemigo*> enemigos;
    QList<Ladrillo*> ladrillos;

    // Temporizadores
    QTimer *temporizadorJuego;

    // Variables del sistema de juego
    int tiempoJuego;
    int puntuacion;
    int vidas;
    int nivelActual = 1;

    bool JuegoTerminado;
    bool juegoIniciado;
    bool NivelCompleto;

    struct Configuracion {
        int limiteTiempo = 120;
    } configuracion;

    static const int VIDAS_INICIALES = 3;

    void inicializarPanelInfo();
    void inicializarEstadoDelJuego();
    void configurarTemporizador();
    void mostrarDialogoOpcionesFinJuego();

public slots:
    void reiniciarNivel();
    void alJugadorMurio();
    void alBombaColocada();
    void alBombaExplotada(const QPointF& centro, int rango); // Nueva función para manejar explosiones
    void verificarCondicionesVictoria();

private slots:
    void verificarColisionPuerta();

signals:
    void volverAlMenu();
    void juegoTerminado(bool victoria);

private:
    void crearPuertaAleatoria();
    void mostrarPuerta();
    void mostrarVentanaGameOver(bool victoria);
    void mostrarOpcionesFinJuego(bool victoria);
    void destruirEnemigosEnExplosion(const QPointF& centro, int rango);
    void destruirLadrillosEnExplosion(const QPointF& centro, int rango);

    bool puertaLiberada = false;
};

#endif // ESCENA_H
