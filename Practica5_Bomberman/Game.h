#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

#include "Escena.h"

class Game : public QMainWindow {
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);

signals:
    void volverAlMenu();

private slots:
    void manejarVolver();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QGraphicsScene* scene;
    QGraphicsView *vista;
    Escena *escena;
    QPushButton *botonVolver;
};

#endif // GAME_H
