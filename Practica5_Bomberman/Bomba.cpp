#include "Bomba.h"
#include "Pared.h"
#include "Ladrillo.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Escena.h"

#include <QTimer>
#include <QPixmap>
#include <QGraphicsScene>
#include <QSoundEffect>
#include <QDebug>

Bomba::Bomba(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), rangoExplosion(1), spriteActual(0), explotando(false) {

    cargarSprites();
    temporizador = new QTimer(this);
    temporizador->setSingleShot(true);

    temporizadorAnimacion = new QTimer(this);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Bomba::actualizarAnimacion);
    temporizadorAnimacion->start(300); // Cambiar sprite cada 300ms

    connect(temporizador, &QTimer::timeout, this, &Bomba::explotar);
}

void Bomba::cargarSprites() {
    sprites.append(QPixmap(":/images/bomba1.png").scaled(40, 40));
    sprites.append(QPixmap(":/images/bomba2.png").scaled(40, 40));
    sprites.append(QPixmap(":/images/bomba3.png").scaled(40, 40));

    if (!sprites.isEmpty()) {
        setPixmap(sprites.first());
    }
}

void Bomba::iniciarCuentaRegresiva(int milisegundos) {
    temporizador->start(milisegundos);
}

void Bomba::actualizarAnimacion() {
    if (!explotando && !sprites.isEmpty()) {
        spriteActual = (spriteActual + 1) % sprites.size();
        setPixmap(sprites[spriteActual]);
    }
}

void Bomba::explotar() {
    if (explotando) return;

    explotando = true;
    temporizadorAnimacion->stop();

    // 🔊 Efecto de sonido
    QSoundEffect* efecto = new QSoundEffect(this);
    efecto->setSource(QUrl("qrc:/sounds/explosion.wav"));
    efecto->setVolume(0.5);
    efecto->play();

    qDebug() << "[BOMBA] ¡Bomba explotó en posición!" << pos();

    crearExplosion();

    // Emitir señales
    emit explotada(this);
    emit explosion(pos(), rangoExplosion);
    qDebug() << "[BOMBA] Señales de bomba explotada emitidas.";

    QTimer::singleShot(500, this, [this]() {
        if (scene()) scene()->removeItem(this);
        qDebug() << "[BOMBA] Bomba eliminada de la escena.";
        deleteLater();
    });
}

// void Bomba::crearExplosion() {
//     if (!scene()) {
//         qDebug() << "[BOMBA] No hay escena activa para crear explosión.";
//         return;
//     }

//     int gridSize = 40;
//     QPointF centro = pos();

//     int gridX = qRound(centro.x() / gridSize) * gridSize;
//     int gridY = qRound(centro.y() / gridSize) * gridSize;
//     QPointF centroGrid(gridX, gridY);

//     crearEfectoExplosion(centroGrid);
//     verificarColisionesEnPosicion(centroGrid);

//     QList<QPointF> direcciones = {
//         QPointF(0, -gridSize),  // Arriba
//         QPointF(0, gridSize),   // Abajo
//         QPointF(-gridSize, 0),  // Izquierda
//         QPointF(gridSize, 0)    // Derecha
//     };

//     for (const QPointF& direccion : direcciones) {
//         bool bloqueado = false;

//         for (int i = 1; i <= rangoExplosion && !bloqueado; ++i) {
//             QPointF posExplosion = centroGrid + direccion * i;

//             if (posExplosion.x() < 0 || posExplosion.y() < 50 ||
//                 posExplosion.x() >= 920 || posExplosion.y() >= 570) {
//                 break;
//             }

//             QList<QGraphicsItem*> items = scene()->items(QRectF(posExplosion, QSizeF(gridSize, gridSize)));

//             for (QGraphicsItem* item : items) {
//                 if (dynamic_cast<Pared*>(item)) {
//                     bloqueado = true;
//                     break;
//                 }
//                 if (dynamic_cast<Ladrillo*>(item)) {
//                     bloqueado = false;
//                     break;
//                 }
//             }

//             //Mostrar animación incluso si hay ladrillo (para que se vea el fuego)
//             crearEfectoExplosion(posExplosion);
//             verificarColisionesEnPosicion(posExplosion);

//             if (bloqueado) break;
//         }
//     }
// }

