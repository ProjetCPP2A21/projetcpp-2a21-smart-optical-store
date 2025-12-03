QT       += core gui
QT       += sql
QT += core gui widgets sql
config +=console
QT += printsupport
QT += charts
QT       += core gui sql network charts widgets
QT += core gui sql network
QT += widgets charts
QT += multimedia multimediawidgets
QT += core gui widgets multimedia multimediawidgets
QT += multimedia
QT       += core gui sql network multimedia multimediawidgets charts serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RESOURCES +=
SOURCES += \
    arduino_produit.cpp \
    qrcodegen.cpp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17



SOURCES += \
    connection.cpp \
    main.cpp \
    gproduit.cpp \
    produit.cpp
    qrcodegen.cpp

HEADERS += \
    arduino_produit.h \
    connection.h \
    gproduit.h \
    produit.h \
    qrcodegen.hpp

FORMS += \
    gproduit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

DISTFILES +=
