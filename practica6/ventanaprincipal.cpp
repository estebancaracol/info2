#include "ventanaprincipal.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QCloseEvent>
#include <QColorDialog>
#include <QInputDialog>

// IMPLEMENTACIÓN DEL DIÁLOGO PARA AGREGAR CUERPOS
DialogoAgregarCuerpo::DialogoAgregarCuerpo(QWidget *parent) : QDialog(parent), m_colorSeleccionado(Qt::blue)
{
    setWindowTitle("Agregar Nuevo Cuerpo Estelar");
    setModal(true);
    resize(350, 400);
    QFormLayout* layout = new QFormLayout(this);
    // Crear controles
    m_lineNombre = new QLineEdit("NuevoCuerpo");

    m_spinPosX = new QDoubleSpinBox();
    m_spinPosX->setRange(-50000, 50000);
    m_spinPosX->setValue(0);
    m_spinPosX->setSuffix(" px");

    m_spinPosY = new QDoubleSpinBox();
    m_spinPosY->setRange(-50000, 50000);
    m_spinPosY->setValue(0);
    m_spinPosY->setSuffix(" px");

    m_spinMasa = new QDoubleSpinBox();
    m_spinMasa->setRange(0.1, 999999);
    m_spinMasa->setValue(100);
    m_spinMasa->setSuffix(" kg");

    m_spinRadio = new QDoubleSpinBox();
    m_spinRadio->setRange(1, 1000);
    m_spinRadio->setValue(50);
    m_spinRadio->setSuffix(" px");

    m_spinVelX = new QDoubleSpinBox();
    m_spinVelX->setRange(-1000, 1000);
    m_spinVelX->setValue(0);
    m_spinVelX->setSuffix(" px/s");

    m_spinVelY = new QDoubleSpinBox();
    m_spinVelY->setRange(-1000, 1000);
    m_spinVelY->setValue(0);
    m_spinVelY->setSuffix(" px/s");

    m_botonColor = new QPushButton("Seleccionar Color");
    m_botonColor->setStyleSheet(QString("background-color: %1").arg(m_colorSeleccionado.name()));

    connect(m_botonColor, &QPushButton::clicked, this, &DialogoAgregarCuerpo::seleccionarColor);
    // Agregar al layout
    layout->addRow("Nombre:", m_lineNombre);
    layout->addRow("Posición X:", m_spinPosX);
    layout->addRow("Posición Y:", m_spinPosY);
    layout->addRow("Masa:", m_spinMasa);
    layout->addRow("Radio:", m_spinRadio);
    layout->addRow("Velocidad X:", m_spinVelX);
    layout->addRow("Velocidad Y:", m_spinVelY);
    layout->addRow("Color:", m_botonColor);
    // Botones de confirmación
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* botonAceptar = new QPushButton("Crear Cuerpo");
    QPushButton* botonCancelar = new QPushButton("Cancelar");

    connect(botonAceptar, &QPushButton::clicked, this, &QDialog::accept);
    connect(botonCancelar, &QPushButton::clicked, this, &QDialog::reject);

    layoutBotones->addWidget(botonAceptar);
    layoutBotones->addWidget(botonCancelar);

    QWidget* widgetBotones = new QWidget;
    widgetBotones->setLayout(layoutBotones);
    layout->addRow(widgetBotones);
}

