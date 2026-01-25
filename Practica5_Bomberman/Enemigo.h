#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"
#include <QTimer>

class Enemigo : public Entidad {
    Q_OBJECT
public:
    explicit Enemigo(QGraphicsItem *parent = nullptr);
    ~Enemigo();

    void iniciarMovimiento();
    void detenerMovimiento();
    void establecerVelocidad(int v);
    int obtenerVelocidad() const;

    void activarAnimacionMuerte();
    bool estaMuriendo() const { return muriendo; }

private slots:
    void actualizarMovimiento();
    void actualizarAnimacion();

private:
    void cambiarDireccion();
    QPointF obtenerDireccionAleatoria();
    void cargarSprites();

    QTimer *temporizadorMovimiento;
    QTimer *temporizadorAnimacion;
    QPointF direccion;

    int velocidad;
    bool muriendo;

    int contadorMovimiento;
    int intervaloCambioDireccion;
};

#endif // ENEMIGO_H
