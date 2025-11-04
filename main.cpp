#include <QApplication>
#include "gfournisseur.h"
#include "connection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ✅ Step 1: Connect to DB using Singleton
    if (!Connection::getInstance().createconnect()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection to DS_optismart failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return -1;
    }

    // ✅ Step 2: Show success message
    QMessageBox::information(nullptr, QObject::tr("Database Connected"),
                             QObject::tr("Connection to DS_optismart successful!\nClick OK to continue."),
                             QMessageBox::Ok);

    // ✅ Step 3: Create and show main window AFTER connection
    gfournisseur w;
    w.show();

    return a.exec();
}
