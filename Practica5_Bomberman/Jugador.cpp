#include "Jugador.h"
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

#include "Pared.h"
#include "Ladrillo.h"
#include "Enemigo.h"

Jugador::Jugador(QGraphicsItem *parent)
    : Entidad(parent), maximoBombas(1), rangoExplosion(1), velocidad(2),
    muriendo(false), inmune(false), visible(true), direccionActual(0) {
    cargarSprites();
    spriteDefecto = QPixmap(":/images/player_p.png").scaled(35, 35);
    setPixmap(spriteDefecto);

    // Timer para movimiento continuo
    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, &Jugador::actualizarMovimiento);
    //temporizadorMovimiento->start(30); // ~25
    temporizadorMovimiento->start(16); // ~25 FPS


    // Timer para animaciones
    temporizadorAnimacion = new QTimer(this);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Jugador::resetearASpritePorDefecto);
    temporizadorAnimacion->setSingleShot(true);
    temporizadorAnimacion->setInterval(200);

    // Timer para inmunidad
    temporizadorInmunidad = new QTimer(this);
    connect(temporizadorInmunidad, &QTimer::timeout, this, &Jugador::finalizarInmunidad);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

Jugador::~Jugador() {
    qDebug() << "[JUGADOR] Destructor llamado.";
}

void Jugador::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    agregarTeclaPresionada(key);
    event->accept();
}

void Jugador::keyReleaseEvent(QKeyEvent* event) {
    int key = event->key();
    quitarTeclaPresionada(key);
    event->accept();
}

void Jugador::cargarSprites() {
    // Cargar sprites para cada dirección
    QStringList rutasAbajo = {
        ":/images/player_front1.png",
        ":/images/player_front2.png",
        ":/images/player_front3.png"
    };

    QStringList rutasArriba = {
        ":/images/player_back1.png",
        ":/images/player_back2.png",
        ":/images/player_back3.png"
    };

    QStringList rutasIzquierda = {
        ":/images/player_left1.png",
        ":/images/player_left2.png",
        ":/images/player_left3.png"
    };

    QStringList rutasDerecha = {
        ":/images/player_right1.png",
        ":/images/player_right2.png",
        ":/images/player_right3.png"
    };

    // Cargar y escalar sprites
    for (const QString &ruta : rutasAbajo) {
        spritesAbajo.append(QPixmap(ruta).scaled(35, 35));
    }
    for (const QString &ruta : rutasArriba) {
        spritesArriba.append(QPixmap(ruta).scaled(35, 35));
    }
    for (const QString &ruta : rutasIzquierda) {
        spritesIzquierda.append(QPixmap(ruta).scaled(35, 35));
    }
    for (const QString &ruta : rutasDerecha) {
        spritesDerecha.append(QPixmap(ruta).scaled(35, 35));
    }
}

void Jugador::agregarTeclaPresionada(int tecla) {
    teclasPresionadas.insert(tecla);
}

void Jugador::quitarTeclaPresionada(int tecla) {
    teclasPresionadas.remove(tecla);
    if (teclasPresionadas.isEmpty()) {
        direccionActual = 0;
        temporizadorAnimacion->start();
    }
}

void Jugador::manejarInput() {
    if (muriendo || teclasPresionadas.isEmpty()) return;

    // Prioridad de movimiento basada en la última tecla presionada
    if (teclasPresionadas.contains(Qt::Key_W) || teclasPresionadas.contains(Qt::Key_Up)) {
        moverEnDireccion(Qt::Key_W);
    } else if (teclasPresionadas.contains(Qt::Key_S) || teclasPresionadas.contains(Qt::Key_Down)) {
        moverEnDireccion(Qt::Key_S);
    } else if (teclasPresionadas.contains(Qt::Key_A) || teclasPresionadas.contains(Qt::Key_Left)) {
        moverEnDireccion(Qt::Key_A);
    } else if (teclasPresionadas.contains(Qt::Key_D) || teclasPresionadas.contains(Qt::Key_Right)) {
        moverEnDireccion(Qt::Key_D);
    } else if (teclasPresionadas.contains(Qt::Key_Space)) {
        colocarBomba();
    }
}

void Jugador::moverEnDireccion(int tecla) {
    if (muriendo) return;

    QPointF nuevaPos = pos();
    int nuevaDireccion = direccionActual;

    switch (tecla) {
    case Qt::Key_W:
    case Qt::Key_Up:
        nuevaPos.ry() -= velocidad;
        nuevaDireccion = 1;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        nuevaPos.ry() += velocidad;
        nuevaDireccion = 2;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        nuevaPos.rx() -= velocidad;
        nuevaDireccion = 3;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        nuevaPos.rx() += velocidad;
        nuevaDireccion = 4;
        break;
    default:
        return;
    }

    if (puedeMoversea(nuevaPos)) {
        setPos(nuevaPos);
        if (direccionActual != nuevaDireccion) {
            direccionActual = nuevaDireccion;
        }
        actualizarSpriteDireccion(tecla);
        temporizadorAnimacion->stop();

        // Verificar colisiones con enemigos
        verificarColisionEnemigos();
    }
}

