#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    Block(const QString &spritePath, QGraphicsItem *parent = nullptr);
};

#endif // BLOCK_H
