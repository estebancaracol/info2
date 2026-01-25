#include "PanelInfo.h"

#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#include <QPen>

PanelInfo::PanelInfo(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // Cargar fuente retro
    int idFuente = QFontDatabase::addApplicationFont(":/fuente/PressStart2P-Regular.ttf");
    QString familia = QFontDatabase::applicationFontFamilies(idFuente).at(0);
    QFont fuenteRetro(familia, 10);

    // Configurar el panel
    setRect(0, 0, 920, 50);
    setBrush(QBrush(Qt::lightGray));
    setPen(Qt::NoPen);

    // Nivel (posición más a la izquierda)
    textoNivel = new QGraphicsTextItem("NIVEL: 1", this);
    textoNivel->setDefaultTextColor(Qt::white);
    textoNivel->setFont(fuenteRetro);
    textoNivel->setPos(20, 15);

    // Tiempo
    textoTiempo = new QGraphicsTextItem("TIEMPO: 150", this);
    textoTiempo->setDefaultTextColor(Qt::white);
    textoTiempo->setFont(fuenteRetro);
    textoTiempo->setPos(200, 15);

    // Puntaje
    textoPuntuacion = new QGraphicsTextItem("PUNTOS: 0000", this);
    textoPuntuacion->setDefaultTextColor(Qt::white);
    textoPuntuacion->setFont(fuenteRetro);
    textoPuntuacion->setPos(450, 15);

    // Vidas
    textoVidas = new QGraphicsTextItem("VIDAS: 3", this);
    textoVidas->setDefaultTextColor(Qt::white);
    textoVidas->setFont(fuenteRetro);
    textoVidas->setPos(700, 15);
}

void PanelInfo::actualizarTiempo(int tiempo)
{
    textoTiempo->setPlainText("TIEMPO: " + QString::number(tiempo));
}

void PanelInfo::actualizarPuntuacion(int puntuacion)
{
    textoPuntuacion->setPlainText("PUNTOS: " + QString::number(puntuacion));
}

void PanelInfo::actualizarVidas(int vidas)
{
    textoVidas->setPlainText("VIDAS: " + QString::number(vidas));
}

void PanelInfo::actualizarNivel(int nivel)
{
    textoNivel->setPlainText("NIVEL: " + QString::number(nivel));
}
