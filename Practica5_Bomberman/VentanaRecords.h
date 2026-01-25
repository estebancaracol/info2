#ifndef VENTANARECORDS_H
#define VENTANARECORDS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include "SistemaRecords.h"

class VentanaRecords : public QDialog {
    Q_OBJECT

public:
    explicit VentanaRecords(QWidget *parent = nullptr);
    explicit VentanaRecords(int puntuacion, int nivel, int tiempoJuego, QWidget *parent = nullptr);

    void mostrarRecords();
    void configurarVentanaNuevoRecord(int puntuacion, int nivel, int tiempoJuego);

private slots:
    void guardarNuevoRecord();
    void cerrarVentana();

private:
    void configurarUI();
    void actualizarListaRecords();

    QVBoxLayout *layoutPrincipal;
    QLabel *labelTitulo;
    QLabel *labelInstrucciones;
    QListWidget *listaRecords;
    QLineEdit *inputNombre;
    QPushButton *botonGuardar;
    QPushButton *botonCerrar;

    bool esModoNuevoRecord;
    int puntuacionActual;
    int nivelActual;
    int tiempoActual;
};

#endif // VENTANARECORDS_H
