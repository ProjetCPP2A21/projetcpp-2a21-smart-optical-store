#ifndef ARDUINO_PRODUIT_H
#define ARDUINO_PRODUIT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class arduino_produit : public QObject {
    Q_OBJECT
public:
    explicit arduino_produit(QObject *parent = nullptr);
    ~arduino_produit();

signals:
    void carteDetectee(const QString &id);

private slots:
    void lireCarte();

private:
    QSerialPort serial;
    void ouvrirPort();
};

#endif // ARDUINO_PRODUIT_H

