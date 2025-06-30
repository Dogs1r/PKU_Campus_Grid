/****************************************************************************
** Meta object code from reading C++ file 'fancytoolbar.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../fancytoolbar.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fancytoolbar.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12FancyToolBarE_t {};
} // unnamed namespace

template <> constexpr inline auto FancyToolBar::qt_create_metaobjectdata<qt_meta_tag_ZN12FancyToolBarE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FancyToolBar",
        "requestShowWidget",
        "",
        "QWidget*",
        "widget",
        "requestShowToolBar",
        "widgetShown"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestShowWidget'
        QtMocHelpers::SignalData<void(QWidget *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'requestShowToolBar'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'widgetShown'
        QtMocHelpers::SignalData<void(QWidget *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FancyToolBar, qt_meta_tag_ZN12FancyToolBarE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject FancyToolBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QToolBar::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FancyToolBarE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FancyToolBarE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12FancyToolBarE_t>.metaTypes,
    nullptr
} };

void FancyToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FancyToolBar *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestShowWidget((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 1: _t->requestShowToolBar(); break;
        case 2: _t->widgetShown((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FancyToolBar::*)(QWidget * )>(_a, &FancyToolBar::requestShowWidget, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FancyToolBar::*)()>(_a, &FancyToolBar::requestShowToolBar, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FancyToolBar::*)(QWidget * )>(_a, &FancyToolBar::widgetShown, 2))
            return;
    }
}

const QMetaObject *FancyToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FancyToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FancyToolBarE_t>.strings))
        return static_cast<void*>(this);
    return QToolBar::qt_metacast(_clname);
}

int FancyToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FancyToolBar::requestShowWidget(QWidget * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void FancyToolBar::requestShowToolBar()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FancyToolBar::widgetShown(QWidget * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
