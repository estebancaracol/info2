// #include "cuerpoestelar.h"
// #include <QStyleOptionGraphicsItem>
// #include <QWidget>
// CuerpoEstelar::CuerpoEstelar(const QString& nombre, double x, double y, double masa,
//                              double radio, double vx, double vy)
//     : m_nombre(nombre), m_x(x), m_y(y), m_masa(masa), m_radio(radio),
//     m_vx(vx), m_vy(vy), m_ax(0.0), m_ay(0.0), m_color(Qt::blue)
// {
//     // Configurar posición inicial en la escena
//     setPos(m_x, m_y);

//     // Agregar posición inicial a la trayectoria
//     m_trayectoria.append(QPointF(m_x, m_y));
// }
// QRectF CuerpoEstelar::boundingRect() const
// {
//     // Rectángulo que contiene el cuerpo (con margen para la trayectoria)
//     double margen = m_radio * 2;
//     return QRectF(-margen, -margen, margen * 2, margen * 2);
// }
// void CuerpoEstelar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     Q_UNUSED(option)
//     Q_UNUSED(widget)

//     painter->setRenderHint(QPainter::Antialiasing);

//     // Dibujar trayectoria si hay más de un punto
//     if (m_trayectoria.size() > 1) {
//         QPen penTrayectoria(m_color.lighter(150));
//         penTrayectoria.setWidth(1);
//         penTrayectoria.setStyle(Qt::DashLine);
//         painter->setPen(penTrayectoria);

//         for (int i = 1; i < m_trayectoria.size(); ++i) {
//             QPointF p1 = m_trayectoria[i-1];
//             QPointF p2 = m_trayectoria[i];

//             // Convertir coordenadas globales a locales
//             p1 -= QPointF(m_x, m_y);
//             p2 -= QPointF(m_x, m_y);

//             painter->drawLine(p1, p2);
//         }
//     }

//     // Dibujar el cuerpo estelar
//     painter->setBrush(QBrush(m_color));
//     painter->setPen(QPen(m_color.darker(120), 2));
//     painter->drawEllipse(-m_radio, -m_radio, m_radio * 2, m_radio * 2);

//     // Dibujar centro del cuerpo
//     painter->setBrush(QBrush(m_color.lighter(180)));
//     painter->setPen(QPen(Qt::white, 1));
//     double centroRadio = m_radio * 0.3;
//     painter->drawEllipse(-centroRadio, -centroRadio, centroRadio * 2, centroRadio * 2);

//     // Dibujar nombre del cuerpo
//     painter->setPen(QPen(Qt::white));
//     painter->setFont(QFont("Arial", 8, QFont::Bold));
//     QRectF rectTexto(-m_radio * 2, m_radio + 5, m_radio * 4, 15);
//     painter->drawText(rectTexto, Qt::AlignCenter, m_nombre);
// }
// void CuerpoEstelar::actualizarPosicion(double dt)
// {
//     // Implementar ecuaciones de movimiento según las especificaciones
//     // x = x₀ + vₓt + aₓt²/2
//     // y = y₀ + vᵧt + aᵧt²/2
//     // vₓ = vₓ₀ + aₓt
//     // vᵧ = vᵧ₀ + aᵧt

//     // Actualizar posición
//     m_x = m_x + m_vx * dt + 0.5 * m_ax * dt * dt;
//     m_y = m_y + m_vy * dt + 0.5 * m_ay * dt * dt;

//     // Actualizar velocidad
//     m_vx = m_vx + m_ax * dt;
//     m_vy = m_vy + m_ay * dt;

//     // Actualizar posición en la escena gráfica
//     setPos(m_x, m_y);

//     // Agregar nueva posición a la trayectoria
//     m_trayectoria.append(QPointF(m_x, m_y));

//     // Limitar el tamaño de la trayectoria para evitar uso excesivo de memoria
//     if (m_trayectoria.size() > MAX_TRAYECTORIA) {
//         m_trayectoria.removeFirst();
//     }
// }
// void CuerpoEstelar::calcularFuerzaGravitacional(const CuerpoEstelar* otro, double& fx, double& fy) const
// {
//     if (otro == this) {
//         fx = fy = 0.0;
//         return;
//     }

//     // Calcular diferencias de posición
//     double dx = otro->m_x - m_x;
//     double dy = otro->m_y - m_y;

//     // Calcular distancia
//     double r = std::sqrt(dx * dx + dy * dy);

//     // Evitar división por cero (colisiones)
//     if (r < (m_radio + otro->m_radio)) {
//         r = m_radio + otro->m_radio;
//     }

