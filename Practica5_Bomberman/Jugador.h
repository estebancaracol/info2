#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include "Bomba.h"
#include <QTimer>
#include <QKeyEvent>
#include <QSet>

class Jugador : public Entidad {
    Q_OBJECT
public:
    explicit Jugador(QGraphicsItem *parent = nullptr);
    ~Jugador();

    void manejarInput();
    void colocarBomba();
    void activarAnimacionMuerte();

    bool estaMuriendo() const { return muriendo; }
    bool estaInmune() const { return inmune; }
    void activarInmunidad(int duracionMs = 2000);

    // Gestión de teclas presionadas
    void agregarTeclaPresionada(int tecla);
    void quitarTeclaPresionada(int tecla);
    void iniciarAnimacionMuerte(const QStringList& sprites);

    void setPosicionInicial(const QPointF& pos);

signals:
    void enemigoDestruido();
    void ladrilloDestruido();
    void jugadorMurio();
    void bombaColocada();

public slots:
    void alBombaExplotada(Bomba* bomba);
    void alEnemigoDestruido();
    void alLadrilloDestruido();
    void actualizarMovimiento();
    void finalizarInmunidad();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    void cargarSprites();
    void moverEnDireccion(int tecla);
    void actualizarSpriteDireccion(int tecla);
    void resetearASpritePorDefecto();
    void verificarColisionEnemigos();

    // Sprites direccionales
    QVector<QPixmap> spritesDerecha, spritesIzquierda, spritesArriba, spritesAbajo;
    int indiceDerecha = 0, indiceIzquierda = 0, indiceArriba = 0, indiceAbajo = 0;
    int direccionActual = 0; // 0=ninguna, 1=arriba, 2=abajo, 3=izquierda, 4=derecha

    QPixmap spriteDefecto;
    QPointF posicionInicial;
    QTimer* temporizadorMovimiento;
    QTimer* temporizadorAnimacion;
    QTimer* temporizadorInmunidad;

    // Control de teclas
    QSet<int> teclasPresionadas;

    QList<Bomba*> bombasActivas;
    int maximoBombas;
    int rangoExplosion;

    int velocidad;
    bool muriendo;
    bool inmune;
    bool visible;
};

#endif // JUGADOR_H
