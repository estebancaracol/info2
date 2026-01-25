/****************************************************************************
** Meta object code from reading C++ file 'ventanaprincipal.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ventanaprincipal.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ventanaprincipal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSDialogoAgregarCuerpoENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDialogoAgregarCuerpoENDCLASS = QtMocHelpers::stringData(
    "DialogoAgregarCuerpo",
    "seleccionarColor",
    ""
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDialogoAgregarCuerpoENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject DialogoAgregarCuerpo::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSDialogoAgregarCuerpoENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDialogoAgregarCuerpoENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDialogoAgregarCuerpoENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DialogoAgregarCuerpo, std::true_type>,
        // method 'seleccionarColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DialogoAgregarCuerpo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DialogoAgregarCuerpo *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->seleccionarColor(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *DialogoAgregarCuerpo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogoAgregarCuerpo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDialogoAgregarCuerpoENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogoAgregarCuerpo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSVentanaPrincipalENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSVentanaPrincipalENDCLASS = QtMocHelpers::stringData(
    "VentanaPrincipal",
    "onIniciarPausar",
    "",
    "onReiniciar",
    "onCargarArchivo",
    "onResetearPosicionesOriginales",
    "onAgregarCuerpo",
    "onVerificarConArchivo",
    "onResetearZoom",
    "onCargarSistema1",
    "onCargarSistema2",
    "onCambiarVelocidad",
    "valor",
    "onCambiarZoom",
    "onToggleTrayectorias",
    "mostrar",
    "onToggleEtiquetas",
    "onToggleColisiones",
    "detectar",
    "actualizarVisualizacion",
    "actualizarInformacion",
    "onColisionDetectada",
    "cuerpo1",
    "cuerpo2"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVentanaPrincipalENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x08,    1 /* Private */,
       3,    0,  117,    2, 0x08,    2 /* Private */,
       4,    0,  118,    2, 0x08,    3 /* Private */,
       5,    0,  119,    2, 0x08,    4 /* Private */,
       6,    0,  120,    2, 0x08,    5 /* Private */,
       7,    0,  121,    2, 0x08,    6 /* Private */,
       8,    0,  122,    2, 0x08,    7 /* Private */,
       9,    0,  123,    2, 0x08,    8 /* Private */,
      10,    0,  124,    2, 0x08,    9 /* Private */,
      11,    1,  125,    2, 0x08,   10 /* Private */,
      13,    1,  128,    2, 0x08,   12 /* Private */,
      14,    1,  131,    2, 0x08,   14 /* Private */,
      16,    1,  134,    2, 0x08,   16 /* Private */,
      17,    1,  137,    2, 0x08,   18 /* Private */,
      19,    0,  140,    2, 0x08,   20 /* Private */,
      20,    0,  141,    2, 0x08,   21 /* Private */,
      21,    2,  142,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   23,

       0        // eod
};

Q_CONSTINIT const QMetaObject VentanaPrincipal::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSVentanaPrincipalENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVentanaPrincipalENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVentanaPrincipalENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VentanaPrincipal, std::true_type>,
        // method 'onIniciarPausar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReiniciar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCargarArchivo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetearPosicionesOriginales'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAgregarCuerpo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onVerificarConArchivo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetearZoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCargarSistema1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCargarSistema2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCambiarVelocidad'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onCambiarZoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onToggleTrayectorias'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onToggleEtiquetas'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onToggleColisiones'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'actualizarVisualizacion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actualizarInformacion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onColisionDetectada'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void VentanaPrincipal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VentanaPrincipal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onIniciarPausar(); break;
        case 1: _t->onReiniciar(); break;
        case 2: _t->onCargarArchivo(); break;
        case 3: _t->onResetearPosicionesOriginales(); break;
        case 4: _t->onAgregarCuerpo(); break;
        case 5: _t->onVerificarConArchivo(); break;
        case 6: _t->onResetearZoom(); break;
        case 7: _t->onCargarSistema1(); break;
        case 8: _t->onCargarSistema2(); break;
        case 9: _t->onCambiarVelocidad((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onCambiarZoom((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->onToggleTrayectorias((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->onToggleEtiquetas((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->onToggleColisiones((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->actualizarVisualizacion(); break;
        case 15: _t->actualizarInformacion(); break;
        case 16: _t->onColisionDetectada((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *VentanaPrincipal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VentanaPrincipal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVentanaPrincipalENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VentanaPrincipal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
