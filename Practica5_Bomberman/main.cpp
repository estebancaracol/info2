#include <QApplication>
#include <QIcon>
#include <QDir>

#include "VentanaJuego.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Configurar información de la aplicación
    a.setApplicationName("Bomberman");

    // Configurar ícono de la aplicación si está disponible
    QIcon iconoAplicacion(":/images/bomberman.png");
    if (!iconoAplicacion.isNull()) {
        a.setWindowIcon(iconoAplicacion);
    }

    VentanaJuego ventana;
    ventana.show();

    return a.exec();
}
