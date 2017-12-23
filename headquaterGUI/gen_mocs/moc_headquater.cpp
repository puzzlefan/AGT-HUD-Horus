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
       7,   35,   40,   40, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Person[] = {
    "Person\0updateImage(unsigned char*)\0"
    "data\0\0"
};

void Person::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Person *_t = static_cast<Person *>(_o);
        switch (_id) {
        case 0: _t->updateImage((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
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
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   41,   53,   53, 0x05,
      54,   83,   53,   53, 0x05,
      99,  130,   53,   53, 0x05,
     144,  130,   53,   53, 0x05,
     175,  204,   53,   53, 0x05,
     216,  204,   53,   53, 0x05,
     245,  275,   53,   53, 0x05,
     285,  324,   53,   53, 0x05,
     328,  347,   53,   53, 0x05,

 // slots: signature, parameters, type, tag, flags
     356,   41,   53,   53, 0x08,
     380,   83,   53,   53, 0x08,
     403,  130,   53,   53, 0x08,
     428,  130,   53,   53, 0x08,
     453,  204,   53,   53, 0x08,
     476,  204,   53,   53, 0x08,
     499,  275,   53,   53, 0x08,
     523,   53,   53,   53, 0x08,
     540,  555,   53,   53, 0x08,
     561,  594,   53,   53, 0x08,
     604,  347,   53,   53, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_headquater[] = {
    "headquater\0newConfirmedIDSignal(int,int)\0"
    "ID,vectorNo\0\0updatedStatusSignal(int,int)\0"
    "ID,recentStatus\0updatedTempHeadSignal(int,int)\0"
    "ID,recentTemp\0updatedTempFootSignal(int,int)\0"
    "updatedCOHeadSignal(int,int)\0ID,recentCO\0"
    "updatedCOFootSignal(int,int)\0"
    "answerdMessageSignal(int,int)\0ID,answer\0"
    "updatedImageSignal(int,unsigned char*)\0"
    "ID,\0newDataSignal(int)\0vectorNo\0"
    "newConfirmedID(int,int)\0updatedStatus(int,int)\0"
    "updatedTempHead(int,int)\0"
    "updatedTempFoot(int,int)\0"
    "updatedCOHead(int,int)\0updatedCOFoot(int,int)\0"
    "answerdMessage(int,int)\0sendNewMessage()\0"
    "newTopTab(int)\0index\0"
    "updatedImage(int,unsigned char*)\0"
    "ID,result\0sortingData(int)\0"
};

void headquater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        headquater *_t = static_cast<headquater *>(_o);
        switch (_id) {
        case 0: _t->newConfirmedIDSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->updatedStatusSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->updatedTempHeadSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->updatedTempFootSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->updatedCOHeadSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->updatedCOFootSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->answerdMessageSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->updatedImageSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2]))); break;
        case 8: _t->newDataSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->newConfirmedID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->updatedStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->updatedTempHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->updatedTempFoot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->updatedCOHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->updatedCOFoot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->answerdMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->sendNewMessage(); break;
        case 17: _t->newTopTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->updatedImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2]))); break;
        case 19: _t->sortingData((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void headquater::newConfirmedIDSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void headquater::updatedStatusSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void headquater::updatedTempHeadSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void headquater::updatedTempFootSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void headquater::updatedCOHeadSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void headquater::updatedCOFootSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void headquater::answerdMessageSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void headquater::updatedImageSignal(int _t1, unsigned char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void headquater::newDataSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
