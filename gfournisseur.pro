QT       += core gui sql printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    fournisseur.cpp \
    main.cpp \
    gfournisseur.cpp

HEADERS += \
    connection.h \
    fournisseur.h \
    gfournisseur.h

FORMS += \
    gfournisseur.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Additional settings for better performance
win32: {
    QMAKE_CXXFLAGS += -O2
    QMAKE_LFLAGS += -O2
}

unix: {
    QMAKE_CXXFLAGS += -O2
    QMAKE_LFLAGS += -O2
}