void DialogoAgregarCuerpo::seleccionarColor()
{
    QColor color = QColorDialog::getColor(m_colorSeleccionado, this, "Seleccionar Color del Cuerpo");
    if (color.isValid()) {
        m_colorSeleccionado = color;
        m_botonColor->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}

QString DialogoAgregarCuerpo::getNombre() const { return m_lineNombre->text(); }
double DialogoAgregarCuerpo::getPosX() const { return m_spinPosX->value(); }
double DialogoAgregarCuerpo::getPosY() const { return m_spinPosY->value(); }
double DialogoAgregarCuerpo::getMasa() const { return m_spinMasa->value(); }
double DialogoAgregarCuerpo::getRadio() const { return m_spinRadio->value(); }
double DialogoAgregarCuerpo::getVelX() const { return m_spinVelX->value(); }
double DialogoAgregarCuerpo::getVelY() const { return m_spinVelY->value(); }
QColor DialogoAgregarCuerpo::getColor() const { return m_colorSeleccionado; }

// IMPLEMENTACIÓN DEL DIÁLOGO PARA EDITAR CUERPOS EXISTENTES
DialogoEditarCuerpo::DialogoEditarCuerpo(CuerpoEstelar* cuerpo, QWidget *parent)
    : QDialog(parent), m_cuerpo(cuerpo)
{
    setWindowTitle("Editar Cuerpo: " + cuerpo->getNombre());
    setModal(true);
    resize(400, 450);
    QFormLayout* layout = new QFormLayout(this);
    // Crear controles con valores actuales del cuerpo
    m_lineNombre = new QLineEdit(cuerpo->getNombre());

    m_spinPosX = new QDoubleSpinBox();
    m_spinPosX->setRange(-50000, 50000);
    m_spinPosX->setValue(cuerpo->getPosX());
    m_spinPosX->setSuffix(" px");

    m_spinPosY = new QDoubleSpinBox();
    m_spinPosY->setRange(-50000, 50000);
    m_spinPosY->setValue(cuerpo->getPosY());
    m_spinPosY->setSuffix(" px");

    m_spinMasa = new QDoubleSpinBox();
    m_spinMasa->setRange(0.1, 999999);
    m_spinMasa->setValue(cuerpo->getMasa());
    m_spinMasa->setSuffix(" kg");

    m_spinRadio = new QDoubleSpinBox();
    m_spinRadio->setRange(1, 1000);
    m_spinRadio->setValue(cuerpo->getRadio());
    m_spinRadio->setSuffix(" px");

    m_spinVelX = new QDoubleSpinBox();
    m_spinVelX->setRange(-1000, 1000);
    m_spinVelX->setValue(cuerpo->getVelX());
    m_spinVelX->setSuffix(" px/s");

    m_spinVelY = new QDoubleSpinBox();
    m_spinVelY->setRange(-1000, 1000);
    m_spinVelY->setValue(cuerpo->getVelY());
    m_spinVelY->setSuffix(" px/s");

    // Color actual (usaremos azul por defecto si no se puede obtener)
    m_colorSeleccionado = Qt::blue; // Color por defecto
    m_botonColor = new QPushButton("Cambiar Color");

    connect(m_botonColor, &QPushButton::clicked, this, &DialogoEditarCuerpo::seleccionarColor);
    // Agregar al layout
    layout->addRow("Nombre:", m_lineNombre);
    layout->addRow("Posición X:", m_spinPosX);
    layout->addRow("Posición Y:", m_spinPosY);
    layout->addRow("Masa:", m_spinMasa);
    layout->addRow("Radio:", m_spinRadio);
    layout->addRow("Velocidad X:", m_spinVelX);
    layout->addRow("Velocidad Y:", m_spinVelY);
    layout->addRow("Color:", m_botonColor);
    // Mensaje informativo
    QLabel* labelInfo = new QLabel("Los cambios se aplicarán inmediatamente.\n Cambiar masa/velocidad afectará el comportamiento físico.");
    labelInfo->setWordWrap(true);
    layout->addRow(labelInfo);
    // Botones de confirmación
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* botonAplicar = new QPushButton("Aplicar Cambios");
    QPushButton* botonCancelar = new QPushButton("Cancelar");

    connect(botonAplicar, &QPushButton::clicked, [this]() {
        aplicarCambios();
        accept();
    });
    connect(botonCancelar, &QPushButton::clicked, this, &QDialog::reject);

    layoutBotones->addWidget(botonAplicar);
    layoutBotones->addWidget(botonCancelar);

    QWidget* widgetBotones = new QWidget;
    widgetBotones->setLayout(layoutBotones);
    layout->addRow(widgetBotones);
}

void DialogoEditarCuerpo::seleccionarColor()
{
    QColor color = QColorDialog::getColor(m_colorSeleccionado, this, "Seleccionar Nuevo Color");
    if (color.isValid()) {
        m_colorSeleccionado = color;
    }
}

void DialogoEditarCuerpo::aplicarCambios()
{
    if (!m_cuerpo) return;

    // Aplicar todos los cambios al cuerpo
    m_cuerpo->setNombre(m_lineNombre->text());
    m_cuerpo->setPosicion(m_spinPosX->value(), m_spinPosY->value());
    m_cuerpo->setMasa(m_spinMasa->value());
    m_cuerpo->setRadio(m_spinRadio->value());
    m_cuerpo->setVelocidad(m_spinVelX->value(), m_spinVelY->value());
    m_cuerpo->setColor(m_colorSeleccionado);

    // Actualizar posición original para que el reset funcione con los nuevos valores
    m_cuerpo->guardarPosicionOriginal();
}

// IMPLEMENTACIÓN DE LA VENTANA PRINCIPAL
VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent), m_mostrarTrayectorias(true), m_mostrarEtiquetas(true),
    m_factorZoom(1.0), m_factorZoomOriginal(1.0)
{
    setWindowTitle("Simulador Gravitacional - Versión Mejorada");
    setMinimumSize(1200, 800);
    resize(1400, 900);
    // Crear simulador
    m_simulador = new SimuladorGravitacional(this);
    // Configurar interfaz
    configurarUI();
    conectarSignales();
    inicializarColores();
    // Estado inicial
    actualizarBotones();
    centrarVista();
    statusBar()->showMessage("Sistema Gravitacional - Cargue un archivo CSV/TXT o seleccione un sistema predefinido");
}

