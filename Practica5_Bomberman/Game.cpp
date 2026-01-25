#include "Game.h"

#include <QKeyEvent>

Game::Game(QWidget *parent) : QMainWindow(parent) {
    // Configurar escena
    scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, 920, 570);

    // Evitar redimensionar ventana
    this->setFixedSize(920, 570);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle("Bomberman - Juego");
    resize(920, 570);

    // Crear escena
    escena = new Escena(this);
    connect(escena, &Escena::volverAlMenu, this, &Game::manejarVolver);
    escena->crearMapa();
    escena->inicializarPersonajes();

    // Crear vista
    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(920, 570);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(vista);

    escena->mostrarTextoTemporal("¡Pulsa ESC para volver al menú¡", 3000);  // 3 segundos

}

void Game::manejarVolver() {
    emit volverAlMenu();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        manejarVolver();
        return;
    }

    // Reenviar teclas al jugador a través de la escena
    if (escena) {
        escena->manejarTeclaPresionada(event->key());
    }

    QMainWindow::keyPressEvent(event);
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    // Reenviar liberación de teclas al jugador a través de la escena
    if (escena) {
        escena->manejarTeclaLiberada(event->key());
    }

    QMainWindow::keyReleaseEvent(event);
}

