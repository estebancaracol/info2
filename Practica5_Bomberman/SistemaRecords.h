#ifndef SISTEMARECORDS_H
#define SISTEMARECORDS_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QSettings>

struct Record {
    QString nombreJugador;
    int puntuacion;
    int nivel;
    QDateTime fecha;
    int tiempoJuego; // en segundos

    Record() : puntuacion(0), nivel(1), tiempoJuego(0) {}
    Record(const QString& nombre, int puntos, int nvl, int tiempo)
        : nombreJugador(nombre), puntuacion(puntos), nivel(nvl),
        fecha(QDateTime::currentDateTime()), tiempoJuego(tiempo) {}
};

class SistemaRecords : public QObject {
    Q_OBJECT

public:
    static SistemaRecords* getInstance();

    void agregarRecord(const QString& nombreJugador, int puntuacion, int nivel, int tiempoJuego);
    QList<Record> obtenerMejoresRecords(int cantidad = 10);
    void guardarRecords();
    void cargarRecords();
    bool esNuevoRecord(int puntuacion);

    int getMejorPuntuacion() const;
    QString formatearRecord(const Record& record) const;

private:
    explicit SistemaRecords(QObject *parent = nullptr);
    static SistemaRecords* instancia;

    QList<Record> records;
    QSettings* configuracion;

    void ordenarRecords();
};

#endif // SISTEMARECORDS_H
