QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QT += multimedia

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Block.cpp \
    Bomba.cpp \
    Enemigo.cpp \
    Entidad.cpp \
    Escena.cpp \
    Game.cpp \
    Jugador.cpp \
    Ladrillo.cpp \
    PanelInfo.cpp \
    Pared.cpp \
    SistemaRecords.cpp \
    VentanaJuego.cpp \
    VentanaPersonalizada.cpp \
    VentanaRecords.cpp \
    main.cpp

HEADERS += \
    Block.h \
    Bomba.h \
    Enemigo.h \
    Entidad.h \
    Escena.h \
    Game.h \
    Jugador.h \
    Ladrillo.h \
    PanelInfo.h \
    Pared.h \
    SistemaRecords.h \
    VentanaJuego.h \
    VentanaPersonalizada.h \
    VentanaRecords.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
