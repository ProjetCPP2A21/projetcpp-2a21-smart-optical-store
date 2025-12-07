#include "arduinof.h"

ArduinoF::ArduinoF()
{
    serial = new QSerialPort();
    arduino_is_available = false;
    arduino_port_name = "";
}

QString ArduinoF::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *ArduinoF::getserial()
{
    return serial;
}

int ArduinoF::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id){
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "ArduinoF trouvé sur le port :" << arduino_port_name;
            }
        }
    }

    if(arduino_is_available){
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}

int ArduinoF::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray ArduinoF::read_from_arduino()
{
    if(serial->isReadable()){
        return serial->readAll();
    }
    return QByteArray();
}

int ArduinoF::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
        return 0;
    }
    qDebug() << "Erreur ArduinoF: Impossible d'écrire sur le port série !";
    return 1;
}
