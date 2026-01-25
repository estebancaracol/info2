#include "simuladorgravitacional.h"
#include <QStringList>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <cmath>
#include <QRegularExpression>

SimuladorGravitacional::SimuladorGravitacional(QObject *parent)
    : QObject(parent), m_simulando(false), m_deltaT(1.0), m_iteracion(0),
    m_deteccionColisionesActiva(true), m_hayColisiones(false)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(50); // 20 FPS por defecto
    connect(m_timer, &QTimer::timeout, this, &SimuladorGravitacional::actualizarSimulacion);
}

SimuladorGravitacional::~SimuladorGravitacional()
{
    eliminarTodosCuerpos();
}

void SimuladorGravitacional::agregarCuerpo(CuerpoEstelar* cuerpo)
{
    if (cuerpo) {
        m_cuerpos.append(cuerpo);
        emit estadoActualizado();
    }
}

void SimuladorGravitacional::eliminarTodosCuerpos()
{
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        delete cuerpo;
    }
    m_cuerpos.clear();
    m_historiaTrayectorias.clear();
    m_colisionesActuales.clear();
    m_hayColisiones = false;
    emit estadoActualizado();
}

void SimuladorGravitacional::iniciarSimulacion()
{
    if (!m_simulando && !m_cuerpos.isEmpty()) {
        m_simulando = true;
        m_timer->start();
        emit simulacionIniciada();
        qDebug() << "Simulación iniciada con" << m_cuerpos.size() << "cuerpos";
    }
}

void SimuladorGravitacional::pausarSimulacion()
{
    if (m_simulando) {
        m_simulando = false;
        m_timer->stop();
        emit simulacionPausada();
        qDebug() << "Simulación pausada en iteración" << m_iteracion;
    }
}

void SimuladorGravitacional::reiniciarSimulacion()
{
    pausarSimulacion();
    m_iteracion = 0;
    m_historiaTrayectorias.clear();
    m_colisionesActuales.clear();
    m_hayColisiones = false;
    // Reiniciar aceleraciones de todos los cuerpos
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->reiniciarAceleracion();
        cuerpo->marcarColision(false);
    }
    emit simulacionReiniciada();
    qDebug() << "Simulación reiniciada";
}

void SimuladorGravitacional::resetearPosicionesOriginales()
{
    pausarSimulacion();
    m_iteracion = 0;
    m_historiaTrayectorias.clear();
    m_colisionesActuales.clear();
    m_hayColisiones = false;
    // Restaurar todos los cuerpos a su posición original
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->restaurarPosicionOriginal();
    }
    emit simulacionReiniciada();
    qDebug() << "Posiciones originales restauradas";
}

void SimuladorGravitacional::setMostrarTrayectorias(bool mostrar)
{
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->setMostrarTrayectoria(mostrar);
    }
}

void SimuladorGravitacional::actualizarSimulacion()
{
    if (!m_simulando) return;
    try {
        // Calcular todas las interacciones gravitacionales
        calcularInteraccionesGravitacionales();
        // Detectar colisiones si está habilitado
        if (m_deteccionColisionesActiva) {
            detectarColisiones();
        }
        // Actualizar posiciones de todos los cuerpos
        actualizarPosicionesCuerpos();
        // Guardar estado actual para historial (solo para verificación)
        guardarEstadoActual();
        // Incrementar contador de iteraciones
        m_iteracion++;
        // Emitir señal de actualización
        emit estadoActualizado();
    } catch (const std::exception& e) {
        emit errorSimulacion(QString("Error en simulación: %1").arg(e.what()));
        pausarSimulacion();
    }
}

