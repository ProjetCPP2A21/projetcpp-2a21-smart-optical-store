#include "arduino_produit.h"
#include <QDebug>

arduino_produit::arduino_produit(QObject *parent) : QObject(parent) {
    ouvrirPort();
}

arduino_produit::~arduino_produit() {
    if (serial.isOpen()) serial.close();
}

void arduino_produit::ouvrirPort() {
    // Remplace "COM3" par le port de ton Arduino
    serial.setPortName("COM12");       // changer COM3 → COM12
    serial.setBaudRate(QSerialPort::Baud115200);

    if (!serial.open(QIODevice::ReadOnly)) {
        qDebug() << "Impossible d'ouvrir le port Arduino";
        return;
    }

    connect(&serial, &QSerialPort::readyRead, this, &arduino_produit::lireCarte);
    qDebug() << "Port Arduino ouvert avec succès";
}

void arduino_produit::lireCarte() {
    while (serial.canReadLine()) {
        QString id = QString::fromUtf8(serial.readLine()).trimmed();
        emit carteDetectee(id);
    }
}