VentanaPrincipal::~VentanaPrincipal()
{
    if (m_simulador->estaSimulando()) {
        m_simulador->pausarSimulacion();
    }
}

void VentanaPrincipal::configurarUI()
{
    m_widgetCentral = new QWidget;
    setCentralWidget(m_widgetCentral);
    // Layout principal con splitter
    QHBoxLayout* layoutPrincipal = new QHBoxLayout(m_widgetCentral);
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    // Crear visualización (lado izquierdo)
    crearVisualizacion();
    // Crear panel de control (lado derecho)
    QWidget* panelDerecho = new QWidget;
    panelDerecho->setMaximumWidth(400);
    panelDerecho->setMinimumWidth(400);
    QVBoxLayout* layoutDerecho = new QVBoxLayout(panelDerecho);
    crearPanelControl();
    crearPanelInformacion();
    layoutDerecho->addWidget(m_grupoControl);
    layoutDerecho->addWidget(m_grupoSistemas);
    layoutDerecho->addWidget(m_grupoVisualizacion);
    layoutDerecho->addWidget(m_grupoInformacion);
    layoutDerecho->addStretch();
    // Configurar splitter
    splitter->addWidget(m_vistaGrafica);
    splitter->addWidget(panelDerecho);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    layoutPrincipal->addWidget(splitter);
}

void VentanaPrincipal::crearVisualizacion()
{
    // Crear vista gráfica
    m_vistaGrafica = new QGraphicsView;
    m_escena = new QGraphicsScene;
    m_vistaGrafica->setScene(m_escena);
    m_vistaGrafica->setRenderHint(QPainter::Antialiasing);
    m_vistaGrafica->setDragMode(QGraphicsView::RubberBandDrag);
    m_vistaGrafica->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    // Configurar escena
    m_escena->setSceneRect(-15000, -15000, 30000, 30000);
    m_escena->setBackgroundBrush(QBrush(QColor(10, 10, 30))); // Fondo espacio más oscuro
    // Dibujar grid de referencia mejorado
    QPen penGrid(QColor(40, 40, 60), 1, Qt::DotLine);
    for (int x = -15000; x <= 15000; x += 1000) {
        m_escena->addLine(x, -15000, x, 15000, penGrid);
    }
    for (int y = -15000; y <= 15000; y += 1000) {
        m_escena->addLine(-15000, y, 15000, y, penGrid);
    }
    // Líneas de ejes principales más visibles
    QPen penEjes(QColor(80, 80, 120), 3);
    m_escena->addLine(-15000, 0, 15000, 0, penEjes); // Eje X
    m_escena->addLine(0, -15000, 0, 15000, penEjes);  // Eje Y

    // Marcar origen
    QPen penOrigen(QColor(255, 255, 0), 2);
    m_escena->addEllipse(-50, -50, 100, 100, penOrigen);
}

