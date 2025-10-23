QT       += core gui
QT       +=sql
QT += core gui widgets sql printsupport
QT += charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authentification.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    main.cpp \
    optismart.cpp \
    ordonnance.cpp \
    produit.cpp

HEADERS += \
    authentification.h \
    client.h \
    connection.h \
    employe.h \
    fournisseur.h \
    optismart.h \
    ordonnance.h \
    produit.h

FORMS += \
    optismart.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resoures.qrc

DISTFILES += \
    ../GEmployev0/logo1.png
