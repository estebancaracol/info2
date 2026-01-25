#include "VentanaJuego.h"
#include "Game.h"
#include "VentanaRecords.h"
#include "SistemaRecords.h"

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPixmap>
#include <QPalette>
#include <QFontDatabase>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QGraphicsDropShadowEffect>

VentanaJuego::VentanaJuego(QWidget *parent) : QMainWindow(parent), colorIndex(0) {
    setFixedSize(920, 570);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("BOMBERMAN 💣 Menú Principal");

    // Sonidos
    sonidoInicio = new QSoundEffect(this);
    sonidoInicio->setSource(QUrl("qrc:/sounds/inicio.wav"));
    sonidoInicio->setVolume(0.5);
    sonidoInicio->play();

    sonidoBoton = new QSoundEffect(this);
    sonidoBoton->setSource(QUrl("qrc:/sounds/boton.wav"));
    sonidoBoton->setVolume(0.8);

    QWidget *widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);
    layoutPrincipal->setSpacing(20);
    layoutPrincipal->setContentsMargins(100, 40, 100, 40);

    // Fuente personalizada
    int idFuente = QFontDatabase::addApplicationFont(":/fuente/PressStart2P-Regular.ttf");
    QString nombreFuente = QFontDatabase::applicationFontFamilies(idFuente).at(0);

    // Título animado
    labelTitulo = new QLabel("💣 BOMBERMAN 💣");
    labelTitulo->setAlignment(Qt::AlignCenter);
    QFont fuenteTitulo;
    fuenteTitulo.setFamily(nombreFuente);
    fuenteTitulo.setPointSize(24);
    fuenteTitulo.setBold(true);
    labelTitulo->setFont(fuenteTitulo);

    // Sombra al título
    auto sombraTitulo = new QGraphicsDropShadowEffect();
    sombraTitulo->setBlurRadius(10);
    sombraTitulo->setOffset(2, 2);
    sombraTitulo->setColor(Qt::black);
    labelTitulo->setGraphicsEffect(sombraTitulo);

    timerAnimacionTitulo = new QTimer(this);
    connect(timerAnimacionTitulo, &QTimer::timeout, this, &VentanaJuego::animarTitulo);
    timerAnimacionTitulo->start(500);
    animarTitulo();

    QLabel *labelImagen = new QLabel();
    QPixmap imagenBomberman(":/images/bomberman.png");
    if (!imagenBomberman.isNull()) {
        labelImagen->setPixmap(imagenBomberman.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        labelImagen->setAlignment(Qt::AlignCenter);
        labelImagen->setStyleSheet("margin: 10px;");
    }

    QLabel *labelSubtitulo = new QLabel("¡Coloca bombas y derrota a tus enemigos!");
    labelSubtitulo->setAlignment(Qt::AlignCenter);
    QFont fuenteSubtitulo;
    fuenteSubtitulo.setPointSize(12);
    fuenteSubtitulo.setBold(true);
    labelSubtitulo->setFont(fuenteSubtitulo);
    labelSubtitulo->setStyleSheet("color: #ecf0f1; margin: 5px;");

    SistemaRecords* sistema = SistemaRecords::getInstance();
    int mejorPuntuacion = sistema->getMejorPuntuacion();
    QLabel *labelMejorRecord = new QLabel(QString("🏆 Mejor Record: %1 puntos").arg(mejorPuntuacion));
    labelMejorRecord->setAlignment(Qt::AlignCenter);
    labelMejorRecord->setStyleSheet("color: #f39c12; font-size: 15px; font-weight: bold; margin: 5px;");

    // Estilo botones
    QString estiloBoton = R"(
    QPushButton {
        font-family: Arial Black, sans-serif;
        font-size: 15px;
        background-color: #2ecc71;
        border: 2px solid #27ae60;
        border-radius: 10px;
        padding: 8px;
        color: white;
    }
    QPushButton:hover {
        background-color: #27ae60;
    }
    QPushButton:pressed {
        background-color: #1e8449;
        padding-left: 10px;
        padding-top: 10px;
    }
)";


    botonIniciar = new QPushButton("🎮 INICIAR PARTIDA");
    botonIniciar->setMinimumHeight(40);
    botonIniciar->setStyleSheet(estiloBoton);

    botonRecords = new QPushButton("🏆 VER RECORDS");
    botonRecords->setMinimumHeight(40);
    botonRecords->setStyleSheet(estiloBoton);

    botonSalir = new QPushButton("🚪 SALIR");
    botonSalir->setMinimumHeight(40);
    botonSalir->setStyleSheet(estiloBoton);

    layoutPrincipal->addWidget(labelImagen);
    layoutPrincipal->addWidget(labelTitulo);
    layoutPrincipal->addWidget(labelSubtitulo);
    layoutPrincipal->addWidget(labelMejorRecord);
    layoutPrincipal->addSpacing(20);
    layoutPrincipal->addWidget(botonIniciar);
    layoutPrincipal->addWidget(botonRecords);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();

    connect(botonIniciar, &QPushButton::clicked, this, [this]() {
        sonidoBoton->play();
        iniciarPartida();
    });

    connect(botonRecords, &QPushButton::clicked, this, [this]() {
        sonidoBoton->play();
        mostrarRecords();
    });

    connect(botonSalir, &QPushButton::clicked, this, [this]() {
        sonidoBoton->play();
        close();
    });
}

void VentanaJuego::iniciarPartida() {
    this->hide();
    Game *juego = new Game();
    connect(juego, &Game::volverAlMenu, this, [this, juego]() {
        juego->close();
        this->show();
    });
    juego->show();
}

void VentanaJuego::mostrarRecords() {
    VentanaRecords *ventanaRecords = new VentanaRecords(this);
    ventanaRecords->exec();
    delete ventanaRecords;
}

void VentanaJuego::animarTitulo() {
    QStringList colores = {
        "#f1c40f", "#e74c3c", "#e67e22", "#f39c12",
        "#27ae60", "#3498db", "#9b59b6", "#1abc9c"
    };

    QString colorActual = colores[colorIndex % colores.size()];
    colorIndex++;

    QString estilo = QString(
                         "color: %1; "
                         "margin: 10px; "
                         "border: 1px solid %2; "
                         "border-radius: 10px; "
                         "padding: 10px; "
                         "background: rgba(255,255,255,0.1);"
                         ).arg(colorActual, colorActual);

    labelTitulo->setStyleSheet(estilo);
}