void SimuladorGravitacional::calcularInteraccionesGravitacionales()
{
    // Reiniciar aceleraciones de todos los cuerpos
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->reiniciarAceleracion();
    }
    // Calcular interacciones entre todos los pares de cuerpos
    for (int i = 0; i < m_cuerpos.size(); ++i) {
        for (int j = i + 1; j < m_cuerpos.size(); ++j) {
            CuerpoEstelar* cuerpo1 = m_cuerpos[i];
            CuerpoEstelar* cuerpo2 = m_cuerpos[j];
            // Calcular fuerza gravitacional entre cuerpo1 y cuerpo2
            double fx, fy;
            cuerpo1->calcularFuerzaGravitacional(cuerpo2, fx, fy);
            // Aplicar fuerza a cuerpo1 (F = ma, entonces a = F/m)
            double a1x = fx / cuerpo1->getMasa();
            double a1y = fy / cuerpo1->getMasa();
            cuerpo1->aplicarAceleracion(a1x, a1y);
            // Aplicar fuerza opuesta a cuerpo2 (tercera ley de Newton)
            double a2x = -fx / cuerpo2->getMasa();
            double a2y = -fy / cuerpo2->getMasa();
            cuerpo2->aplicarAceleracion(a2x, a2y);
        }
    }
}

void SimuladorGravitacional::detectarColisiones()
{
    // Limpiar estado anterior
    m_colisionesActuales.clear();
    m_hayColisiones = false;

    // Desmarcar colisiones previas
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->marcarColision(false);
    }
    // Detectar colisiones entre todos los pares
    for (int i = 0; i < m_cuerpos.size(); ++i) {
        for (int j = i + 1; j < m_cuerpos.size(); ++j) {
            CuerpoEstelar* cuerpo1 = m_cuerpos[i];
            CuerpoEstelar* cuerpo2 = m_cuerpos[j];
            if (cuerpo1->hayColision(cuerpo2)) {
                // Marcar ambos cuerpos en colisión
                cuerpo1->marcarColision(true);
                cuerpo2->marcarColision(true);

                // Registrar la colisión
                m_colisionesActuales.append(qMakePair(cuerpo1->getNombre(), cuerpo2->getNombre()));
                m_hayColisiones = true;

                // Emitir señal de colisión
                emit colisionDetectada(cuerpo1->getNombre(), cuerpo2->getNombre());

                // Procesar efectos de la colisión
                procesarColision(cuerpo1, cuerpo2);
            }
        }
    }
}

void SimuladorGravitacional::procesarColision(CuerpoEstelar* cuerpo1, CuerpoEstelar* cuerpo2)
{
    // Implementación básica: reducir velocidades para simular pérdida de energía
    double factor = 0.8; // Factor de reducción de velocidad

    cuerpo1->setVelocidad(cuerpo1->getVelX() * factor, cuerpo1->getVelY() * factor);
    cuerpo2->setVelocidad(cuerpo2->getVelX() * factor, cuerpo2->getVelY() * factor);
}

void SimuladorGravitacional::actualizarPosicionesCuerpos()
{
    for (CuerpoEstelar* cuerpo : m_cuerpos) {
        cuerpo->actualizarPosicion(m_deltaT);
    }
}

void SimuladorGravitacional::guardarEstadoActual()
{
    QList<QPointF> estadoActual;
    for (const CuerpoEstelar* cuerpo : m_cuerpos) {
        estadoActual.append(QPointF(cuerpo->getPosX(), cuerpo->getPosY()));
    }
    m_historiaTrayectorias.append(estadoActual);
}

bool SimuladorGravitacional::cargarArchivoGenerico(const QString& rutaArchivo)
{
    QString formato = detectarFormatoArchivo(rutaArchivo);

    if (formato == "CSV") {
        return cargarDesdeCSV(rutaArchivo);
    } else if (formato == "TXT") {
        return cargarDesdeTXT(rutaArchivo);
    } else {
        emit errorSimulacion("Formato de archivo no soportado: " + rutaArchivo);
        return false;
    }
}