void VentanaPrincipal::crearPanelControl()
{
    m_grupoControl = new QGroupBox("Control de Simulación");
    QVBoxLayout* layout = new QVBoxLayout(m_grupoControl);
    // Botones principales
    m_botonIniciarPausar = new QPushButton("Iniciar");
    m_botonReiniciar = new QPushButton("Reiniciar");
    // Botón de resetear posiciones
    m_botonResetearPosiciones = new QPushButton("Resetear a Posición Original");
    // Botón de cargar archivo
    m_botonCargarArchivo = new QPushButton("Cargar CSV/TXT");
    // Gestión de cuerpos
    m_botonAgregarCuerpo = new QPushButton("Agregar Cuerpo");

    // Botón para editar cuerpos existentes
    m_botonEditarCuerpo = new QPushButton("Editar Cuerpo");

    m_botonVerificarArchivo = new QPushButton("Verificar con Archivo");
    layout->addWidget(m_botonIniciarPausar);
    layout->addWidget(m_botonReiniciar);
    layout->addWidget(m_botonResetearPosiciones);
    layout->addWidget(new QLabel(""));
    layout->addWidget(m_botonCargarArchivo);
    layout->addWidget(m_botonAgregarCuerpo);
    layout->addWidget(m_botonEditarCuerpo); // NUEVO
    layout->addWidget(new QLabel(""));
    layout->addWidget(m_botonVerificarArchivo);
    // Crear panel de sistemas predefinidos
    m_grupoSistemas = new QGroupBox("Sistemas Predefinidos");
    QVBoxLayout* layoutSistemas = new QVBoxLayout(m_grupoSistemas);
    m_botonSistema1 = new QPushButton("Sistema 1 (3 cuerpos)");
    m_botonSistema2 = new QPushButton("Sistema 2 (5 cuerpos)");
    layoutSistemas->addWidget(m_botonSistema1);
    layoutSistemas->addWidget(m_botonSistema2);
}

void VentanaPrincipal::crearPanelInformacion()
{
    m_grupoVisualizacion = new QGroupBox("Visualización");
    QGridLayout* layoutVis = new QGridLayout(m_grupoVisualizacion);
    // Control de velocidad
    layoutVis->addWidget(new QLabel("Velocidad:"), 0, 0);
    m_sliderVelocidad = new QSlider(Qt::Horizontal);
    m_sliderVelocidad->setRange(1,100);
    m_sliderVelocidad->setValue(20);
    layoutVis->addWidget(m_sliderVelocidad, 0, 1);
    // Control de zoom con botón de reset
    layoutVis->addWidget(new QLabel("Zoom:"), 1, 0);
    m_sliderZoom = new QSlider(Qt::Horizontal);
    m_sliderZoom->setRange(10, 500);
    m_sliderZoom->setValue(100);
    layoutVis->addWidget(m_sliderZoom, 1, 1);

    m_botonResetearZoom = new QPushButton("Reset");
    m_botonResetearZoom->setMaximumWidth(60);
    layoutVis->addWidget(m_botonResetearZoom, 1, 2);
    // Checkboxes
    m_checkTrayectorias = new QCheckBox("Mostrar Trayectorias");
    m_checkTrayectorias->setChecked(true);
    m_checkEtiquetas = new QCheckBox("Mostrar Etiquetas");
    m_checkEtiquetas->setChecked(true);

    m_checkColisiones = new QCheckBox("Detectar Colisiones");
    m_checkColisiones->setChecked(true);
    m_checkColisiones->setStyleSheet("QCheckBox { color: #FF5722; font-weight: bold; }");
    layoutVis->addWidget(m_checkTrayectorias, 2, 0, 1, 2);
    layoutVis->addWidget(m_checkEtiquetas, 3, 0, 1, 2);
    layoutVis->addWidget(m_checkColisiones, 4, 0, 1, 2);
    // Panel de información
    m_grupoInformacion = new QGroupBox("Información del Sistema");
    QGridLayout* layoutInfo = new QGridLayout(m_grupoInformacion);
    m_labelTiempo = new QLabel("Tiempo: 0.0 s");
    m_labelIteracion = new QLabel("Iteración: 0");
    m_labelNumCuerpos = new QLabel("Cuerpos: 0");
    m_labelEstado = new QLabel("Estado: Detenido");

    m_labelColisiones = new QLabel("Colisiones: No");
    m_labelVerificacion = new QLabel("Verificación: No realizada");
    m_labelVerificacion->setStyleSheet("QLabel { color: #FFC107; }");
    layoutInfo->addWidget(m_labelTiempo, 0, 0);
    layoutInfo->addWidget(m_labelIteracion, 1, 0);
    layoutInfo->addWidget(m_labelNumCuerpos, 2, 0);
    layoutInfo->addWidget(m_labelEstado, 3, 0);
    layoutInfo->addWidget(m_labelColisiones, 4, 0);
    layoutInfo->addWidget(m_labelVerificacion, 5, 0);
}

