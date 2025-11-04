#include "gordonnance.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Établir la connexion à la BD
    Connection* c = Connection::instance();
    bool test = c->createconnect();

    Gordonnance w;

    if(test) {
        w.show();
        QMessageBox::information(nullptr, "Connexion BD",
                                 "Connexion à la base de données réussie!");
    } else {
        QMessageBox::critical(nullptr, "Erreur Connexion",
                              "Échec de connexion à la base de données!");
        return -1;
    }

    return a.exec();
}
