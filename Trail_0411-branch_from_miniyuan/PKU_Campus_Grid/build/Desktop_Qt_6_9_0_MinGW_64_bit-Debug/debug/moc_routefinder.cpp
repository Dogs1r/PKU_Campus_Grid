/****************************************************************************
** Meta object code from reading C++ file 'routefinder.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../routefinder.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'routefinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN11RouteFinderE_t {};
} // unnamed namespace

template <> constexpr inline auto RouteFinder::qt_create_metaobjectdata<qt_meta_tag_ZN11RouteFinderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RouteFinder",
        "startStationChanged",
        "",
        "X",
        "Y",
        "endStationChanged",
        "pathFound",
        "QList<int>",
        "path",
        "requestReturn",
        "setStartStation",
        "setEndStation",
        "triggerFindPath"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'startStationChanged'
        QtMocHelpers::SignalData<void(double, double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 }, { QMetaType::Double, 4 },
        }}),
        // Signal 'endStationChanged'
        QtMocHelpers::SignalData<void(double, double)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 }, { QMetaType::Double, 4 },
        }}),
        // Signal 'pathFound'
        QtMocHelpers::SignalData<void(const QVector<int> &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Signal 'requestReturn'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setStartStation'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setEndStation'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'triggerFindPath'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RouteFinder, qt_meta_tag_ZN11RouteFinderE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RouteFinder::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11RouteFinderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11RouteFinderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11RouteFinderE_t>.metaTypes,
    nullptr
} };

void RouteFinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RouteFinder *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->startStationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 1: _t->endStationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 2: _t->pathFound((*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[1]))); break;
        case 3: _t->requestReturn(); break;
        case 4: _t->setStartStation(); break;
        case 5: _t->setEndStation(); break;
        case 6: _t->triggerFindPath(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RouteFinder::*)(double , double )>(_a, &RouteFinder::startStationChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RouteFinder::*)(double , double )>(_a, &RouteFinder::endStationChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RouteFinder::*)(const QVector<int> & )>(_a, &RouteFinder::pathFound, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (RouteFinder::*)()>(_a, &RouteFinder::requestReturn, 3))
            return;
    }
}

const QMetaObject *RouteFinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RouteFinder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11RouteFinderE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RouteFinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void RouteFinder::startStationChanged(double _t1, double _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void RouteFinder::endStationChanged(double _t1, double _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void RouteFinder::pathFound(const QVector<int> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void RouteFinder::requestReturn()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