QString SimuladorGravitacional::detectarFormatoArchivo(const QString& rutaArchivo) const
{
    QFileInfo info(rutaArchivo);
    QString extension = info.suffix().toUpper();

    if (extension == "CSV") {
        return "CSV";
    } else if (extension == "TXT") {
        return "TXT";
    }

    // Si no hay extensión clara, examinar contenido
    QFile archivo(rutaArchivo);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&archivo);
        QString primeraLinea = stream.readLine();

        if (primeraLinea.contains(",")) {
            return "CSV";
        } else if (primeraLinea.contains("\t") || primeraLinea.contains(" ")) {
            return "TXT";
        }
    }

    return "DESCONOCIDO";
}

bool SimuladorGravitacional::cargarDesdeTXT(const QString& rutaArchivo)
{
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorSimulacion(QString("No se pudo abrir el archivo: %1").arg(rutaArchivo));
        return false;
    }
    eliminarTodosCuerpos();
    QTextStream stream(&archivo);
    bool primeraLinea = true;
    int lineaNumero = 0;
    while (!stream.atEnd()) {
        QString linea = stream.readLine().trimmed();
        lineaNumero++;
        // Saltar líneas vacías
        if (linea.isEmpty()) continue;
        QStringList campos = parsearLineaTXT(linea);
        // Formato esperado para TXT: nombre x y masa radio vx vy
        if (campos.size() < 7) {
            continue;
        }
        try {
            QString nombre = campos[0];
            double x = campos[1].toDouble();
            double y = campos[2].toDouble();
            double masa = campos[3].toDouble();
            double radio = campos[4].toDouble();
            double vx = campos[5].toDouble();
            double vy = campos[6].toDouble();
            // Validar datos
            if (masa <= 0 || radio <= 0) {
                emit errorSimulacion(QString("Línea %1: masa y radio deben ser positivos").arg(lineaNumero));
                continue;
            }
            CuerpoEstelar* nuevoCuerpo = new CuerpoEstelar(nombre, x, y, masa, radio, vx, vy);
            agregarCuerpo(nuevoCuerpo);
        } catch (const std::exception& e) {
            emit errorSimulacion(QString("Línea %1: error al convertir datos - %2").arg(lineaNumero).arg(e.what()));
            continue;
        }
    }
    archivo.close();
    if (m_cuerpos.isEmpty()) {
        emit errorSimulacion("No se cargaron cuerpos válidos del archivo TXT");
        return false;
    }
    qDebug() << "Cargados" << m_cuerpos.size() << "cuerpos desde TXT:" << rutaArchivo;
    return true;
}

QStringList SimuladorGravitacional::parsearLineaTXT(const QString& linea) const
{
    // Para archivos TXT, separar por tabulaciones o espacios múltiples
    QStringList campos = linea.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);;
    return campos;
}

double SimuladorGravitacional::verificarConArchivo(const QString& rutaArchivo) const
{
    QList<QList<QPointF>> trayectoriasReferencia = cargarTrayectoriasReferencia(rutaArchivo);

    if (trayectoriasReferencia.isEmpty() || m_historiaTrayectorias.isEmpty()) {
        return 0.0; // No se puede verificar
    }

    int puntosVerificados = 0;
    int puntosCorrectos = 0;
    double tolerancia = 100.0; // Tolerancia en píxeles

    // Comparar trayectorias punto por punto
    int minIteraciones = std::min(trayectoriasReferencia.size(), m_historiaTrayectorias.size());
    int minCuerpos = std::min(
        trayectoriasReferencia.isEmpty() ? 0 : trayectoriasReferencia[0].size(),
        m_cuerpos.size()
        );

    for (int iter = 0; iter < minIteraciones; ++iter) {
        for (int cuerpo = 0; cuerpo < minCuerpos; ++cuerpo) {
            if (cuerpo < trayectoriasReferencia[iter].size() &&
                cuerpo < m_historiaTrayectorias[iter].size()) {

                QPointF puntoRef = trayectoriasReferencia[iter][cuerpo];
                QPointF puntoSim = m_historiaTrayectorias[iter][cuerpo];

                double distancia = std::sqrt(
                    std::pow(puntoRef.x() - puntoSim.x(), 2) +
                    std::pow(puntoRef.y() - puntoSim.y(), 2)
                    );

                puntosVerificados++;
                if (distancia <= tolerancia) {
                    puntosCorrectos++;
                }
            }
        }
    }

    if (puntosVerificados == 0) return 0.0;

    return (double)puntosCorrectos / puntosVerificados * 100.0;
}

