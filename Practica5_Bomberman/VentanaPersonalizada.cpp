#include "VentanaPersonalizada.h"
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>

VentanaPersonalizada::VentanaPersonalizada(const QString &tituloTexto, const QStringList &botones, QWidget *parent)
    : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(500, 400);

    // Fondo oscuro con borde redondeado
    QWidget *contenedor = new QWidget(this);
    contenedor->setObjectName("contenedor");
    contenedor->setStyleSheet("#contenedor { background-color: rgba(30, 30, 30, 220); border-radius: 20px; }");
    contenedor->setGeometry(0, 0, width(), height());

    QVBoxLayout *layout = new QVBoxLayout(contenedor);
    layout->setContentsMargins(20, 30, 20, 20);
    layout->setSpacing(20);

    // Cargar fuente retro
    int idFuente = QFontDatabase::addApplicationFont(":/fuente/PressStart2P-Regular.ttf");
    QString nombreFuente = QFontDatabase::applicationFontFamilies(idFuente).at(0);

    // Título estilo retro
    tituloAnimado = new QLabel(tituloTexto);
    tituloAnimado->setAlignment(Qt::AlignCenter);
    tituloAnimado->setStyleSheet(QString("font-family: '%1'; font-size: 18px; color: #e74c3c;").arg(nombreFuente));
    layout->addWidget(tituloAnimado);

    animarTitulo();

    // Sombras sutiles
    QGraphicsDropShadowEffect *sombra = new QGraphicsDropShadowEffect(this);
    sombra->setBlurRadius(15);
    sombra->setOffset(0, 4);
    sombra->setColor(Qt::black);
    contenedor->setGraphicsEffect(sombra);

    // Crear botones
    for (const QString &textoBoton : botones) {
        QPushButton *boton = new QPushButton(textoBoton);
        boton->setCursor(Qt::PointingHandCursor);
        boton->setMinimumHeight(40);
        boton->setStyleSheet(
            "QPushButton {"
            " background-color: rgba(0, 255, 0, 60);"
            " color: white;"
            " font-size: 14px;"
            " border: 2px solid #00FF99;"
            " border-radius: 12px;"
            " font-family: 'Arial Black';"
            "}"
            "QPushButton:hover {"
            " background-color: rgba(0, 255, 0, 120);"
            "}"
            );

        layout->addWidget(boton);

        connect(boton, &QPushButton::clicked, this, [this, textoBoton]() {
            emit opcionSeleccionada(textoBoton);
            this->close();
        });
    }
}

void VentanaPersonalizada::animarTitulo() {
    coloresTitulo = {
        "#f1c40f", "#e74c3c", "#e67e22", "#f39c12",
        "#27ae60", "#3498db", "#9b59b6", "#1abc9c"
    };
    indiceColor = 0;

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, [this]() {
        QString colorActual = coloresTitulo.at(indiceColor);
        tituloAnimado->setStyleSheet(QString("font-family: 'Press Start 2P'; font-size: 18px; color: %1;").arg(colorActual));
        indiceColor = (indiceColor + 1) % coloresTitulo.size();
    });
    timerAnimacion->start(300); // cambia color cada 300 ms
}
