#ifndef ARDUINOF_H
#define ARDUINOF_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class ArduinoF
{
public:
    ArduinoF();

    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray d);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_port_name();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // ARDUINOF_H
