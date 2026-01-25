// #include "SistemaRecords.h"
// #include <QStandardPaths>
// #include <QDir>
// #include <QDebug>
// #include <algorithm>

// SistemaRecords* SistemaRecords::instancia = nullptr;

// SistemaRecords::SistemaRecords(QObject *parent) : QObject(parent) {
//     // Configurar ruta de almacenamiento
//     QString rutaConfig = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
//     QDir dir;
//     dir.mkpath(rutaConfig);

//     configuracion = new QSettings(rutaConfig + "/bomberman_records.ini", QSettings::IniFormat, this);
//     cargarRecords();
// }

// SistemaRecords* SistemaRecords::getInstance() {
//     if (!instancia) {
//         instancia = new SistemaRecords();
//     }
//     return instancia;
// }

// void SistemaRecords::agregarRecord(const QString& nombreJugador, int puntuacion, int nivel, int tiempoJuego) {
//     Record nuevoRecord(nombreJugador, puntuacion, nivel, tiempoJuego);
//     records.append(nuevoRecord);
//     ordenarRecords();

//     // Mantener solo los mejores 20 records
//     if (records.size() > 20) {
//         records = records.mid(0, 20);
//     }

//     guardarRecords();
//     qDebug() << "Nuevo record agregado:" << nombreJugador << "con" << puntuacion << "puntos";
// }

// QList<Record> SistemaRecords::obtenerMejoresRecords(int cantidad) {
//     int limite = qMin(cantidad, records.size());
//     return records.mid(0, limite);
// }

// void SistemaRecords::ordenarRecords() {
//     std::sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
//         if (a.puntuacion != b.puntuacion) {
//             return a.puntuacion > b.puntuacion; // Mayor puntuación primero
//         }
//         if (a.nivel != b.nivel) {
//             return a.nivel > b.nivel; // Mayor nivel primero
//         }
//         return a.tiempoJuego < b.tiempoJuego; // Menor tiempo primero
//     });
// }

// void SistemaRecords::guardarRecords() {
//     configuracion->beginWriteArray("records");
//     for (int i = 0; i < records.size(); ++i) {
//         configuracion->setArrayIndex(i);
//         configuracion->setValue("nombreJugador", records[i].nombreJugador);
//         configuracion->setValue("puntuacion", records[i].puntuacion);
//         configuracion->setValue("nivel", records[i].nivel);
//         configuracion->setValue("fecha", records[i].fecha);
//         configuracion->setValue("tiempoJuego", records[i].tiempoJuego);
//     }
//     configuracion->endArray();
//     configuracion->sync();
// }

// void SistemaRecords::cargarRecords() {
//     records.clear();
//     int size = configuracion->beginReadArray("records");
//     for (int i = 0; i < size; ++i) {
//         configuracion->setArrayIndex(i);
//         Record record;
//         record.nombreJugador = configuracion->value("nombreJugador").toString();
//         record.puntuacion = configuracion->value("puntuacion").toInt();
//         record.nivel = configuracion->value("nivel").toInt();
//         record.fecha = configuracion->value("fecha").toDateTime();
//         record.tiempoJuego = configuracion->value("tiempoJuego").toInt();
//         records.append(record);
//     }
//     configuracion->endArray();
//     ordenarRecords();
// }

// bool SistemaRecords::esNuevoRecord(int puntuacion) {
//     if (records.size() < 10) return true; // Si hay menos de 10 records, siempre es nuevo
//     return puntuacion > records.last().puntuacion;
// }

// int SistemaRecords::getMejorPuntuacion() const {
//     if (records.isEmpty()) return 0;
//     return records.first().puntuacion;
// }

// QString SistemaRecords::formatearRecord(const Record& record) const {
//     return QString("%1 - %2 pts (Nivel %3) - %4")
//     .arg(record.nombreJugador)
//         .arg(record.puntuacion)
//         .arg(record.nivel)
//         .arg(record.fecha.toString("dd/MM/yyyy"));
// }

#include "SistemaRecords.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <algorithm>

SistemaRecords* SistemaRecords::instancia = nullptr;