void VentanaPrincipal::conectarSignales()
{
    // Conectar botones existentes
    connect(m_botonIniciarPausar, &QPushButton::clicked, this, &VentanaPrincipal::onIniciarPausar);
    connect(m_botonReiniciar, &QPushButton::clicked, this, &VentanaPrincipal::onReiniciar);
    connect(m_botonCargarArchivo, &QPushButton::clicked, this, &VentanaPrincipal::onCargarArchivo);
    connect(m_botonSistema1, &QPushButton::clicked, this, &VentanaPrincipal::onCargarSistema1);
    connect(m_botonSistema2, &QPushButton::clicked, this, &VentanaPrincipal::onCargarSistema2);

    // Conectar nuevos botones
    connect(m_botonResetearPosiciones, &QPushButton::clicked, this, &VentanaPrincipal::onResetearPosicionesOriginales);
    connect(m_botonAgregarCuerpo, &QPushButton::clicked, this, &VentanaPrincipal::onAgregarCuerpo);
    connect(m_botonEditarCuerpo, &QPushButton::clicked, this, &VentanaPrincipal::onEditarCuerpo); // NUEVO
    connect(m_botonVerificarArchivo, &QPushButton::clicked, this, &VentanaPrincipal::onVerificarConArchivo);
    connect(m_botonResetearZoom, &QPushButton::clicked, this, &VentanaPrincipal::onResetearZoom);
    // Conectar controles de visualización
    connect(m_sliderVelocidad, &QSlider::valueChanged, this, &VentanaPrincipal::onCambiarVelocidad);
    connect(m_sliderZoom, &QSlider::valueChanged, this, &VentanaPrincipal::onCambiarZoom);
    connect(m_checkTrayectorias, &QCheckBox::toggled, this, &VentanaPrincipal::onToggleTrayectorias);
    connect(m_checkEtiquetas, &QCheckBox::toggled, this, &VentanaPrincipal::onToggleEtiquetas);
    connect(m_checkColisiones, &QCheckBox::toggled, this, &VentanaPrincipal::onToggleColisiones);
    // Conectar señales del simulador
    connect(m_simulador, &SimuladorGravitacional::simulacionIniciada, this, &VentanaPrincipal::actualizarBotones);
    connect(m_simulador, &SimuladorGravitacional::simulacionPausada, this, &VentanaPrincipal::actualizarBotones);
    connect(m_simulador, &SimuladorGravitacional::simulacionReiniciada, this, &VentanaPrincipal::actualizarBotones);
    connect(m_simulador, &SimuladorGravitacional::estadoActualizado, this, &VentanaPrincipal::actualizarVisualizacion);
    connect(m_simulador, &SimuladorGravitacional::estadoActualizado, this, &VentanaPrincipal::actualizarInformacion);
    connect(m_simulador, &SimuladorGravitacional::colisionDetectada, this, &VentanaPrincipal::onColisionDetectada);

    connect(m_simulador, &SimuladorGravitacional::errorSimulacion, [this](const QString& mensaje) {
        QMessageBox::warning(this, "Error de Simulación", mensaje);
        statusBar()->showMessage("Error: " + mensaje, 5000);
    });
}

