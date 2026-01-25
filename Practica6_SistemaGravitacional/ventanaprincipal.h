// #ifndef VENTANAPRINCIPAL_H
// #define VENTANAPRINCIPAL_H
// #include <QMainWindow>
// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QGridLayout>
// #include <QPushButton>
// #include <QLabel>
// #include <QSlider>
// #include <QSpinBox>
// #include <QDoubleSpinBox>
// #include <QFileDialog>
// #include <QMenuBar>
// #include <QStatusBar>
// #include <QMessageBox>
// #include <QGroupBox>
// #include <QComboBox>
// #include <QCheckBox>
// #include <QProgressBar>
// #include <QTimer>

// #include "simuladorgravitacional.h"
// #include "cuerpoestelar.h"

// class VentanaPrincipal : public QMainWindow
// {
//     Q_OBJECT
// public:
//     VentanaPrincipal(QWidget *parent = nullptr);
//     ~VentanaPrincipal();
// private slots:
//     // Control de simulación
//     void onIniciarPausar();
//     void onReiniciar();
//     void onCargarArchivo();
//     void onGuardarTrayectorias();
//     void onGuardarEstadoActual();

//     // Sistemas predefinidos
//     void onCargarSistema1();
//     void onCargarSistema2();

//     // Configuración
//     void onCambiarVelocidad(int valor);
//     void onCambiarZoom(int valor);
//     void onToggleTrayectorias(bool mostrar);
//     void onToggleEtiquetas(bool mostrar);

//     // Actualizaciones de simulación
//     void actualizarVisualizacion();
//     void actualizarInformacion();

// protected:
//     void closeEvent(QCloseEvent *event) override;
// private:
//     // Métodos de configuración de UI
//     void configurarUI();
//     void crearBarraHerramientas();
//     void crearPanelControl();
//     void crearVisualizacion();
//     void crearPanelInformacion();
//     void conectarSignales();

//     // Métodos utilitarios
//     void actualizarBotones();
//     void limpiarEscena();
//     void centrarVista();
//     void ajustarEscala();
//     QString formatearTiempo(double segundos) const;

//     // Widgets principales
//     QWidget* m_widgetCentral;
//     QGraphicsView* m_vistaGrafica;
//     QGraphicsScene* m_escena;

//     // Panel de control
//     QGroupBox* m_grupoControl;
//     QPushButton* m_botonIniciarPausar;
//     QPushButton* m_botonReiniciar;
//     QPushButton* m_botonCargarArchivo;
//     QPushButton* m_botonGuardarTrayectorias;
//     QPushButton* m_botonGuardarEstado;

//     // Sistemas predefinidos
//     QGroupBox* m_grupoSistemas;
//     QPushButton* m_botonSistema1;
//     QPushButton* m_botonSistema2;

//     // Configuración de visualización
//     QGroupBox* m_grupoVisualizacion;
//     QSlider* m_sliderVelocidad;
//     QSlider* m_sliderZoom;
//     QCheckBox* m_checkTrayectorias;
//     QCheckBox* m_checkEtiquetas;

//     // Panel de información
//     QGroupBox* m_grupoInformacion;
//     QLabel* m_labelTiempo;
//     QLabel* m_labelIteracion;
//     QLabel* m_labelNumCuerpos;
//     QLabel* m_labelEstado;

//     // Simulador
//     SimuladorGravitacional* m_simulador;

//     // Estado de la aplicación
//     bool m_mostrarTrayectorias;
//     bool m_mostrarEtiquetas;
//     double m_factorZoom;
//     QString m_ultimoArchivo;

//     // Colores para los cuerpos
//     QList<QColor> m_coloresCuerpos;
//     void inicializarColores();
// };
// #endif // VENTANAPRINCIPAL_H


#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QProgressBar>
#include <QTimer>
#include <QLineEdit>
#include <QDialog>
#include <QFormLayout>

#include "simuladorgravitacional.h"
#include "cuerpoestelar.h"

// NUEVA CLASE: Diálogo para agregar cuerpos
class DialogoAgregarCuerpo : public QDialog
{
    Q_OBJECT
public:
    explicit DialogoAgregarCuerpo(QWidget *parent = nullptr);

