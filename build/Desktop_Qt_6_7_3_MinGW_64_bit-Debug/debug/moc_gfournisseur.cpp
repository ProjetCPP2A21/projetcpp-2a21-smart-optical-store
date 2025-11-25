/****************************************************************************
** Meta object code from reading C++ file 'gfournisseur.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../gfournisseur.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gfournisseur.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSgfournisseurENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSgfournisseurENDCLASS = QtMocHelpers::stringData(
    "gfournisseur",
    "on_bajouter_f_clicked",
    "",
    "on_bsupprimer_f_clicked",
    "on_bmodifier_f_clicked",
    "on_nom_le_textChanged",
    "text",
    "on_email_le_textChanged",
    "on_telephone_le_textChanged",
    "on_bstatistique_f_clicked",
    "on_bexporter_f_clicked",
    "on_btrier_f_clicked",
    "on_brechercher_f_clicked",
    "on_bnouveau_f_clicked",
    "on_tableWidget_4_itemClicked",
    "QTableWidgetItem*",
    "item"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgfournisseurENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    1,   89,    2, 0x08,    4 /* Private */,
       7,    1,   92,    2, 0x08,    6 /* Private */,
       8,    1,   95,    2, 0x08,    8 /* Private */,
       9,    0,   98,    2, 0x08,   10 /* Private */,
      10,    0,   99,    2, 0x08,   11 /* Private */,
      11,    0,  100,    2, 0x08,   12 /* Private */,
      12,    0,  101,    2, 0x08,   13 /* Private */,
      13,    0,  102,    2, 0x08,   14 /* Private */,
      14,    1,  103,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject gfournisseur::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSgfournisseurENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgfournisseurENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgfournisseurENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gfournisseur, std::true_type>,
        // method 'on_bajouter_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bsupprimer_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bmodifier_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_nom_le_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_email_le_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_telephone_le_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_bstatistique_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bexporter_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btrier_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_brechercher_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bnouveau_f_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_4_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>
    >,
    nullptr
} };

void gfournisseur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gfournisseur *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_bajouter_f_clicked(); break;
        case 1: _t->on_bsupprimer_f_clicked(); break;
        case 2: _t->on_bmodifier_f_clicked(); break;
        case 3: _t->on_nom_le_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->on_email_le_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_telephone_le_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_bstatistique_f_clicked(); break;
        case 7: _t->on_bexporter_f_clicked(); break;
        case 8: _t->on_btrier_f_clicked(); break;
        case 9: _t->on_brechercher_f_clicked(); break;
        case 10: _t->on_bnouveau_f_clicked(); break;
        case 11: _t->on_tableWidget_4_itemClicked((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *gfournisseur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gfournisseur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgfournisseurENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int gfournisseur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
