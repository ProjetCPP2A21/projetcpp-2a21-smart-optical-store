QT       += core gui
QT       += sql
QT += core gui widgets sql
config +=console
QT += printsupport
QT += charts




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    main.cpp \
    gproduit.cpp \
    produit.cpp

HEADERS += \
    connection.h \
    gproduit.h \
    produit.h

FORMS += \
    gproduit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

DISTFILES += \
    back.png \
    logo.png
