/****************************************************************************
** Meta object code from reading C++ file 'bg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Bg_t {
    QByteArrayData data[16];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bg_t qt_meta_stringdata_Bg = {
    {
QT_MOC_LITERAL(0, 0, 2), // "Bg"
QT_MOC_LITERAL(1, 3, 7), // "message"
QT_MOC_LITERAL(2, 11, 0), // ""
QT_MOC_LITERAL(3, 12, 23), // "QVector<iproc::message>"
QT_MOC_LITERAL(4, 36, 4), // "msgs"
QT_MOC_LITERAL(5, 41, 5), // "steps"
QT_MOC_LITERAL(6, 47, 4), // "step"
QT_MOC_LITERAL(7, 52, 7), // "stopped"
QT_MOC_LITERAL(8, 60, 11), // "calculating"
QT_MOC_LITERAL(9, 72, 6), // "onStop"
QT_MOC_LITERAL(10, 79, 7), // "onStart"
QT_MOC_LITERAL(11, 87, 7), // "qtitles"
QT_MOC_LITERAL(12, 95, 12), // "isSaveToFile"
QT_MOC_LITERAL(13, 108, 8), // "interval"
QT_MOC_LITERAL(14, 117, 8), // "duration"
QT_MOC_LITERAL(15, 126, 9) // "calculate"

    },
    "Bg\0message\0\0QVector<iproc::message>\0"
    "msgs\0steps\0step\0stopped\0calculating\0"
    "onStop\0onStart\0qtitles\0isSaveToFile\0"
    "interval\0duration\0calculate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       7,    0,   61,    2, 0x06 /* Public */,
       8,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   63,    2, 0x0a /* Public */,
      10,    4,   64,    2, 0x0a /* Public */,
      10,    3,   73,    2, 0x2a /* Public | MethodCloned */,
      10,    2,   80,    2, 0x2a /* Public | MethodCloned */,
      15,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Bool, QMetaType::Int, QMetaType::Int,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Bool, QMetaType::Int,   11,   12,   13,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Bool,   11,   12,
    QMetaType::Void,

       0        // eod
};

void Bg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Bg *_t = static_cast<Bg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->message((*reinterpret_cast< QVector<iproc::message>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->stopped(); break;
        case 2: _t->calculating(); break;
        case 3: _t->onStop(); break;
        case 4: _t->onStart((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->onStart((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->onStart((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->calculate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Bg::*_t)(QVector<iproc::message> , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bg::message)) {
                *result = 0;
            }
        }
        {
            typedef void (Bg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bg::stopped)) {
                *result = 1;
            }
        }
        {
            typedef void (Bg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bg::calculating)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Bg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Bg.data,
      qt_meta_data_Bg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Bg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Bg.stringdata0))
        return static_cast<void*>(const_cast< Bg*>(this));
    return QObject::qt_metacast(_clname);
}

int Bg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Bg::message(QVector<iproc::message> _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Bg::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Bg::calculating()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
