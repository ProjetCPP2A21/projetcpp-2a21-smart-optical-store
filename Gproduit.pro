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
QT += multimedia        # ← TRÈS IMPORTANT ! Ajoute cette ligne
RESOURCES +=
SOURCES += \
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
