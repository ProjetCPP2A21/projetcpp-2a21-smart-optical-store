#include "gordonnance.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click OK to continue."));
        Gordonnance w;
        w.show();
        return a.exec();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed.\n"
                                          "Please check your settings."));
        return 1;
    }
}