// IMPLEMENTACIÓN DE SLOTS
void VentanaPrincipal::onIniciarPausar()
{
    if (m_simulador->estaSimulando()) {
        m_simulador->pausarSimulacion();
        statusBar()->showMessage("Simulación pausada");
    } else {
        if (m_simulador->getNumCuerpos() > 0) {
            m_simulador->iniciarSimulacion();
            statusBar()->showMessage("Simulación iniciada");
        } else {
            QMessageBox::information(this, "Información",
                                     "Cargue un archivo CSV/TXT, seleccione un sistema predefinido o agregue cuerpos manualmente.");
        }
    }
}

void VentanaPrincipal::onReiniciar()
{
    m_simulador->reiniciarSimulacion();
    actualizarVisualizacion();
    statusBar()->showMessage("Simulación reiniciada");
}
void VentanaPrincipal::onCargarArchivo()
{
    QString archivo = QFileDialog::getOpenFileName(this,
                                                   "Cargar archivo de sistema", m_ultimoArchivo,
                                                   "Archivos de datos (*.csv *.txt);;Archivos CSV (*.csv);;Archivos TXT (*.txt);;Todos los archivos (*)");
    if (!archivo.isEmpty()) {
        if (m_simulador->cargarArchivoGenerico(archivo)) {
            m_ultimoArchivo = archivo;
            actualizarVisualizacion();
            centrarVista();
            statusBar()->showMessage(QString("Cargado: %1 (%2 cuerpos)")
                                         .arg(QFileInfo(archivo).fileName())
                                         .arg(m_simulador->getNumCuerpos()));
        }
    }
}

void VentanaPrincipal::onResetearPosicionesOriginales()
{
    if (m_simulador->getNumCuerpos() == 0) {
        QMessageBox::information(this, "Información", "No hay cuerpos para resetear.");
        return;
    }

    m_simulador->resetearPosicionesOriginales();
    actualizarVisualizacion();
    centrarVista();
    statusBar()->showMessage("Cuerpos regresados a su posición original");
}

void VentanaPrincipal::onAgregarCuerpo()
{
    DialogoAgregarCuerpo dialogo(this);
    if (dialogo.exec() == QDialog::Accepted) {
        CuerpoEstelar* nuevoCuerpo = new CuerpoEstelar(
            dialogo.getNombre(),
            dialogo.getPosX(),
            dialogo.getPosY(),
            dialogo.getMasa(),
            dialogo.getRadio(),
            dialogo.getVelX(),
            dialogo.getVelY()
            );

        nuevoCuerpo->setColor(dialogo.getColor());
        m_simulador->agregarCuerpo(nuevoCuerpo);

        actualizarVisualizacion();
        statusBar()->showMessage(QString("Cuerpo '%1' agregado al sistema").arg(dialogo.getNombre()));
    }
}

// Implementación de editar cuerpo
void VentanaPrincipal::onEditarCuerpo()
{
    if (m_simulador->getNumCuerpos() == 0) {
        QMessageBox::information(this, "Información", "No hay cuerpos para editar.");
        return;
    }

    // Crear lista de cuerpos para seleccionar
    QStringList nombresCuerpos;
    const QList<CuerpoEstelar*>& cuerpos = m_simulador->getCuerpos();

    for (const CuerpoEstelar* cuerpo : cuerpos) {
        nombresCuerpos << QString("%1 (Masa: %2, Vel: %3,%4)")
        .arg(cuerpo->getNombre())
            .arg(cuerpo->getMasa(), 0, 'f', 1)
            .arg(cuerpo->getVelX(), 0, 'f', 1)
            .arg(cuerpo->getVelY(), 0, 'f', 1);
    }

    bool ok;
    QString seleccion = QInputDialog::getItem(this,
                                              "Seleccionar Cuerpo a Editar",
                                              "Elija el cuerpo que desea modificar:",
                                              nombresCuerpos, 0, false, &ok);

    if (ok && !seleccion.isEmpty()) {
        int indice = nombresCuerpos.indexOf(seleccion);
        if (indice >= 0 && indice < cuerpos.size()) {
            CuerpoEstelar* cuerpoSeleccionado = cuerpos[indice];

            DialogoEditarCuerpo dialogoEditar(cuerpoSeleccionado, this);
            if (dialogoEditar.exec() == QDialog::Accepted) {
                actualizarVisualizacion();
                statusBar()->showMessage(QString("Cuerpo '%1' modificado exitosamente")
                                             .arg(cuerpoSeleccionado->getNombre()));
            }
        }
    }
}

