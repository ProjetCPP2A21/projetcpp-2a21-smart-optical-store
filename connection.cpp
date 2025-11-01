#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DS_optismart");//inserer le nom de la source de données
    db.setUserName("optismart");//inserer nom de l'utilisateur
    db.setPassword("0000");//inserer mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
        qDebug() << "Connexion à la base de données réussie avec le pilote :" << db.driverName();
    } else {
        qDebug() << "Échec de la connexion à la base de données :" << db.lastError().text();
        test = false;
    }

    return test;
}
