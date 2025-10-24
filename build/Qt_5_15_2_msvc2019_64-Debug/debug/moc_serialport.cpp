/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Serialport/serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialPort_t {
    QByteArrayData data[30];
    char stringdata0[390];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPort_t qt_meta_stringdata_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialPort"
QT_MOC_LITERAL(1, 11, 18), // "coordinatesUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 1), // "x"
QT_MOC_LITERAL(4, 33, 1), // "y"
QT_MOC_LITERAL(5, 35, 1), // "z"
QT_MOC_LITERAL(6, 37, 3), // "yaw"
QT_MOC_LITERAL(7, 41, 13), // "rosMapUpdated"
QT_MOC_LITERAL(8, 55, 13), // "OccupancyGrid"
QT_MOC_LITERAL(9, 69, 3), // "map"
QT_MOC_LITERAL(10, 73, 14), // "rosScanUpdated"
QT_MOC_LITERAL(11, 88, 9), // "LaserScan"
QT_MOC_LITERAL(12, 98, 4), // "scan"
QT_MOC_LITERAL(13, 103, 12), // "rosTfUpdated"
QT_MOC_LITERAL(14, 116, 9), // "TFMessage"
QT_MOC_LITERAL(15, 126, 2), // "tf"
QT_MOC_LITERAL(16, 129, 23), // "on_portSearchBt_clicked"
QT_MOC_LITERAL(17, 153, 21), // "on_portOpenBt_clicked"
QT_MOC_LITERAL(18, 175, 26), // "manual_serialPortReadyRead"
QT_MOC_LITERAL(19, 202, 22), // "on_clearRecvBt_clicked"
QT_MOC_LITERAL(20, 225, 17), // "on_sendBt_clicked"
QT_MOC_LITERAL(21, 243, 23), // "on_btnClearSend_clicked"
QT_MOC_LITERAL(22, 267, 12), // "tcpReadyRead"
QT_MOC_LITERAL(23, 280, 16), // "tcpErrorOccurred"
QT_MOC_LITERAL(24, 297, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(25, 326, 5), // "error"
QT_MOC_LITERAL(26, 332, 12), // "udpReadyRead"
QT_MOC_LITERAL(27, 345, 24), // "on_wifiConnectBt_clicked"
QT_MOC_LITERAL(28, 370, 12), // "parseRosData"
QT_MOC_LITERAL(29, 383, 6) // "recBuf"

    },
    "SerialPort\0coordinatesUpdated\0\0x\0y\0z\0"
    "yaw\0rosMapUpdated\0OccupancyGrid\0map\0"
    "rosScanUpdated\0LaserScan\0scan\0"
    "rosTfUpdated\0TFMessage\0tf\0"
    "on_portSearchBt_clicked\0on_portOpenBt_clicked\0"
    "manual_serialPortReadyRead\0"
    "on_clearRecvBt_clicked\0on_sendBt_clicked\0"
    "on_btnClearSend_clicked\0tcpReadyRead\0"
    "tcpErrorOccurred\0QAbstractSocket::SocketError\0"
    "error\0udpReadyRead\0on_wifiConnectBt_clicked\0"
    "parseRosData\0recBuf"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   89,    2, 0x06 /* Public */,
       7,    1,   98,    2, 0x06 /* Public */,
      10,    1,  101,    2, 0x06 /* Public */,
      13,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  107,    2, 0x08 /* Private */,
      17,    0,  108,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,
      19,    0,  110,    2, 0x08 /* Private */,
      20,    0,  111,    2, 0x08 /* Private */,
      21,    0,  112,    2, 0x08 /* Private */,
      22,    0,  113,    2, 0x08 /* Private */,
      23,    1,  114,    2, 0x08 /* Private */,
      26,    0,  117,    2, 0x08 /* Private */,
      27,    0,  118,    2, 0x08 /* Private */,
      28,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short, QMetaType::Short, QMetaType::Short, QMetaType::Short,    3,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   29,

       0        // eod
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->coordinatesUpdated((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3])),(*reinterpret_cast< qint16(*)>(_a[4]))); break;
        case 1: _t->rosMapUpdated((*reinterpret_cast< const OccupancyGrid(*)>(_a[1]))); break;
        case 2: _t->rosScanUpdated((*reinterpret_cast< const LaserScan(*)>(_a[1]))); break;
        case 3: _t->rosTfUpdated((*reinterpret_cast< const TFMessage(*)>(_a[1]))); break;
        case 4: _t->on_portSearchBt_clicked(); break;
        case 5: _t->on_portOpenBt_clicked(); break;
        case 6: _t->manual_serialPortReadyRead(); break;
        case 7: _t->on_clearRecvBt_clicked(); break;
        case 8: _t->on_sendBt_clicked(); break;
        case 9: _t->on_btnClearSend_clicked(); break;
        case 10: _t->tcpReadyRead(); break;
        case 11: _t->tcpErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->udpReadyRead(); break;
        case 13: _t->on_wifiConnectBt_clicked(); break;
        case 14: _t->parseRosData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialPort::*)(qint16 , qint16 , qint16 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::coordinatesUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialPort::*)(const OccupancyGrid & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::rosMapUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SerialPort::*)(const LaserScan & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::rosScanUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SerialPort::*)(const TFMessage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::rosTfUpdated)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialPort::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SerialPort.data,
    qt_meta_data_SerialPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SerialPort::coordinatesUpdated(qint16 _t1, qint16 _t2, qint16 _t3, qint16 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialPort::rosMapUpdated(const OccupancyGrid & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SerialPort::rosScanUpdated(const LaserScan & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SerialPort::rosTfUpdated(const TFMessage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
