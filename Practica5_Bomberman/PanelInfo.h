#ifndef PANELINFO_H
#define PANELINFO_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>


class PanelInfo : public QGraphicsRectItem
{
public:

    PanelInfo(QGraphicsItem *parent = nullptr);
    void actualizarTiempo(int tiempo);

    void actualizarPuntuacion(int puntuacion);

    void actualizarVidas(int vidas);

    void actualizarNivel(int nivel);

private:
    QGraphicsTextItem *textoTiempo;
    QGraphicsTextItem *textoPuntuacion;
    QGraphicsTextItem *textoVidas;
    QGraphicsTextItem *textoNivel;
};

#endif // PANELINFO_H