void VentanaPrincipal::onVerificarConArchivo()
{
    QString archivo = QFileDialog::getOpenFileName(this,
                                                   "Seleccionar archivo de verificación", m_ultimoArchivo,
                                                   "Archivos de datos (*.txt *.csv);;Todos los archivos (*)");
    if (!archivo.isEmpty()) {
        double porcentaje = m_simulador->verificarConArchivo(archivo);

        QString mensaje = QString("Verificación completada: %1% de precisión").arg(porcentaje, 0, 'f', 2);
        m_labelVerificacion->setText(QString("Verificación: %1%").arg(porcentaje, 0, 'f', 1));

        if (porcentaje >= 90.0) {
            statusBar()->showMessage(mensaje + " - ¡Excelente precisión!");
        } else if (porcentaje >= 70.0) {
            statusBar()->showMessage(mensaje + " - Precisión aceptable");
        } else {
            statusBar()->showMessage(mensaje + " - Baja precisión");
        }

        QMessageBox::information(this, "Verificación", mensaje);
    }
}

void VentanaPrincipal::onResetearZoom()
{
    m_factorZoom = m_factorZoomOriginal;
    m_sliderZoom->setValue(100);
    ajustarEscala();
    centrarVista();
    statusBar()->showMessage("Zoom restablecido a vista original");
}

void VentanaPrincipal::onCargarSistema1()
{
    m_simulador->configurarSistema1();
    actualizarVisualizacion();
    centrarVista();
    statusBar()->showMessage("Sistema 1 cargado (3 cuerpos)");
}

void VentanaPrincipal::onCargarSistema2()
{
    m_simulador->configurarSistema2();
    actualizarVisualizacion();
    centrarVista();
    statusBar()->showMessage("Sistema 2 cargado (5 cuerpos)");
}

void VentanaPrincipal::onCambiarVelocidad(int valor)
{
    int intervalo = 201 - (valor * 2);
    m_simulador->setIntervaloActualizacion(intervalo);
}

void VentanaPrincipal::onCambiarZoom(int valor)
{
    m_factorZoom = valor / 100.0;
    ajustarEscala();
}

void VentanaPrincipal::onToggleTrayectorias(bool mostrar)
{
    m_mostrarTrayectorias = mostrar;
    m_simulador->setMostrarTrayectorias(mostrar);
    actualizarVisualizacion();
}

void VentanaPrincipal::onToggleEtiquetas(bool mostrar)
{
    m_mostrarEtiquetas = mostrar;
    actualizarVisualizacion();
}

void VentanaPrincipal::onToggleColisiones(bool detectar)
{
    m_simulador->setDeteccionColisiones(detectar);
    if (detectar) {
        statusBar()->showMessage("Detección de colisiones activada");
    } else {
        statusBar()->showMessage("Detección de colisiones desactivada");
        m_labelColisiones->setText("Colisiones: Desactivadas");
    }
}

void VentanaPrincipal::onColisionDetectada(const QString& cuerpo1, const QString& cuerpo2)
{
    QString mensaje = QString("¡COLISIÓN! %1 ↔ %2").arg(cuerpo1).arg(cuerpo2);
    m_labelColisiones->setText("Colisiones: Sí");
    statusBar()->showMessage(mensaje, 3000);
}

void VentanaPrincipal::actualizarVisualizacion()
{
    const QList<CuerpoEstelar*>& cuerpos = m_simulador->getCuerpos();
    for (int i = 0; i < cuerpos.size(); ++i) {
        CuerpoEstelar* cuerpo = cuerpos[i];
        // Asignar color si no tiene uno específico
        if (i < m_coloresCuerpos.size()) {
            if (!cuerpo->tieneColorPersonalizado()) {
                cuerpo->setColor(m_coloresCuerpos[i]);
            }
        }
        // Agregar cuerpo a la escena si no está ya agregado
        if (cuerpo->scene() != m_escena) {
            m_escena->addItem(cuerpo);
        }
    }
}

