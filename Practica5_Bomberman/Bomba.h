#ifndef BOMBA_H
#define BOMBA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QVector>
#include <QPixmap>

class Bomba : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Bomba(QGraphicsItem *parent = nullptr);
    void iniciarCuentaRegresiva(int milisegundos = 2000);
    void setRangoExplosion(int rango) { rangoExplosion = rango; }
    int getRangoExplosion() const { return rangoExplosion; }

signals:
    void explotada(Bomba* self);
    void explosion(const QPointF& centro, int rango); // Nueva señal para manejar puntos

private slots:
    void explotar();
    void actualizarAnimacion();

private:
    void cargarSprites();
    void crearExplosion();
    void crearEfectoExplosion(const QPointF& posicion);
    void verificarColisionesEnPosicion(const QPointF& posicion);

    QTimer *temporizador;
    QTimer *temporizadorAnimacion;
    QVector<QPixmap> sprites;
    int spriteActual;
    int rangoExplosion;
    bool explotando;
};

#endif // BOMBA_H
