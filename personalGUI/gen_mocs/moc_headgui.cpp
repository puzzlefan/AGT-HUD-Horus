/****************************************************************************
** Meta object code from reading C++ file 'headgui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HeadGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,   30,   30,   30, 0x05,
      31,   30,   30,   30, 0x05,
      55,   30,   30,   30, 0x05,
      66,   30,   30,   30, 0x05,
      79,   30,   30,   30, 0x05,
      93,   30,   30,   30, 0x05,
     106,   30,   30,   30, 0x05,
     119,   30,   30,   30, 0x05,
     135,   30,   30,   30, 0x05,
     157,   30,   30,   30, 0x05,
     182,  228,   30,   30, 0x05,
     290,  316,   30,   30, 0x05,
     327,  316,   30,   30, 0x05,
     353,  377,   30,   30, 0x05,
     386,  377,   30,   30, 0x05,
     410,  440,   30,   30, 0x05,

 // slots: signature, parameters, type, tag, flags
     452,  489,   30,   30, 0x0a,
     492,   30,   30,   30, 0x08,
     510,   30,   30,   30, 0x08,
     515,   30,   30,   30, 0x08,
     522,   30,   30,   30, 0x08,
     530,   30,   30,   30, 0x08,
     537,   30,   30,   30, 0x08,
     544,   30,   30,   30, 0x08,
     554,  228,   30,   30, 0x08,
     594,  316,   30,   30, 0x08,
     614,  316,   30,   30, 0x08,
     634,  652,   30,   30, 0x08,
     665,  683,   30,   30, 0x08,
     696,   30,   30,   30, 0x08,
     712,  440,   30,   30, 0x08,
     736,   30,   30,   30, 0x08,
     752,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HeadGUI[] = {
    "HeadGUI\0changingLightSignal()\0\0"
    "certifyPersonaeSignal()\0upSignal()\0"
    "downSignal()\0rightSignal()\0leftSignal()\0"
    "backSignal()\0certifySignal()\0"
    "coosingStatusSignal()\0newValuesForHeadquater()\0"
    "updateBraceletSignal(int,int,int,int,int,int)\0"
    "valueUp,valueDown,valueRight,valueLeft,valueBack,valueCertify\0"
    "updateTempHeadSignal(int)\0recentTemp\0"
    "updateTempFootSignal(int)\0"
    "updateCOHeadSignal(int)\0recentCO\0"
    "updateCOFootSignal(int)\0"
    "messageRecivedSignal(QString)\0sendMessage\0"
    "updateImage(unsigned short*,int,int)\0"
    ",,\0certifyPersonae()\0up()\0down()\0"
    "right()\0left()\0back()\0certify()\0"
    "updateBracelet(int,int,int,int,int,int)\0"
    "updateTempHead(int)\0updateTempFoot(int)\0"
    "updateCOHead(int)\0recentCOHead\0"
    "updateCOFoot(int)\0recentCOFoot\0"
    "coosingStatus()\0messageRecived(QString)\0"
    "changingLight()\0sortingValuesForHeadquater()\0"
};

void HeadGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HeadGUI *_t = static_cast<HeadGUI *>(_o);
        switch (_id) {
        case 0: _t->changingLightSignal(); break;
        case 1: _t->certifyPersonaeSignal(); break;
        case 2: _t->upSignal(); break;
        case 3: _t->downSignal(); break;
        case 4: _t->rightSignal(); break;
        case 5: _t->leftSignal(); break;
        case 6: _t->backSignal(); break;
        case 7: _t->certifySignal(); break;
        case 8: _t->coosingStatusSignal(); break;
        case 9: _t->newValuesForHeadquater(); break;
        case 10: _t->updateBraceletSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 11: _t->updateTempHeadSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateTempFootSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateCOHeadSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->updateCOFootSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->messageRecivedSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->updateImage((*reinterpret_cast< unsigned short*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->certifyPersonae(); break;
        case 18: _t->up(); break;
        case 19: _t->down(); break;
        case 20: _t->right(); break;
        case 21: _t->left(); break;
        case 22: _t->back(); break;
        case 23: _t->certify(); break;
        case 24: _t->updateBracelet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 25: _t->updateTempHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->updateTempFoot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->updateCOHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->updateCOFoot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->coosingStatus(); break;
        case 30: _t->messageRecived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->changingLight(); break;
        case 32: _t->sortingValuesForHeadquater(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HeadGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HeadGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HeadGUI,
      qt_meta_data_HeadGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HeadGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HeadGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HeadGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeadGUI))
        return static_cast<void*>(const_cast< HeadGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HeadGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void HeadGUI::changingLightSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HeadGUI::certifyPersonaeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HeadGUI::upSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HeadGUI::downSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HeadGUI::rightSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HeadGUI::leftSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HeadGUI::backSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void HeadGUI::certifySignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void HeadGUI::coosingStatusSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void HeadGUI::newValuesForHeadquater()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void HeadGUI::updateBraceletSignal(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void HeadGUI::updateTempHeadSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HeadGUI::updateTempFootSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HeadGUI::updateCOHeadSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void HeadGUI::updateCOFootSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void HeadGUI::messageRecivedSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_END_MOC_NAMESPACE