QList<QList<QPointF>> SimuladorGravitacional::cargarTrayectoriasReferencia(const QString& rutaArchivo) const
{
    QList<QList<QPointF>> trayectorias;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return trayectorias;
    }

    QTextStream stream(&archivo);
    while (!stream.atEnd()) {
        QString linea = stream.readLine().trimmed();
        if (linea.isEmpty()) continue;

        QStringList campos = parsearLineaTXT(linea);
        QList<QPointF> puntos;

        // Asumiendo que el archivo contiene coordenadas x1,y1,x2,y2,x3,y3...
        for (int i = 0; i < campos.size() - 1; i += 2) {
            bool ok1, ok2;
            double x = campos[i].toDouble(&ok1);
            double y = campos[i + 1].toDouble(&ok2);

            if (ok1 && ok2) {
                puntos.append(QPointF(x, y));
            }
        }

        if (!puntos.isEmpty()) {
            trayectorias.append(puntos);
        }
    }

    archivo.close();
    return trayectorias;
}

bool SimuladorGravitacional::cargarDesdeCSV(const QString& rutaArchivo)
{
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorSimulacion(QString("No se pudo abrir el archivo: %1").arg(rutaArchivo));
        return false;
    }
    eliminarTodosCuerpos();
    QTextStream stream(&archivo);
    bool primeraLinea = true;
    int lineaNumero = 0;
    while (!stream.atEnd()) {
        QString linea = stream.readLine().trimmed();
        lineaNumero++;
        // Saltar líneas vacías
        if (linea.isEmpty()) continue;
        // Saltar encabezado (primera línea si contiene texto no numérico)
        if (primeraLinea && (linea.contains("nombre") || linea.contains("x") || linea.contains("y"))) {
            primeraLinea = false;
            continue;
        }
        primeraLinea = false;
        QStringList campos = parsearLineaCSV(linea);
        // Verificar que tenemos al menos 7 campos (nombre,x,y,masa,radio,vx,vy)
        if (campos.size() < 7) {
            emit errorSimulacion(QString("Línea %1: formato incorrecto, se esperan 7 campos").arg(lineaNumero));
            continue;
        }
        try {
            QString nombre = campos[0];
            double x = campos[1].toDouble();
            double y = campos[2].toDouble();
            double masa = campos[3].toDouble();
            double radio = campos[4].toDouble();
            double vx = campos[5].toDouble();
            double vy = campos[6].toDouble();
            // Validar datos
            if (masa <= 0 || radio <= 0) {
                emit errorSimulacion(QString("Línea %1: masa y radio deben ser positivos").arg(lineaNumero));
                continue;
            }
            CuerpoEstelar* nuevoCuerpo = new CuerpoEstelar(nombre, x, y, masa, radio, vx, vy);
            agregarCuerpo(nuevoCuerpo);
        } catch (const std::exception& e) {
            emit errorSimulacion(QString("Línea %1: error al convertir datos - %2").arg(lineaNumero).arg(e.what()));
            continue;
        }
    }
    archivo.close();
    if (m_cuerpos.isEmpty()) {
        emit errorSimulacion("No se cargaron cuerpos válidos del archivo");
        return false;
    }
    qDebug() << "Cargados" << m_cuerpos.size() << "cuerpos desde" << rutaArchivo;
    return true;
}