void Bomba::crearExplosion() {
    if (!scene()) {
        qDebug() << "[BOMBA] No hay escena activa para crear explosión.";
        return;
    }

    const int gridSize = 40;
    const int alturaPanel = 50;

    QPointF centro = pos();

    int gridX = qRound(centro.x() / gridSize) * gridSize;
    int gridY = qRound((centro.y() - alturaPanel) / gridSize) * gridSize + alturaPanel;
    QPointF centroGrid(gridX, gridY);

    crearEfectoExplosion(centroGrid);
    verificarColisionesEnPosicion(centroGrid);

    QList<QPointF> direcciones = {
        QPointF(0, -gridSize),  // Arriba
        QPointF(0, gridSize),   // Abajo
        QPointF(-gridSize, 0),  // Izquierda
        QPointF(gridSize, 0)    // Derecha
    };

    for (const QPointF& direccion : direcciones) {
        bool bloqueado = false;

        for (int i = 1; i <= rangoExplosion && !bloqueado; ++i) {
            QPointF posExplosion = centroGrid + direccion * i;

            if (posExplosion.x() < 0 || posExplosion.y() < alturaPanel ||
                posExplosion.x() >= 920 || posExplosion.y() >= 570) {
                break;
            }

            QList<QGraphicsItem*> items = scene()->items(QRectF(posExplosion, QSizeF(gridSize, gridSize)));

            for (QGraphicsItem* item : items) {
                if (dynamic_cast<Pared*>(item)) {
                    bloqueado = true;
                    break;
                }
                if (dynamic_cast<Ladrillo*>(item)) {
                    // Permite mostrar la explosión sobre el ladrillo
                    break;  // no bloquea completamente
                }
            }

            crearEfectoExplosion(posExplosion);
            verificarColisionesEnPosicion(posExplosion);

            if (bloqueado) break;
        }
    }
}

void Bomba::verificarColisionesEnPosicion(const QPointF& posicion) {
    if (!scene()) return;

    int gridSize = 40;
    QRectF rectExplosion(posicion, QSizeF(gridSize, gridSize));
    QList<QGraphicsItem*> items = scene()->items(rectExplosion);

    for (QGraphicsItem* item : items) {
        if (Enemigo* enemigo = dynamic_cast<Enemigo*>(item)) {
            if (!enemigo->estaMuriendo()) {
                enemigo->activarAnimacionMuerte();
            }
        }

        if (Jugador* jugador = dynamic_cast<Jugador*>(item)) {
            if (!jugador->estaInmune() && !jugador->estaMuriendo()) {
                jugador->activarAnimacionMuerte();
            }
        }

        if (Ladrillo* ladrillo = dynamic_cast<Ladrillo*>(item)) {
            scene()->removeItem(ladrillo);
            delete ladrillo;
            Escena* escena = dynamic_cast<Escena*>(this->scene());
            if (escena) {
                escena->sumarPuntos(10);
            }
            qDebug() << "[ESCENA] Ladrillo destruido en: " << posicion;
        }
    }
}


void Bomba::crearEfectoExplosion(const QPointF& posicion) {
    if (!scene()) return;

    QGraphicsPixmapItem* explosion = new QGraphicsPixmapItem();
    explosion->setPos(posicion);
    explosion->setZValue(10);
    scene()->addItem(explosion);

    static QVector<QPixmap> framesExplosion;
    if (framesExplosion.isEmpty()) {
        framesExplosion.append(QPixmap(":/images/E1.png").scaled(40, 40));
        framesExplosion.append(QPixmap(":/images/E2.png").scaled(40, 40));
        framesExplosion.append(QPixmap(":/images/E3.png").scaled(40, 40));
    }

    if (!framesExplosion.isEmpty()) {
        explosion->setPixmap(framesExplosion[0]);
    }

    QTimer* timerAnimacion = new QTimer(this);
    int* frameActual = new int(0);

    connect(timerAnimacion, &QTimer::timeout, this, [=]() mutable {
        if (*frameActual < framesExplosion.size() - 1) {
            (*frameActual)++;
            if (explosion && explosion->scene()) {
                explosion->setPixmap(framesExplosion[*frameActual]);
            }
        } else {
            timerAnimacion->stop();
            if (explosion && explosion->scene()) {
                explosion->scene()->removeItem(explosion);
            }
            delete explosion;
            delete frameActual;
            timerAnimacion->deleteLater();
        }
    });

    timerAnimacion->start(150);
}