SistemaRecords::SistemaRecords(QObject *parent) : QObject(parent) {
    // Configurar ruta de almacenamiento
    QString rutaConfig = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    dir.mkpath(rutaConfig);

    configuracion = new QSettings(rutaConfig + "/bomberman_records.ini", QSettings::IniFormat, this);
    cargarRecords();
}

SistemaRecords* SistemaRecords::getInstance() {
    if (!instancia) {
        instancia = new SistemaRecords();
    }
    return instancia;
}

void SistemaRecords::agregarRecord(const QString& nombreJugador, int puntuacion, int nivel, int tiempoJuego) {
    Record nuevoRecord(nombreJugador, puntuacion, nivel, tiempoJuego);
    records.append(nuevoRecord);
    ordenarRecords();

    // Mantener solo los mejores 20 records
    if (records.size() > 20) {
        records = records.mid(0, 20);
    }

    guardarRecords();
    qDebug() << "Nuevo record agregado:" << nombreJugador << "con" << puntuacion << "puntos";
}

QList<Record> SistemaRecords::obtenerMejoresRecords(int cantidad) {
    int limite = qMin(cantidad, records.size());
    return records.mid(0, limite);
}

void SistemaRecords::ordenarRecords() {
    std::sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
        if (a.puntuacion != b.puntuacion) {
            return a.puntuacion > b.puntuacion; // Mayor puntuación primero
        }
        if (a.nivel != b.nivel) {
            return a.nivel > b.nivel; // Mayor nivel primero
        }
        return a.tiempoJuego < b.tiempoJuego; // Menor tiempo primero
    });
}

void SistemaRecords::guardarRecords() {
    configuracion->beginWriteArray("records");
    for (int i = 0; i < records.size(); ++i) {
        configuracion->setArrayIndex(i);
        configuracion->setValue("nombreJugador", records[i].nombreJugador);
        configuracion->setValue("puntuacion", records[i].puntuacion);
        configuracion->setValue("nivel", records[i].nivel);
        configuracion->setValue("fecha", records[i].fecha);
        configuracion->setValue("tiempoJuego", records[i].tiempoJuego);
    }
    configuracion->endArray();
    configuracion->sync();

    qDebug() << "Records guardados. Total de records:" << records.size();
}

void SistemaRecords::cargarRecords() {
    records.clear();
    int size = configuracion->beginReadArray("records");
    for (int i = 0; i < size; ++i) {
        configuracion->setArrayIndex(i);
        Record record;
        record.nombreJugador = configuracion->value("nombreJugador").toString();
        record.puntuacion = configuracion->value("puntuacion").toInt();
        record.nivel = configuracion->value("nivel").toInt();
        record.fecha = configuracion->value("fecha").toDateTime();
        record.tiempoJuego = configuracion->value("tiempoJuego").toInt();
        records.append(record);
    }
    configuracion->endArray();
    ordenarRecords();

    qDebug() << "Records cargados. Total de records:" << records.size();
}

// FUNCIÓN CORREGIDA: Ahora verifica correctamente si es un nuevo record
bool SistemaRecords::esNuevoRecord(int puntuacion) {
    // Si no hay records, cualquier puntuación es un nuevo record
    if (records.isEmpty()) {
        qDebug() << "No hay records existentes, cualquier puntuación es nueva";
        return true;
    }

    // Si hay menos de 10 records, siempre es un nuevo record
    if (records.size() < 10) {
        qDebug() << "Menos de 10 records, puntuación automáticamente califica";
        return true;
    }

    // Si hay 10 o más records, verificar si la puntuación es mejor que el peor record (posición 9)
    bool esNuevo = puntuacion > records[9].puntuacion;
    qDebug() << "Verificando puntuación" << puntuacion << "vs peor record" << records[9].puntuacion << "- Es nuevo:" << esNuevo;
    return esNuevo;
}

int SistemaRecords::getMejorPuntuacion() const {
    if (records.isEmpty()) return 0;
    return records.first().puntuacion;
}

QString SistemaRecords::formatearRecord(const Record& record) const {
    return QString("%1 - %2 pts (Nivel %3) - %4")
    .arg(record.nombreJugador)
        .arg(record.puntuacion)
        .arg(record.nivel)
        .arg(record.fecha.toString("dd/MM/yyyy"));
}
