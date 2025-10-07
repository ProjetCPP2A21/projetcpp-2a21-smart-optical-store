#include "gemployev1.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include <QFile>
#include <QApplication>



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
    Gemploye w;
    w.show();
    return a.exec();
}
