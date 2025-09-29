#include "gemploye.h"

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

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GEmploye_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    loadStyleSheet(a, "style.qss"); // If file is in application directory
    GEmploye w;
    w.show();
    return a.exec();
}
