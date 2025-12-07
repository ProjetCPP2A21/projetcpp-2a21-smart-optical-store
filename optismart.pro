QT += core gui widgets
QT += sql
QT += printsupport
QT += charts
QT += network
QT += serialport
QT += multimedia multimediawidgets
QT += quick quickwidgets    # indispensable pour QQuickWidget (carte QML)
# QT += location positioning   # seulement si tu utilises vraiment la géoloc (sinon inutile)
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    arduino_o.cpp \
    arduinof.cpp \
    main.cpp \
    optismart.cpp \
    client.cpp \
    produit.cpp \
    fournisseur.cpp \
    ordonnance.cpp \
    employe.cpp \
    chatbot.cpp \
    arduino_client.cpp \
    arduino_produit.cpp \
    connection.cpp \
    smtp.cpp \
    qrcodegen.cpp \
    performance.cpp \
    planninghoraire.cpp

HEADERS += \
    arduino_o.h \
    arduinof.h \
    optismart.h \
    client.h \
    produit.h \
    fournisseur.h \
    ordonnance.h \
    employe.h \
    chatbot.h \
    arduino_client.h \
    arduino_produit.h \
    connection.h \
    smtp.h \
    qrcodegen.hpp \
    performance.h \
    planninghoraire.h

FORMS += \
    optismart.ui

RESOURCES += \
    ressources.qrc

# Optionnel : désactiver les warnings dépréciés si tu veux un build propre
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
