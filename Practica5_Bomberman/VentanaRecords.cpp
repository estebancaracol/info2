#include "VentanaRecords.h"
#include <QFont>
#include <QMessageBox>

VentanaRecords::VentanaRecords(QWidget *parent)
    : QDialog(parent), esModoNuevoRecord(false), puntuacionActual(0), nivelActual(1), tiempoActual(0) {
    configurarUI();
    mostrarRecords();
}

VentanaRecords::VentanaRecords(int puntuacion, int nivel, int tiempoJuego, QWidget *parent)
    : QDialog(parent), esModoNuevoRecord(true), puntuacionActual(puntuacion),
    nivelActual(nivel), tiempoActual(tiempoJuego) {
    configurarUI();
    configurarVentanaNuevoRecord(puntuacion, nivel, tiempoJuego);
}

void VentanaRecords::configurarUI() {
    setFixedSize(500, 600);
    setWindowTitle("Records de Bomberman");
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setModal(true);

    layoutPrincipal = new QVBoxLayout(this);

    // Título
    labelTitulo = new QLabel("🏆 RECORDS DE BOMBERMAN 🏆");
    labelTitulo->setAlignment(Qt::AlignCenter);
    QFont fuenteTitulo;
    fuenteTitulo.setPointSize(16);
    fuenteTitulo.setBold(true);
    labelTitulo->setFont(fuenteTitulo);
    labelTitulo->setStyleSheet("color: #DAA520; margin: 10px;");

    // Instrucciones (inicialmente oculto)
    labelInstrucciones = new QLabel("¡Felicidades! Has conseguido un nuevo record.\nIngresa tu nombre:");
    labelInstrucciones->setAlignment(Qt::AlignCenter);
    labelInstrucciones->setStyleSheet("color: #008000; margin: 10px;");
    labelInstrucciones->setVisible(false);

    // Input para nombre (inicialmente oculto)
    inputNombre = new QLineEdit();
    inputNombre->setPlaceholderText("Ingresa tu nombre aquí...");
    inputNombre->setMaxLength(20);
    inputNombre->setAlignment(Qt::AlignCenter);
    inputNombre->setStyleSheet("padding: 8px; border: 2px solid #DAA520; border-radius: 5px;");
    inputNombre->setVisible(false);

    // Lista de records
    listaRecords = new QListWidget();
    listaRecords->setStyleSheet(R"(
        QListWidget {
            background-color: #2b2b2b;
            color: white;
            border: 2px solid #DAA520;
            border-radius: 5px;
            padding: 5px;
        }
        QListWidget::item {
            padding: 8px;
            border-bottom: 1px solid #444;
        }
        QListWidget::item:selected {
            background-color: #DAA520;
            color: black;
        }
    )");

    // Botones
    QHBoxLayout *layoutBotones = new QHBoxLayout();

    botonGuardar = new QPushButton("💾 Guardar Record");
    botonGuardar->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
        QPushButton:disabled {
            background-color: #cccccc;
            color: #666666;
        }
    )");
    botonGuardar->setVisible(false);

    botonCerrar = new QPushButton("🚪 Cerrar");
    botonCerrar->setStyleSheet(R"(
        QPushButton {
            background-color: #f44336;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #da190b;
        }
    )");

    layoutBotones->addWidget(botonGuardar);
    layoutBotones->addWidget(botonCerrar);

    // Agregar todo al layout principal
    layoutPrincipal->addWidget(labelTitulo);
    layoutPrincipal->addWidget(labelInstrucciones);
    layoutPrincipal->addWidget(inputNombre);
    layoutPrincipal->addWidget(listaRecords);
    layoutPrincipal->addLayout(layoutBotones);

    // Conectar señales
    connect(botonGuardar, &QPushButton::clicked, this, &VentanaRecords::guardarNuevoRecord);
    connect(botonCerrar, &QPushButton::clicked, this, &VentanaRecords::cerrarVentana);
    connect(inputNombre, &QLineEdit::returnPressed, this, &VentanaRecords::guardarNuevoRecord);

    // Configurar estilo de la ventana
    setStyleSheet(R"(
        QDialog {
            background-color: #1e1e1e;
            color: white;
        }
    )");
}

void VentanaRecords::mostrarRecords() {
    actualizarListaRecords();
}


void VentanaRecords::configurarVentanaNuevoRecord(int puntuacion, int nivel, int tiempoJuego) {
    // SIEMPRE mostrar la opción de guardar record si hay puntuación
    if (puntuacion > 0) {
        labelInstrucciones->setText("¡Ingresa tu nombre para guardar tu puntuación!");
        labelInstrucciones->setVisible(true);
        inputNombre->setVisible(true);
        botonGuardar->setVisible(true);

        // Agregar información del record actual
        QString infoRecord = QString("Puntuación: %1 | Nivel: %2 | Tiempo: %3s")
                                 .arg(puntuacion)
                                 .arg(nivel)
                                 .arg(tiempoJuego);

        QLabel *labelInfo = new QLabel(infoRecord);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setStyleSheet("color: #FFD700; margin: 5px; font-weight: bold;");
        layoutPrincipal->insertWidget(2, labelInfo);

        inputNombre->setFocus();
    }

    actualizarListaRecords();
}

void VentanaRecords::actualizarListaRecords() {
    listaRecords->clear();

    SistemaRecords* sistema = SistemaRecords::getInstance();
    QList<Record> records = sistema->obtenerMejoresRecords(10);

    if (records.isEmpty()) {
        listaRecords->addItem("🎯 No hay records aún. ¡Sé el primero!");
        return;
    }

    for (int i = 0; i < records.size(); ++i) {
        QString posicion;
        switch (i) {
        case 0: posicion = "🥇"; break;
        case 1: posicion = "🥈"; break;
        case 2: posicion = "🥉"; break;
        default: posicion = QString("%1.").arg(i + 1); break;
        }

        QString recordTexto = QString("%1 %2")
                                  .arg(posicion)
                                  .arg(sistema->formatearRecord(records[i]));

        listaRecords->addItem(recordTexto);
    }
}

void VentanaRecords::guardarNuevoRecord() {
    QString nombre = inputNombre->text().trimmed();

    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Nombre vacío", "Por favor, ingresa tu nombre para guardar el record.");
        inputNombre->setFocus();
        return;
    }

    SistemaRecords* sistema = SistemaRecords::getInstance();
    sistema->agregarRecord(nombre, puntuacionActual, nivelActual, tiempoActual);

    // Ocultar elementos de nuevo record
    labelInstrucciones->setVisible(false);
    inputNombre->setVisible(false);
    botonGuardar->setVisible(false);

    // Actualizar lista y mostrar mensaje
    actualizarListaRecords();
    labelTitulo->setText("🏆 RECORD GUARDADO 🏆");

    QMessageBox::information(this, "¡Record Guardado!",
                             QString("¡Felicidades %1!\nTu record ha sido guardado exitosamente.").arg(nombre));
}

void VentanaRecords::cerrarVentana() {
    accept();
}
