#include "gproduit.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();

    gproduit w;  // Crée la fenêtre MAIS PAS ENCORE show()

    if (test)
    {

        w.refreshTable();
        w.show();

        QMessageBox::information(nullptr, QObject::tr("Base de données"),
                                 QObject::tr("Connexion réussie !\nLes données sont chargées."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                              QObject::tr("Échec de la connexion à la base !\nVérifiez le fichier .db"),
                              QMessageBox::Ok);
        return -1;  // Quitte si pas de base
    }

    return a.exec();
}
