// #ifndef CUERPOESTELAR_H
// #define CUERPOESTELAR_H
// #include <QGraphicsItem>
// #include <QPainter>
// #include <QColor>
// #include <QString>
// #include <cmath>
// class CuerpoEstelar : public QGraphicsItem
// {
// public:
//     // Constructor
//     CuerpoEstelar(const QString& nombre, double x, double y, double masa,
//                   double radio, double vx = 0.0, double vy = 0.0);

//     // Destructor
//     ~CuerpoEstelar() = default;
//     // Métodos requeridos por QGraphicsItem
//     QRectF boundingRect() const override;
//     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//     // Métodos para la simulación física
//     void actualizarPosicion(double dt);
//     void calcularFuerzaGravitacional(const CuerpoEstelar* otro, double& fx, double& fy) const;
//     void aplicarAceleracion(double ax, double ay);
//     void reiniciarAceleracion();

//     // Getters
//     QString getNombre() const { return m_nombre; }
//     double getMasa() const { return m_masa; }
//     double getRadio() const { return m_radio; }
//     double getPosX() const { return m_x; }
//     double getPosY() const { return m_y; }
//     double getVelX() const { return m_vx; }
//     double getVelY() const { return m_vy; }
//     double getAcelX() const { return m_ax; }
//     double getAcelY() const { return m_ay; }

//     // Setters
//     void setPosicion(double x, double y);
//     void setVelocidad(double vx, double vy);
//     void setColor(const QColor& color) { m_color = color; }

//     // Constante gravitacional (simplificada según las especificaciones)
//     static constexpr double G = 1.0;
// private:
//     QString m_nombre;
//     double m_x, m_y;           // Posición actual
//     double m_vx, m_vy;         // Velocidad actual
//     double m_ax, m_ay;         // Aceleración actual
//     double m_masa;             // Masa del cuerpo
//     double m_radio;            // Radio para visualización
//     QColor m_color;            // Color para renderizado

//     // Historial de posiciones para trayectoria
//     QList<QPointF> m_trayectoria;
//     static const int MAX_TRAYECTORIA = 1000;
// };
// #endif // CUERPOESTELAR_H


#ifndef CUERPOESTELAR_H
#define CUERPOESTELAR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QString>
#include <cmath>

class CuerpoEstelar : public QGraphicsItem
{
public:
    // Constructor
    CuerpoEstelar(const QString& nombre, double x, double y, double masa,
                  double radio, double vx = 0.0, double vy = 0.0);

    // Destructor
    ~CuerpoEstelar() = default;

    // Métodos requeridos por QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Métodos para la simulación física
    void actualizarPosicion(double dt);
    void calcularFuerzaGravitacional(const CuerpoEstelar* otro, double& fx, double& fy) const;
    void aplicarAceleracion(double ax, double ay);
    void reiniciarAceleracion();

    // NUEVAS FUNCIONALIDADES: Gestión de posición original
    void guardarPosicionOriginal();
    void restaurarPosicionOriginal();
    void limpiarTrayectoria();

    // NUEVAS FUNCIONALIDADES: Detección de colisiones
    bool hayColision(const CuerpoEstelar* otro) const;
    void marcarColision(bool activo) { m_enColision = activo; }
    bool estaEnColision() const { return m_enColision; }

    // Getters
    QString getNombre() const { return m_nombre; }
    double getMasa() const { return m_masa; }
    double getRadio() const { return m_radio; }
    double getPosX() const { return m_x; }
    double getPosY() const { return m_y; }
    double getVelX() const { return m_vx; }
    double getVelY() const { return m_vy; }
    double getAcelX() const { return m_ax; }
    double getAcelY() const { return m_ay; }

    // NUEVOS GETTERS: Posición original
    double getPosXOriginal() const { return m_x_original; }
    double getPosYOriginal() const { return m_y_original; }
    double getVelXOriginal() const { return m_vx_original; }
    double getVelYOriginal() const { return m_vy_original; }

    // Setters
    void setPosicion(double x, double y);
    void setVelocidad(double vx, double vy);
    //void setColor(const QColor& color) { m_color = color; }
    void setColor(const QColor& color) {
        m_color = color;
        m_colorPersonalizado = true;
    }
    void setMostrarTrayectoria(bool mostrar) { m_mostrarTrayectoria = mostrar; }

    // Constante gravitacional (simplificada según las especificaciones)
    static constexpr double G = 1.0;

    bool tieneColorPersonalizado() const { return m_colorPersonalizado; }

private:
    QString m_nombre;
    double m_x, m_y;           // Posición actual
    double m_vx, m_vy;         // Velocidad actual
    double m_ax, m_ay;         // Aceleración actual
    double m_masa;             // Masa del cuerpo
    double m_radio;            // Radio para visualización
    QColor m_color;            // Color para renderizado

    // NUEVOS ATRIBUTOS: Posición original para reset
    double m_x_original, m_y_original;     // Posición inicial
    double m_vx_original, m_vy_original;   // Velocidad inicial

    // NUEVO ATRIBUTO: Control de colisiones
    bool m_enColision;

    // NUEVO ATRIBUTO: Control de visualización de trayectoria
    bool m_mostrarTrayectoria;

    // Historial de posiciones para trayectoria
    QList<QPointF> m_trayectoria;
    static const int MAX_TRAYECTORIA = 1000;

    bool m_colorPersonalizado = false;
};

#endif // CUERPOESTELAR_H