void Jugador::actualizarSpriteDireccion(int tecla) {
    switch (tecla) {
    case Qt::Key_W:
    case Qt::Key_Up:
        if (indiceArriba >= spritesArriba.size()) indiceArriba = 0;
        setPixmap(spritesArriba[indiceArriba]);
        indiceArriba++;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        if (indiceAbajo >= spritesAbajo.size()) indiceAbajo = 0;
        setPixmap(spritesAbajo[indiceAbajo]);
        indiceAbajo++;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        if (indiceIzquierda >= spritesIzquierda.size()) indiceIzquierda = 0;
        setPixmap(spritesIzquierda[indiceIzquierda]);
        indiceIzquierda++;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        if (indiceDerecha >= spritesDerecha.size()) indiceDerecha = 0;
        setPixmap(spritesDerecha[indiceDerecha]);
        indiceDerecha++;
        break;
    }
}

void Jugador::actualizarMovimiento() {
    manejarInput();

    // Efecto de parpadeo si está inmune
    if (inmune) {
        visible = !visible;
        setVisible(visible);
    }
}

void Jugador::resetearASpritePorDefecto() {
    if (!muriendo) {
        setPixmap(spriteDefecto);
    }
}

void Jugador::verificarColisionEnemigos() {
    if (inmune || muriendo) return;

    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem* item : items) {
        Enemigo* enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo && !enemigo->estaMuriendo()) {
            activarAnimacionMuerte();
            emit jugadorMurio();
            break;
        }
    }
}

void Jugador::setPosicionInicial(const QPointF& pos) {
    posicionInicial = pos;
    setPos(pos);
}

void Jugador::iniciarAnimacionMuerte(const QStringList& sprites) {
    QTimer* timerMuerte = new QTimer(this);
    int* indice = new int(0);
    int duracionFrame = 120; // Un poco más lento para ver mejor la animación

    connect(timerMuerte, &QTimer::timeout, this, [=]() mutable {
        if (*indice < sprites.size()) {
            setPixmap(QPixmap(sprites[*indice]).scaled(35, 35));
            setVisible(true); // Asegurar que esté visible durante la animación
            (*indice)++;
        } else {
            // Animación completada
            timerMuerte->stop();
            delete timerMuerte;
            delete indice;

            qDebug() << "[JUGADOR] Animación de muerte completada.";

            // Restaurar jugador
            setPos(posicionInicial);        // Volver a posición inicial
            setPixmap(spriteDefecto);       // Restaurar sprite por defecto
            setVisible(true);               // Asegurar visibilidad
            activarInmunidad(3000);         // Inmunidad 3 segundos
            muriendo = false;               // Permitir movimiento nuevamente

            // Reactivar timer de movimiento
            //temporizadorMovimiento->start(30);
            temporizadorMovimiento->start(16); // ~25 FPS


            emit jugadorMurio();            // Notificar al sistema
            qDebug() << "[JUGADOR] Jugador restaurado en posición inicial:" << posicionInicial;
        }
    });

    timerMuerte->start(duracionFrame);
}

void Jugador::colocarBomba() {
    if (bombasActivas.size() >= maximoBombas || muriendo) return;

    const int gridSize = 40;
    const int alturaPanel = 50;

    // Calcular posición alineada a la cuadrícula, ajustando el desfase del panel
    int gridX = qRound(pos().x() / gridSize) * gridSize;
    int gridY = qRound((pos().y() - alturaPanel) / gridSize) * gridSize + alturaPanel;

    // Verificar si ya hay una bomba en esta posición
    QRectF rectBomba(gridX, gridY, gridSize, gridSize);
    if (scene()) {
        QList<QGraphicsItem*> items = scene()->items(rectBomba);
        for (QGraphicsItem* item : items) {
            if (dynamic_cast<Bomba*>(item)) {
                return;
            }
        }
    }

    // Crear bomba perfectamente centrada
    Bomba *bomba = new Bomba();
    bomba->setPos(gridX, gridY); // Posición exacta de la cuadrícula ajustada
    bomba->setRangoExplosion(rangoExplosion);
    connect(bomba, &Bomba::explotada, this, &Jugador::alBombaExplotada);

    if (scene()) scene()->addItem(bomba);
    bombasActivas.append(bomba);
    bomba->iniciarCuentaRegresiva();

    emit bombaColocada();
}

void Jugador::activarInmunidad(int duracionMs) {
    inmune = true;
    temporizadorInmunidad->start(duracionMs);
}

void Jugador::finalizarInmunidad() {
    inmune = false;
    setVisible(true);
    visible = true;
}

void Jugador::alBombaExplotada(Bomba *bomba) {
    bombasActivas.removeOne(bomba);
    qDebug() << "Bomba explotó. Bombas activas restantes:" << bombasActivas.size();
}

void Jugador::alEnemigoDestruido() {
    emit enemigoDestruido();
}

void Jugador::alLadrilloDestruido() {
    emit ladrilloDestruido();
}

void Jugador::activarAnimacionMuerte() {
    if (muriendo) return; // Evitar múltiples llamadas

    muriendo = true;

    // Detener movimiento pero mantener visible para la animación
    temporizadorMovimiento->stop();

    qDebug() << "[JUGADOR] Activando animación de muerte.";

    QStringList spritesMuerte = {
        ":/images/personajecolision1.png",
        ":/images/personajecolision2.png",
        ":/images/personajecolision3.png",
        ":/images/personajecolision4.png",
        ":/images/personajecolision5.png",
        ":/images/personajecolision6.png",
        ":/images/personajecolision7.png"
    };
    iniciarAnimacionMuerte(spritesMuerte);
    qDebug() << "[JUGADOR] Fin de activarAnimacionMuerte.";
}
