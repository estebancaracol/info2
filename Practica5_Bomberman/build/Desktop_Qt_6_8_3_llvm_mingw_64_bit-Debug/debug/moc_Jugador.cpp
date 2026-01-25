/****************************************************************************
** Meta object code from reading C++ file 'Jugador.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Jugador.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Jugador.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN7JugadorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7JugadorE = QtMocHelpers::stringData(
    "Jugador",
    "enemigoDestruido",
    "",
    "ladrilloDestruido",
    "jugadorMurio",
    "bombaColocada",
    "alBombaExplotada",
    "Bomba*",
    "bomba",
    "alEnemigoDestruido",
    "alLadrilloDestruido",
    "actualizarMovimiento",
    "finalizarInmunidad"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7JugadorE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,
       3,    0,   69,    2, 0x06,    2 /* Public */,
       4,    0,   70,    2, 0x06,    3 /* Public */,
       5,    0,   71,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   72,    2, 0x0a,    5 /* Public */,
       9,    0,   75,    2, 0x0a,    7 /* Public */,
      10,    0,   76,    2, 0x0a,    8 /* Public */,
      11,    0,   77,    2, 0x0a,    9 /* Public */,
      12,    0,   78,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Jugador::staticMetaObject = { {
    QMetaObject::SuperData::link<Entidad::staticMetaObject>(),
    qt_meta_stringdata_ZN7JugadorE.offsetsAndSizes,
    qt_meta_data_ZN7JugadorE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7JugadorE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Jugador, std::true_type>,
        // method 'enemigoDestruido'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ladrilloDestruido'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'jugadorMurio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'bombaColocada'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'alBombaExplotada'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Bomba *, std::false_type>,
        // method 'alEnemigoDestruido'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'alLadrilloDestruido'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actualizarMovimiento'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'finalizarInmunidad'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Jugador::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Jugador *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->enemigoDestruido(); break;
        case 1: _t->ladrilloDestruido(); break;
        case 2: _t->jugadorMurio(); break;
        case 3: _t->bombaColocada(); break;
        case 4: _t->alBombaExplotada((*reinterpret_cast< std::add_pointer_t<Bomba*>>(_a[1]))); break;
        case 5: _t->alEnemigoDestruido(); break;
        case 6: _t->alLadrilloDestruido(); break;
        case 7: _t->actualizarMovimiento(); break;
        case 8: _t->finalizarInmunidad(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Bomba* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (Jugador::*)();
            if (_q_method_type _q_method = &Jugador::enemigoDestruido; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (Jugador::*)();
            if (_q_method_type _q_method = &Jugador::ladrilloDestruido; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (Jugador::*)();
            if (_q_method_type _q_method = &Jugador::jugadorMurio; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (Jugador::*)();
            if (_q_method_type _q_method = &Jugador::bombaColocada; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Jugador::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Jugador::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7JugadorE.stringdata0))
        return static_cast<void*>(this);
    return Entidad::qt_metacast(_clname);
}

int Jugador::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entidad::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Jugador::enemigoDestruido()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Jugador::ladrilloDestruido()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Jugador::jugadorMurio()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Jugador::bombaColocada()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
