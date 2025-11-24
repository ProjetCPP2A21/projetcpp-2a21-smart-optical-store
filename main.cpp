#include "Gclient.h"

#include "connection.h"
#include <QMessageBox>
#include <QApplication>
//email
#include <QCoreApplication>
#include <QDebug>
#include <client.h>
#include "smtp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gclient w;
    w.show();
    Connection c;
    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    // Envoyer les emails d'anniversaire
    client cl;
    cl.envoyerEmailAnniversaire();

    return a.exec();
}

