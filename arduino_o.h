#ifndef ARDUINO_O_H
#define ARDUINO_O_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QString>
#include <QDebug>

class Arduino_o
{
public:
    Arduino_o();
    ~Arduino_o();

    int connect_arduino();  // connecter le PC à Arduino
    int close_arduino();    // fermer la connexion
    void write_to_arduino(const QByteArray &d); // envoyer des données
    QByteArray read_from_arduino(); // recevoir des données
    QSerialPort* getserial();
    QString getarduino_port_name();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_O_H