    QString getNombre() const;
    double getPosX() const;
    double getPosY() const;
    double getMasa() const;
    double getRadio() const;
    double getVelX() const;
    double getVelY() const;
    QColor getColor() const;

private slots:
    void seleccionarColor();

private:
    QLineEdit* m_lineNombre;
    QDoubleSpinBox* m_spinPosX;
    QDoubleSpinBox* m_spinPosY;
    QDoubleSpinBox* m_spinMasa;
    QDoubleSpinBox* m_spinRadio;
    QDoubleSpinBox* m_spinVelX;
    QDoubleSpinBox* m_spinVelY;
    QPushButton* m_botonColor;
    QColor m_colorSeleccionado;
};

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private slots:
    // Control de simulación
    void onIniciarPausar();
    void onReiniciar();
    void onCargarArchivo();
    //void onGuardarTrayectorias();
    //void onGuardarEstadoActual();

    // NUEVOS SLOTS: Funcionalidades adicionales
    void onResetearPosicionesOriginales();
    void onAgregarCuerpo();
    void onVerificarConArchivo();
    void onResetearZoom();

    // Sistemas predefinidos
    void onCargarSistema1();
    void onCargarSistema2();

    // Configuración
    void onCambiarVelocidad(int valor);
    void onCambiarZoom(int valor);
    void onToggleTrayectorias(bool mostrar);
    void onToggleEtiquetas(bool mostrar);
    void onToggleColisiones(bool detectar); // NUEVO

    // Actualizaciones de simulación
    void actualizarVisualizacion();
    void actualizarInformacion();
    void onColisionDetectada(const QString& cuerpo1, const QString& cuerpo2); // NUEVO

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Métodos de configuración de UI
    void configurarUI();
    void crearBarraHerramientas();
    void crearPanelControl();
    void crearVisualizacion();
    void crearPanelInformacion();
    void conectarSignales();

    // Métodos utilitarios
    void actualizarBotones();
    void limpiarEscena();
    void centrarVista();
    void ajustarEscala();
    QString formatearTiempo(double segundos) const;

    // Widgets principales
    QWidget* m_widgetCentral;
    QGraphicsView* m_vistaGrafica;
    QGraphicsScene* m_escena;

    // Panel de control
    QGroupBox* m_grupoControl;
    QPushButton* m_botonIniciarPausar;
    QPushButton* m_botonReiniciar;
    QPushButton* m_botonCargarArchivo;
    //QPushButton* m_botonGuardarTrayectorias;
    //QPushButton* m_botonGuardarEstado;

    // NUEVOS BOTONES
    QPushButton* m_botonResetearPosiciones;
    QPushButton* m_botonAgregarCuerpo;
    QPushButton* m_botonVerificarArchivo;

    // Sistemas predefinidos
    QGroupBox* m_grupoSistemas;
    QPushButton* m_botonSistema1;
    QPushButton* m_botonSistema2;

    // Configuración de visualización
    QGroupBox* m_grupoVisualizacion;
    QSlider* m_sliderVelocidad;
    QSlider* m_sliderZoom;
    QCheckBox* m_checkTrayectorias;
    QCheckBox* m_checkEtiquetas;
    QCheckBox* m_checkColisiones; // NUEVO
    QPushButton* m_botonResetearZoom; // NUEVO

    // Panel de información
    QGroupBox* m_grupoInformacion;
    QLabel* m_labelTiempo;
    QLabel* m_labelIteracion;
    QLabel* m_labelNumCuerpos;
    QLabel* m_labelEstado;
    QLabel* m_labelColisiones; // NUEVO
    QLabel* m_labelVerificacion; // NUEVO

    // Simulador
    SimuladorGravitacional* m_simulador;

    // Estado de la aplicación
    bool m_mostrarTrayectorias;
    bool m_mostrarEtiquetas;
    double m_factorZoom;
    double m_factorZoomOriginal; // NUEVO: Para resetear zoom
    QString m_ultimoArchivo;

    // Colores para los cuerpos
    QList<QColor> m_coloresCuerpos;
    void inicializarColores();
};

#endif // VENTANAPRINCIPAL_H
