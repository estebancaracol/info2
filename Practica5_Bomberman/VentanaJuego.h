#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QLabel>
#include <QTimer>
#include <QSoundEffect>
#include <QMediaPlayer>


class VentanaJuego : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaJuego(QWidget *parent = nullptr);

private slots:
    void iniciarPartida();
    void mostrarRecords();
    void animarTitulo();

private:
    QGraphicsScene* scene;
    QPushButton *botonIniciar;
    QPushButton *botonRecords;
    QPushButton *botonSalir;

    QSoundEffect* sonidoInicio;
    QSoundEffect* sonidoBoton;

    // Para animación del título
    QLabel *labelTitulo;
    QTimer *timerAnimacionTitulo;
    int colorIndex;
};

#endif // VENTANAJUEGO_H
