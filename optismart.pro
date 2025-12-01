QT       += core gui
QT       +=sql
QT += core gui widgets sql printsupport
QT += charts
QT       += charts sql widgets core gui
QT       += core gui sql widgets charts
QT       += charts
QT       += network
#produit
QT += printsupport
QT += charts
QT       += core gui sql network charts widgets
QT += core gui sql network
QT += widgets charts
QT += multimedia multimediawidgets
QT += core gui widgets multimedia multimediawidgets
QT += multimedia

QT       += quick quickwidgets location positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#produit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatbot.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    main.cpp \
    optismart.cpp \
    ordonnance.cpp \
    performance.cpp \
    planninghoraire.cpp \
    produit.cpp \
    qrcodegen.cpp \
    smtp.cpp


HEADERS += \
    chatbot.h \
    client.h \
    connection.h \
    employe.h \
    fournisseur.h \
    optismart.h \
    ordonnance.h \
    performance.h \
    planninghoraire.h \
    produit.h \
    qrcodegen.hpp \
    smtp.h


FORMS += \
    optismart.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

DISTFILES += \
    ../GEmployev0/logo1.png
