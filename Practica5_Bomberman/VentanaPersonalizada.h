#ifndef VENTANAPERSONALIZADA_H
#define VENTANAPERSONALIZADA_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

class VentanaPersonalizada : public QDialog {
    Q_OBJECT
public:
    explicit VentanaPersonalizada(const QString &tituloTexto, const QStringList &botones, QWidget *parent = nullptr);

signals:
    void opcionSeleccionada(const QString &opcion);

private:
    QLabel *tituloAnimado;
    QTimer *timerAnimacion;
    QStringList coloresTitulo;
    int indiceColor;
    void animarTitulo();
};

#endif // VENTANAPERSONALIZADA_H

