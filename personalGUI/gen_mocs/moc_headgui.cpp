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
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,   32,   32,   32, 0x05,
      33,   32,   32,   32, 0x05,
      44,   32,   32,   32, 0x05,
      57,   32,   32,   32, 0x05,
      71,   32,   32,   32, 0x05,
      84,   32,   32,   32, 0x05,
      97,   32,   32,   32, 0x05,
     113,  143,   32,   32, 0x05,
     155,  207,   32,   32, 0x05,
     269,  295,   32,   32, 0x05,
     306,  295,   32,   32, 0x05,
     332,  356,   32,   32, 0x05,
     365,  356,   32,   32, 0x05,
     389,   32,   32,   32, 0x05,
     411,   32,   32,   32, 0x05,
     433,   32,   32,   32, 0x05,
     463,   32,   32,   32, 0x05,
     490,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
     515,  567,   32,   32, 0x0a,
     571,   32,   32,   32, 0x08,
     589,   32,   32,   32, 0x08,
     594,   32,   32,   32, 0x08,
     601,   32,   32,   32, 0x08,
     609,   32,   32,   32, 0x08,
     616,   32,   32,   32, 0x08,
     623,   32,   32,   32, 0x08,
     633,   32,   32,   32, 0x08,
     649,  207,   32,   32, 0x08,
     695,  295,   32,   32, 0x08,
     715,  295,   32,   32, 0x08,
     735,  753,   32,   32, 0x08,
     766,  784,   32,   32, 0x08,
     797,  143,   32,   32, 0x08,
     821,   32,   32,   32, 0x08,
     837,   32,   32,   32, 0x08,
     866,   32,   32,   32, 0x08,
     897,   32,   32,   32, 0x08,
     925,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HeadGUI[] = {
    "HeadGUI\0certifyPersonaeSignal()\0\0"
    "upSignal()\0downSignal()\0rightSignal()\0"
    "leftSignal()\0backSignal()\0certifySignal()\0"
    "messageRecivedSignal(QString)\0sendMessage\0"
    "updateBraceletSignal(bool,bool,bool,bool,bool,bool)\0"
    "valueUp,valueDown,valueRight,valueLeft,valueBack,valueCertify\0"
    "updateTempHeadSignal(int)\0recentTemp\0"
    "updateTempFootSignal(int)\0"
    "updateCOHeadSignal(int)\0recentCO\0"
    "updateCOFootSignal(int)\0changingLightSignal()\0"
    "coosingStatusSignal()\0"
    "newDataFromHeadquaterSignal()\0"
    "newDataFromArduinoSignal()\0"
    "newValuesForHeadquater()\0"
    "updateImage(unsigned short*,int,int,unsigned char*)\0"
    ",,,\0certifyPersonae()\0up()\0down()\0"
    "right()\0left()\0back()\0certify()\0"
    "coosingStatus()\0"
    "updateBracelet(bool,bool,bool,bool,bool,bool)\0"
    "updateTempHead(int)\0updateTempFoot(int)\0"
    "updateCOHead(int)\0recentCOHead\0"
    "updateCOFoot(int)\0recentCOFoot\0"
    "messageRecived(QString)\0changingLight()\0"
    "sortingValuesForHeadquater()\0"
    "sortingNewDataFromHeadquater()\0"
    "sortingNewDataFromArduino()\0"
    "readingSensors()\0"
};

void HeadGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HeadGUI *_t = static_cast<HeadGUI *>(_o);
        switch (_id) {
        case 0: _t->certifyPersonaeSignal(); break;
        case 1: _t->upSignal(); break;
        case 2: _t->downSignal(); break;
        case 3: _t->rightSignal(); break;
        case 4: _t->leftSignal(); break;
        case 5: _t->backSignal(); break;
        case 6: _t->certifySignal(); break;
        case 7: _t->messageRecivedSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->updateBraceletSignal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 9: _t->updateTempHeadSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateTempFootSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateCOHeadSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateCOFootSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->changingLightSignal(); break;
        case 14: _t->coosingStatusSignal(); break;
        case 15: _t->newDataFromHeadquaterSignal(); break;
        case 16: _t->newDataFromArduinoSignal(); break;
        case 17: _t->newValuesForHeadquater(); break;
        case 18: _t->updateImage((*reinterpret_cast< unsigned short*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< unsigned char*(*)>(_a[4]))); break;
        case 19: _t->certifyPersonae(); break;
        case 20: _t->up(); break;
        case 21: _t->down(); break;
        case 22: _t->right(); break;
        case 23: _t->left(); break;
        case 24: _t->back(); break;
        case 25: _t->certify(); break;
        case 26: _t->coosingStatus(); break;
        case 27: _t->updateBracelet((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 28: _t->updateTempHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->updateTempFoot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->updateCOHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->updateCOFoot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->messageRecived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->changingLight(); break;
        case 34: _t->sortingValuesForHeadquater(); break;
        case 35: _t->sortingNewDataFromHeadquater(); break;
        case 36: _t->sortingNewDataFromArduino(); break;
        case 37: _t->readingSensors(); break;
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
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void HeadGUI::certifyPersonaeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HeadGUI::upSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HeadGUI::downSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HeadGUI::rightSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HeadGUI::leftSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HeadGUI::backSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HeadGUI::certifySignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void HeadGUI::messageRecivedSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HeadGUI::updateBraceletSignal(bool _t1, bool _t2, bool _t3, bool _t4, bool _t5, bool _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HeadGUI::updateTempHeadSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HeadGUI::updateTempFootSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void HeadGUI::updateCOHeadSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HeadGUI::updateCOFootSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HeadGUI::changingLightSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void HeadGUI::coosingStatusSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void HeadGUI::newDataFromHeadquaterSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void HeadGUI::newDataFromArduinoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}

// SIGNAL 17
void HeadGUI::newValuesForHeadquater()
{
    QMetaObject::activate(this, &staticMetaObject, 17, 0);
}
QT_END_MOC_NAMESPACE
