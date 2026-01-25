#include "Entidad.h"
#include "Pared.h"
#include "Ladrillo.h"

#include <QGraphicsScene>

Entidad::Entidad(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {}

void Entidad::mover(QPointF delta) {
    setPos(pos() + delta);
}

bool Entidad::puedeMoversea(const QPointF &nuevaPos) {
    QRectF nuevosBordes(nuevaPos, boundingRect().size());
    if (!scene()) return false;
    QList<QGraphicsItem*> elementos = scene()->items(nuevosBordes);
    for (QGraphicsItem* elemento : elementos) {
        if (elemento == this) continue;
        if (dynamic_cast<Pared*>(elemento) || dynamic_cast<Ladrillo*>(elemento)) {
            return false;
        }
    }
    return true;
}

void Entidad::cargarSprites(const QStringList &rutas) {
    sprites.clear();
    for (const QString &ruta : rutas) {
        sprites.append(QPixmap(ruta).scaled(35, 35));
    }
    if (!sprites.isEmpty()) setPixmap(sprites.first());
}

void Entidad::avanzarSprite(QVector<QPixmap> &lista, int &indice) {
    if (lista.isEmpty()) return;
    if (indice >= lista.size()) indice = 0;
    setPixmap(lista[indice]);
    indice++;
}

void Entidad::iniciarAnimacionMuerte(const QStringList &rutasMuerte, int velocidadMs) {
    spritesMuerte.clear();
    for (const QString &ruta : rutasMuerte)
        spritesMuerte.append(QPixmap(ruta).scaled(35, 35));

    if (spritesMuerte.isEmpty()) return;

    setPixmap(spritesMuerte[0]);
    frameMuerte = 0;

    if (!timerMuerte) {
        timerMuerte = new QTimer(this);
        connect(timerMuerte, &QTimer::timeout, this, &Entidad::actualizarAnimacionMuerte);
    }

    timerMuerte->start(velocidadMs);
}

void Entidad::actualizarAnimacionMuerte() {
    ++frameMuerte;
    if (frameMuerte < spritesMuerte.size()) {
        setPixmap(spritesMuerte[frameMuerte]);
    } else {
        timerMuerte->stop();
        if (scene()) scene()->removeItem(this);
        deleteLater();
    }
}