void SimuladorGravitacional::configurarSistema1()
{
    eliminarTodosCuerpos();
    // Sistema 1
    // Cuerpo 1: x=0, y=-7000, masa=70, radio=120, vx=2, vy=0
    CuerpoEstelar* cuerpo1 = new CuerpoEstelar("Cuerpo1", 0, -7000, 70, 120, 2, 0);
    cuerpo1->setColor(QColor(255, 100, 100)); // Rojo
    agregarCuerpo(cuerpo1);
    // Cuerpo 2: x=0, y=0, masa=70000, radio=300, vx=0, vy=0
    CuerpoEstelar* cuerpo2 = new CuerpoEstelar("Cuerpo2", 0, 0, 70000, 300, 0, 0);
    cuerpo2->setColor(QColor(255, 255, 100)); // Amarillo
    agregarCuerpo(cuerpo2);
    // Cuerpo 3: x=4000, y=5000, masa=25, radio=100, vx=-1.6, vy=1.2
    CuerpoEstelar* cuerpo3 = new CuerpoEstelar("Cuerpo3", 4000, 5000, 25, 100, -1.6, 1.2);
    cuerpo3->setColor(QColor(100, 100, 255)); // Azul
    agregarCuerpo(cuerpo3);
    resetearPosicionesOriginales();
    qDebug() << "Sistema 1 configurado";
}

void SimuladorGravitacional::configurarSistema2()
{
    eliminarTodosCuerpos();
    // Sistema 2
    // Cuerpo 1: x=0, y=0, masa=50000, radio=200, vx=0, vy=0
    CuerpoEstelar* cuerpo1 = new CuerpoEstelar("Central", 0, 0, 50000, 200, 0, 0);
    cuerpo1->setColor(QColor(255, 255, 100)); // Amarillo
    agregarCuerpo(cuerpo1);
    // Cuerpo 2: x=-5000, y=0, masa=70, radio=70, vx=0, vy=-2
    CuerpoEstelar* cuerpo2 = new CuerpoEstelar("Oeste", -5000, 0, 70, 70, 0, -2);
    cuerpo2->setColor(QColor(255, 100, 100)); // Rojo
    agregarCuerpo(cuerpo2);
    // Cuerpo 3: x=5000, y=0, masa=70, radio=70, vx=0, vy=2
    CuerpoEstelar* cuerpo3 = new CuerpoEstelar("Este", 5000, 0, 70, 70, 0, 2);
    cuerpo3->setColor(QColor(100, 255, 100)); // Verde
    agregarCuerpo(cuerpo3);
    // Cuerpo 4: x=0, y=-5000, masa=70, radio=70, vx=2, vy=0
    CuerpoEstelar* cuerpo4 = new CuerpoEstelar("Sur", 0, -5000, 70, 70, 2, 0);
    cuerpo4->setColor(QColor(100, 100, 255)); // Azul
    agregarCuerpo(cuerpo4);
    // Cuerpo 5: x=0, y=5000, masa=70, radio=70, vx=-2, vy=0
    CuerpoEstelar* cuerpo5 = new CuerpoEstelar("Norte", 0, 5000, 70, 70, -2, 0);
    cuerpo5->setColor(QColor(255, 100, 255)); // Magenta
    agregarCuerpo(cuerpo5);
    resetearPosicionesOriginales();
    qDebug() << "Sistema 2 configurado";
}

QStringList SimuladorGravitacional::parsearLineaCSV(const QString& linea) const
{
    QStringList campos;
    QString campoActual;
    bool dentroComillas = false;
    for (int i = 0; i < linea.length(); ++i) {
        QChar caracter = linea[i];
        if (caracter == '"') {
            dentroComillas = !dentroComillas;
        } else if (caracter == ',' && !dentroComillas) {
            campos.append(campoActual.trimmed());
            campoActual.clear();
        } else {
            campoActual.append(caracter);
        }
    }
    // Agregar último campo
    campos.append(campoActual.trimmed());
    return campos;
}
