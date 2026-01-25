#include "Block.h"
#include <QPixmap>
#include <QDebug>

Block::Block(const QString &spritePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) {
    QPixmap sprite(spritePath);
    if (!sprite.isNull()) {
        // Escalar a 40x40
        setPixmap(sprite.scaled(40, 40));
    } else {
        qDebug() << "Error cargar sprite:" << spritePath;
    }
}