void VentanaPrincipal::actualizarInformacion()
{
    m_labelTiempo->setText(QString("Tiempo: %1 s").arg(formatearTiempo(m_simulador->getTiempoSimulacion())));
    m_labelIteracion->setText(QString("Iteración: %1").arg(m_simulador->getIteracion()));
    m_labelNumCuerpos->setText(QString("Cuerpos: %1").arg(m_simulador->getNumCuerpos()));
    m_labelEstado->setText(QString("Estado: %1").arg(m_simulador->estaSimulando() ? "Simulando" : "Detenido"));

    // Actualizar estado de colisiones
    if (m_checkColisiones->isChecked()) {
        if (!m_simulador->hayColisionesActivas()) {
            m_labelColisiones->setText("Colisiones: No");
            m_labelColisiones->setStyleSheet("QLabel { color: #4CAF50; }");
        }
    }
}

void VentanaPrincipal::actualizarBotones()
{
    bool simulando = m_simulador->estaSimulando();
    bool hayCuerpos = m_simulador->getNumCuerpos() > 0;
    m_botonIniciarPausar->setText(simulando ? "Pausar" : "Iniciar");
    m_botonIniciarPausar->setEnabled(hayCuerpos);
    m_botonReiniciar->setEnabled(hayCuerpos);
    m_botonResetearPosiciones->setEnabled(hayCuerpos);
    m_botonEditarCuerpo->setEnabled(hayCuerpos); // NUEVO
    m_botonVerificarArchivo->setEnabled(hayCuerpos);
}

void VentanaPrincipal::limpiarEscena()
{
    QList<QGraphicsItem*> items = m_escena->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<CuerpoEstelar*>(item) != nullptr) {
            continue;
        }
    }
}

void VentanaPrincipal::centrarVista()
{
    if (m_simulador->getNumCuerpos() > 0) {
        m_vistaGrafica->fitInView(m_escena->itemsBoundingRect(), Qt::KeepAspectRatio);
        m_vistaGrafica->scale(0.9, 0.9);
    } else {
        m_vistaGrafica->centerOn(0, 0);
    }
}

void VentanaPrincipal::ajustarEscala()
{
    m_vistaGrafica->setTransform(QTransform::fromScale(m_factorZoom, m_factorZoom));
}

QString VentanaPrincipal::formatearTiempo(double segundos) const
{
    if (segundos < 60) {
        return QString::number(segundos, 'f', 1);
    } else if (segundos < 3600) {
        int minutos = segundos / 60;
        double seg = std::fmod(segundos, 60);
        return QString("%1:%2").arg(minutos).arg(seg, 0, 'f', 1);
    } else {
        int horas = segundos / 3600;
        int minutos = (segundos - horas * 3600) / 60;
        double seg = std::fmod(segundos, 60);
        return QString("%1:%2:%3").arg(horas).arg(minutos, 2, 10, QChar('0')).arg(seg, 0, 'f', 1);
    }
}

void VentanaPrincipal::inicializarColores()
{
    m_coloresCuerpos = {
        QColor(255, 100, 100),  // Rojo
        QColor(255, 255, 100),  // Amarillo
        QColor(100, 100, 255),  // Azul
        QColor(100, 255, 100),  // Verde
        QColor(255, 100, 255),  // Magenta
        QColor(100, 255, 255),  // Cian
        QColor(255, 150, 100),  // Naranja
        QColor(150, 100, 255),  // Violeta
        QColor(255, 255, 255),  // Blanco
        QColor(200, 200, 200)   // Gris claro
    };
}

void VentanaPrincipal::closeEvent(QCloseEvent *event)
{
    if (m_simulador->estaSimulando()) {
        int respuesta = QMessageBox::question(this, "Confirmar salida",
                                              "La simulación está en curso. ¿Desea salir de todos modos?",
                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (respuesta == QMessageBox::Yes) {
            m_simulador->pausarSimulacion();
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}
