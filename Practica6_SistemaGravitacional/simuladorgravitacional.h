// #ifndef SIMULADORGRAVITACIONAL_H
// #define SIMULADORGRAVITACIONAL_H
// #include <QObject>
// #include <QTimer>
// #include <QList>
// #include <QString>
// #include <QTextStream>
// #include <QFile>
// #include <QDebug>
// #include "cuerpoEstelar.h"

// class SimuladorGravitacional : public QObject
// {
//     Q_OBJECT
// public:
//     explicit SimuladorGravitacional(QObject *parent = nullptr);
//     ~SimuladorGravitacional();
//     // Gestión de cuerpos estelares
//     void agregarCuerpo(CuerpoEstelar* cuerpo);
//     void eliminarTodosCuerpos();
//     const QList<CuerpoEstelar*>& getCuerpos() const { return m_cuerpos; }
//     int getNumCuerpos() const { return m_cuerpos.size(); }
//     // Control de la simulación
//     void iniciarSimulacion();
//     void pausarSimulacion();
//     void reiniciarSimulacion();
//     bool estaSimulando() const { return m_simulando; }

//     // Configuración de parámetros
//     void setDeltaTiempo(double dt) { m_deltaT = dt; }
//     void setIntervaloActualizacion(int ms) { m_timer->setInterval(ms); }
//     double getDeltaTiempo() const { return m_deltaT; }

//     // Archivo CSV - Entrada y salida
//     bool cargarDesdeCSV(const QString& rutaArchivo);
//     bool guardarTrayectoriasCSV(const QString& rutaArchivo) const;
//     bool guardarEstadoActualCSV(const QString& rutaArchivo) const;

//     // Estadísticas y información
//     int getIteracion() const { return m_iteracion; }
//     double getTiempoSimulacion() const { return m_iteracion * m_deltaT; }

//     // Configuración de sistemas predefinidos
//     void configurarSistema1();
//     void configurarSistema2();
// signals:
//     void simulacionIniciada();
//     void simulacionPausada();
//     void simulacionReiniciada();
//     void estadoActualizado();
//     void errorSimulacion(const QString& mensaje);
// public slots:
//     void actualizarSimulacion();
// private:
//     QList<CuerpoEstelar*> m_cuerpos;
//     QTimer* m_timer;
//     bool m_simulando;
//     double m_deltaT;              // Paso de tiempo (Δt = 1 según especificaciones)
//     int m_iteracion;

//     // Historial para exportación
//     QList<QList<QPointF>> m_historiaTrayectorias;

//     // Métodos privados para cálculos
//     void calcularInteraccionesGravitacionales();
//     void actualizarPosicionesCuerpos();
//     void guardarEstadoActual();

//     // Métodos utilitarios
//     QString formatearEstadoCuerpo(const CuerpoEstelar* cuerpo) const;
//     QStringList parsearLineaCSV(const QString& linea) const;
// };
// #endif // SIMULADORGRAVITACIONAL_H


#ifndef SIMULADORGRAVITACIONAL_H
#define SIMULADORGRAVITACIONAL_H
#include <QObject>
#include <QTimer>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QPointF>
#include "cuerpoestelar.h"

class SimuladorGravitacional : public QObject
{
    Q_OBJECT
public:
    explicit SimuladorGravitacional(QObject *parent = nullptr);
    ~SimuladorGravitacional();

    // Gestión de cuerpos estelares
    void agregarCuerpo(CuerpoEstelar* cuerpo);
    void eliminarTodosCuerpos();
    const QList<CuerpoEstelar*>& getCuerpos() const { return m_cuerpos; }
    int getNumCuerpos() const { return m_cuerpos.size(); }

    // Control de la simulación
    void iniciarSimulacion();
    void pausarSimulacion();
    void reiniciarSimulacion();
    bool estaSimulando() const { return m_simulando; }

    // NUEVA FUNCIONALIDAD: Resetear a posición original
    void resetearPosicionesOriginales();

    // Configuración de parámetros
    void setDeltaTiempo(double dt) { m_deltaT = dt; }
    void setIntervaloActualizacion(int ms) { m_timer->setInterval(ms); }
    double getDeltaTiempo() const { return m_deltaT; }

    // MEJORA: Control de trayectorias y colisiones
    void setMostrarTrayectorias(bool mostrar);
    void setDeteccionColisiones(bool activa) { m_deteccionColisionesActiva = activa; }
    bool hayColisionesActivas() const { return m_hayColisiones; }

    // Archivo CSV/TXT - Entrada y salida
    bool cargarDesdeCSV(const QString& rutaArchivo);
    bool cargarDesdeTXT(const QString& rutaArchivo);
    bool cargarArchivoGenerico(const QString& rutaArchivo); // NUEVA: Autodetecta formato
    bool guardarTrayectoriasCSV(const QString& rutaArchivo) const;
    bool guardarEstadoActualCSV(const QString& rutaArchivo) const;

    // NUEVA FUNCIONALIDAD: Verificación con archivo de referencia
    double verificarConArchivo(const QString& rutaArchivo) const;
    QList<QList<QPointF>> cargarTrayectoriasReferencia(const QString& rutaArchivo) const;

    // Estadísticas y información
    int getIteracion() const { return m_iteracion; }
    double getTiempoSimulacion() const { return m_iteracion * m_deltaT; }

    // Configuración de sistemas predefinidos
    void configurarSistema1();
    void configurarSistema2();

signals:
    void simulacionIniciada();
    void simulacionPausada();
    void simulacionReiniciada();
    void estadoActualizado();
    void errorSimulacion(const QString& mensaje);
    void colisionDetectada(const QString& cuerpo1, const QString& cuerpo2); // NUEVA SEÑAL

public slots:
    void actualizarSimulacion();

private:
    QList<CuerpoEstelar*> m_cuerpos;
    QTimer* m_timer;
    bool m_simulando;
    double m_deltaT;              // Paso de tiempo (Δt = 1 según especificaciones)
    int m_iteracion;

    // NUEVOS ATRIBUTOS: Control de colisiones
    bool m_deteccionColisionesActiva;
    bool m_hayColisiones;
    QList<QPair<QString, QString>> m_colisionesActuales;

    // Historial para exportación
    QList<QList<QPointF>> m_historiaTrayectorias;

    // Métodos privados para cálculos
    void calcularInteraccionesGravitacionales();
    void actualizarPosicionesCuerpos();
    void guardarEstadoActual();

    // NUEVOS MÉTODOS: Detección de colisiones
    void detectarColisiones();
    void procesarColision(CuerpoEstelar* cuerpo1, CuerpoEstelar* cuerpo2);

    // Métodos utilitarios
    QString formatearEstadoCuerpo(const CuerpoEstelar* cuerpo) const;
    QStringList parsearLineaCSV(const QString& linea) const;
    QStringList parsearLineaTXT(const QString& linea) const; // NUEVO: Para archivos TXT
    QString detectarFormatoArchivo(const QString& rutaArchivo) const; // NUEVO: Autodetección
};

#endif // SIMULADORGRAVITACIONAL_H

