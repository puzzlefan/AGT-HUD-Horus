/****************************************************************************
** Meta object code from reading C++ file 'headquater.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headquater.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headquater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Person[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,   44,   47,   47, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Person[] = {
    "Person\0updateImage(unsigned short*,int,int)\0"
    ",,\0\0"
};

void Person::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Person *_t = static_cast<Person *>(_o);
        switch (_id) {
        case 0: _t->updateImage((*reinterpret_cast< unsigned short*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Person::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Person::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Person,
      qt_meta_data_Person, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Person::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Person::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Person::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Person))
        return static_cast<void*>(const_cast< Person*>(this));
    return QWidget::qt_metacast(_clname);
}

int Person::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_headquater[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   35,   46,   46, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   67,   46,   46, 0x08,
      70,   93,   46,   46, 0x08,
     109,  134,   46,   46, 0x08,
     148,  134,   46,   46, 0x08,
     173,  196,   46,   46, 0x08,
     208,  196,   46,   46, 0x08,
     231,  255,   46,   46, 0x08,
     265,   46,   46,   46, 0x08,
     282,  297,   46,   46, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_headquater[] = {
    "headquater\0newMessage(int,QString)\0"
    "ID,Message\0\0newConfirmedID(int)\0ID\0"
    "updatedStatus(int,int)\0ID,recentStatus\0"
    "updatedTempHead(int,int)\0ID,recentTemp\0"
    "updatedTempFoot(int,int)\0"
    "updatedCOHead(int,int)\0ID,recentCO\0"
    "updatedCOFoot(int,int)\0answerdMessage(int,int)\0"
    "ID,answer\0sendNewMessage()\0newTopTab(int)\0"
    "index\0"
};

void headquater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        headquater *_t = static_cast<headquater *>(_o);
        switch (_id) {
        case 0: _t->newMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->newConfirmedID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updatedStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->updatedTempHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->updatedTempFoot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->updatedCOHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->updatedCOFoot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->answerdMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->sendNewMessage(); break;
        case 9: _t->newTopTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData headquater::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject headquater::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_headquater,
      qt_meta_data_headquater, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &headquater::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *headquater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *headquater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_headquater))
        return static_cast<void*>(const_cast< headquater*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int headquater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void headquater::newMessage(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
