QT       += core gui
QT       +=sql
QT       += core gui sql widgets printsupport
QT       += charts sql widgets core gui
QT       += core gui sql widgets charts
QT       += charts
QT       += network
//arduino
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Gclient.cpp \
    arduino_client.cpp \
    client.cpp \
    connection.cpp \
    main.cpp \
    smtp.cpp

HEADERS += \
    Gclient.h \
    arduino_client.h \
    client.h \
    connection.h \
    smtp.h

FORMS += \
    Gclient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc
