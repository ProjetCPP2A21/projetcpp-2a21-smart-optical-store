#include "optismart.h"
#include "connection.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include <QFile>
#include <QApplication>
#include <QMessageBox>


void loadStyleSheet(QApplication& app, const QString& filename) {
    QFile styleFile(filename);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        qDebug() << "Could not open style file:" << filename;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    optismart w;
    w.show();
    Connection* c= Connection::instance();

    bool test=c->createConnect();
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
