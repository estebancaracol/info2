#include "Enemigo.h"
#include "Escena.h"

#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QTimer>

Enemigo::Enemigo(QGraphicsItem *parent)
    : Entidad(parent), velocidad(1), contadorMovimiento(0), intervaloCambioDireccion(30), muriendo(false) {

    cargarSprites();

    temporizadorMovimiento = new QTimer(this);
    temporizadorAnimacion = new QTimer(this);

    connect(temporizadorMovimiento, &QTimer::timeout, this, &Enemigo::actualizarMovimiento);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Enemigo::actualizarAnimacion);

    direccion = obtenerDireccionAleatoria();
    temporizadorMovimiento->start(50);  // Movimiento más frecuente para mayor fluidez
    temporizadorAnimacion->start(150);  // Animación más rápida
}

Enemigo::~Enemigo() {}

void Enemigo::cargarSprites() {
    QStringList rutas = {
        ":/images/enemy_balloon1.png",
        ":/images/enemy_balloon2.png",
        ":/images/enemy_balloon3.png",
        ":/images/enemy_balloon4.png",
        ":/images/enemy_balloon5.png",
        ":/images/enemy_balloon6.png"
    };
    Entidad::cargarSprites(rutas);
}

void Enemigo::iniciarMovimiento() {
    temporizadorMovimiento->start();
}

void Enemigo::detenerMovimiento() {
    temporizadorMovimiento->stop();
}

void Enemigo::establecerVelocidad(int v) {
    velocidad = v;
}

int Enemigo::obtenerVelocidad() const {
    return velocidad;
}

void Enemigo::actualizarMovimiento() {
    if (muriendo) return;

    QPointF nuevaPos = pos() + direccion * velocidad;

    if (puedeMoversea(nuevaPos)) {
        mover(direccion * velocidad);
        contadorMovimiento++;
    } else {
        // Si no puede moverse, cambiar dirección inmediatamente
        direccion = obtenerDireccionAleatoria();
        contadorMovimiento = 0;

        // Intentar moverse en la nueva dirección
        nuevaPos = pos() + direccion * velocidad;
        if (puedeMoversea(nuevaPos)) {
            mover(direccion * velocidad);
        }
    }

    // Cambiar dirección aleatoriamente de vez en cuando
    if (contadorMovimiento >= intervaloCambioDireccion) {
        contadorMovimiento = 0;
        if (QRandomGenerator::global()->bounded(100) < 30) { // 30% probabilidad
            direccion = obtenerDireccionAleatoria();
        }
    }
}

void Enemigo::actualizarAnimacion() {
    if (!muriendo) avanzarSprite(sprites, indiceSprite);
}

void Enemigo::cambiarDireccion() {
    direccion = obtenerDireccionAleatoria();
}

QPointF Enemigo::obtenerDireccionAleatoria() {
    int r = QRandomGenerator::global()->bounded(4);
    switch (r) {
    case 0: return {0, -1};
    case 1: return {0, 1};
    case 2: return {-1, 0};
    default: return {1, 0};
    }
}

void Enemigo::activarAnimacionMuerte() {
    muriendo = true;
    // NO hacer setVisible(false) para que se vea la animación

    // Detener el movimiento del enemigo
    if (temporizadorMovimiento) {
        temporizadorMovimiento->stop();
    }

    QStringList spritesMuerte = {
        ":/images/globocolision1.png",
        ":/images/globocolision2.png",
        ":/images/globocolision3.png",
        ":/images/globocolision4.png",
        ":/images/globocolision5.png"
    };

    // Llamar a la función de la clase base Entidad con velocidad de 120ms por frame
    iniciarAnimacionMuerte(spritesMuerte, 120);

    qDebug() << "[ENEMIGO] Iniciando animación de muerte";
    QTimer::singleShot(600, this, [this]() {
        if (scene()) {
            scene()->removeItem(this);
        }
        deleteLater();
    });
    Escena* escena = dynamic_cast<Escena*>(this->scene());
    if (escena) {
        escena->sumarPuntos(100);
    }
}