//     // Calcular magnitud de la fuerza gravitacional
//     // F = G * m₁ * m₂ / r²
//     double fuerzaMagnitud = G * m_masa * otro->m_masa / (r * r);

//     // Calcular componentes de la fuerza (normalizar vector de dirección)
//     fx = fuerzaMagnitud * (dx / r);
//     fy = fuerzaMagnitud * (dy / r);
// }
// void CuerpoEstelar::aplicarAceleracion(double ax, double ay)
// {
//     // Sumar aceleración (para múltiples fuerzas)
//     m_ax += ax;
//     m_ay += ay;
// }
// void CuerpoEstelar::reiniciarAceleracion()
// {
//     m_ax = 0.0;
//     m_ay = 0.0;
// }
// void CuerpoEstelar::setPosicion(double x, double y)
// {
//     m_x = x;
//     m_y = y;
//     setPos(m_x, m_y);

//     // Limpiar trayectoria y agregar nueva posición inicial
//     m_trayectoria.clear();
//     m_trayectoria.append(QPointF(m_x, m_y));
// }
// void CuerpoEstelar::setVelocidad(double vx, double vy)
// {
//     m_vx = vx;
//     m_vy = vy;
// }


#include "cuerpoestelar.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>

CuerpoEstelar::CuerpoEstelar(const QString& nombre, double x, double y, double masa,
                             double radio, double vx, double vy)
    : m_nombre(nombre), m_x(x), m_y(y), m_masa(masa), m_radio(radio),
    m_vx(vx), m_vy(vy), m_ax(0.0), m_ay(0.0), m_color(Qt::blue),
    m_enColision(false), m_mostrarTrayectoria(true)
{
    // Configurar posición inicial en la escena
    setPos(m_x, m_y);

    // MEJORA: Guardar posición original automáticamente
    guardarPosicionOriginal();

    // Agregar posición inicial a la trayectoria
    m_trayectoria.append(QPointF(m_x, m_y));
}

QRectF CuerpoEstelar::boundingRect() const
{
    // MEJORA: Rectángulo que contiene el cuerpo y su trayectoria con margen dinámico
    double margen = std::max(m_radio * 3, 50.0); // Margen mínimo de 50 píxeles
    return QRectF(-margen, -margen, margen * 2, margen * 2);
}

void CuerpoEstelar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing);

    // MEJORA: Dibujar trayectoria completa solo si está habilitada
    if (m_mostrarTrayectoria && m_trayectoria.size() > 1) {
        QPen penTrayectoria(m_color.lighter(150));
        penTrayectoria.setWidth(2);
        penTrayectoria.setStyle(Qt::SolidLine);
        painter->setPen(penTrayectoria);

        // CORRECCIÓN: Dibujar trayectoria relativa a la posición actual del objeto
        for (int i = 1; i < m_trayectoria.size(); ++i) {
            QPointF p1 = m_trayectoria[i-1] - QPointF(m_x, m_y);
            QPointF p2 = m_trayectoria[i] - QPointF(m_x, m_y);
            painter->drawLine(p1, p2);
        }

        // MEJORA: Dibujar puntos en la trayectoria para mejor visualización
        painter->setBrush(QBrush(m_color.lighter(180)));
        for (int i = 0; i < m_trayectoria.size(); i += 10) { // Cada 10 puntos
            QPointF punto = m_trayectoria[i] - QPointF(m_x, m_y);
            painter->drawEllipse(punto, 1, 1);
        }
    }

    // MEJORA: Color especial si está en colisión
    QColor colorCuerpo = m_enColision ? QColor(255, 0, 0) : m_color;

    // Dibujar el cuerpo estelar
    painter->setBrush(QBrush(colorCuerpo));
    painter->setPen(QPen(colorCuerpo.darker(120), 3));
    painter->drawEllipse(-m_radio, -m_radio, m_radio * 2, m_radio * 2);

    // MEJORA: Efecto de colisión con anillo pulsante
    if (m_enColision) {
        QPen penColision(QColor(255, 255, 0), 3, Qt::DashLine);
        painter->setPen(penColision);
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(-m_radio * 1.5, -m_radio * 1.5, m_radio * 3, m_radio * 3);
    }

    // Dibujar centro del cuerpo
    painter->setBrush(QBrush(colorCuerpo.lighter(180)));
    painter->setPen(QPen(Qt::white, 1));
    double centroRadio = m_radio * 0.3;
    painter->drawEllipse(-centroRadio, -centroRadio, centroRadio * 2, centroRadio * 2);

    // Dibujar nombre del cuerpo
    painter->setPen(QPen(Qt::white));
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    QRectF rectTexto(-m_radio * 2, m_radio + 5, m_radio * 4, 15);
    painter->drawText(rectTexto, Qt::AlignCenter, m_nombre);

    // MEJORA: Mostrar información adicional si hay colisión
    if (m_enColision) {
        painter->setPen(QPen(Qt::yellow));
        painter->setFont(QFont("Arial", 6, QFont::Bold));
        QRectF rectColision(-m_radio * 2, m_radio + 20, m_radio * 4, 10);
        painter->drawText(rectColision, Qt::AlignCenter, "¡COLISIÓN!");
    }
}

