#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QVector>
#include <QTimer>
#include <QPointF>
#include <QStringList>

class Entidad : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Entidad(QGraphicsItem *parent = nullptr);

    virtual void mover(QPointF delta);
    virtual bool puedeMoversea(const QPointF& nuevaPos);
    void cargarSprites(const QStringList &rutas);
    void iniciarAnimacionMuerte(const QStringList &rutasMuerte, int velocidadMs = 100);
    void avanzarSprite(QVector<QPixmap> &lista, int &indice);

protected slots:
    void actualizarAnimacionMuerte();

protected:
    QVector<QPixmap> sprites;
    QVector<QPixmap> spritesMuerte;
    int indiceSprite = 0;
    int frameMuerte = 0;
    QTimer* timerMuerte = nullptr;

};

#endif // ENTIDAD_H