void CuerpoEstelar::actualizarPosicion(double dt)
{
    // Implementar ecuaciones de movimiento según las especificaciones
    // x = x₀ + vₓt + aₓt²/2
    // y = y₀ + vᵧt + aᵧt²/2
    // vₓ = vₓ₀ + aₓt
    // vᵧ = vᵧ₀ + aᵧt

    // Actualizar posición
    m_x = m_x + m_vx * dt + 0.5 * m_ax * dt * dt;
    m_y = m_y + m_vy * dt + 0.5 * m_ay * dt * dt;

    // Actualizar velocidad
    m_vx = m_vx + m_ax * dt;
    m_vy = m_vy + m_ay * dt;

    // Actualizar posición en la escena gráfica
    setPos(m_x, m_y);

    // MEJORA: Solo agregar a trayectoria si está habilitada
    if (m_mostrarTrayectoria) {
        // Agregar nueva posición a la trayectoria
        m_trayectoria.append(QPointF(m_x, m_y));

        // Limitar el tamaño de la trayectoria para evitar uso excesivo de memoria
        if (m_trayectoria.size() > MAX_TRAYECTORIA) {
            m_trayectoria.removeFirst();
        }
    }
}

void CuerpoEstelar::calcularFuerzaGravitacional(const CuerpoEstelar* otro, double& fx, double& fy) const
{
    if (otro == this) {
        fx = fy = 0.0;
        return;
    }

    // Calcular diferencias de posición
    double dx = otro->m_x - m_x;
    double dy = otro->m_y - m_y;

    // Calcular distancia
    double r = std::sqrt(dx * dx + dy * dy);

    // MEJORA: Verificar colisión y evitar división por cero
    if (r < (m_radio + otro->m_radio)) {
        r = m_radio + otro->m_radio;
        // Nota: La detección de colisión se maneja en el simulador
    }

    // Calcular magnitud de la fuerza gravitacional
    // F = G * m₁ * m₂ / r²
    double fuerzaMagnitud = G * m_masa * otro->m_masa / (r * r);

    // Calcular componentes de la fuerza (normalizar vector de dirección)
    fx = fuerzaMagnitud * (dx / r);
    fy = fuerzaMagnitud * (dy / r);
}

void CuerpoEstelar::aplicarAceleracion(double ax, double ay)
{
    // Sumar aceleración (para múltiples fuerzas)
    m_ax += ax;
    m_ay += ay;
}

void CuerpoEstelar::reiniciarAceleracion()
{
    m_ax = 0.0;
    m_ay = 0.0;
}

// NUEVAS FUNCIONES IMPLEMENTADAS:

void CuerpoEstelar::guardarPosicionOriginal()
{
    m_x_original = m_x;
    m_y_original = m_y;
    m_vx_original = m_vx;
    m_vy_original = m_vy;
}

void CuerpoEstelar::restaurarPosicionOriginal()
{
    m_x = m_x_original;
    m_y = m_y_original;
    m_vx = m_vx_original;
    m_vy = m_vy_original;
    m_ax = 0.0;
    m_ay = 0.0;
    m_enColision = false;

    // Actualizar posición gráfica
    setPos(m_x, m_y);

    // Reiniciar trayectoria
    limpiarTrayectoria();
}

void CuerpoEstelar::limpiarTrayectoria()
{
    m_trayectoria.clear();
    m_trayectoria.append(QPointF(m_x, m_y));
}

bool CuerpoEstelar::hayColision(const CuerpoEstelar* otro) const
{
    if (otro == this) return false;

    double dx = otro->m_x - m_x;
    double dy = otro->m_y - m_y;
    double distancia = std::sqrt(dx * dx + dy * dy);

    return distancia < (m_radio + otro->m_radio);
}

void CuerpoEstelar::setPosicion(double x, double y)
{
    m_x = x;
    m_y = y;
    setPos(m_x, m_y);

    // MEJORA: Limpiar trayectoria solo si se cambia posición manualmente
    limpiarTrayectoria();
}

void CuerpoEstelar::setVelocidad(double vx, double vy)
{
    m_vx = vx;
    m_vy = vy;
}
