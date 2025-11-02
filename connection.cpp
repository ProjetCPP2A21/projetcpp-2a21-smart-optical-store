#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DS_optismart"); // Nom de la source de données ODBC
    db.setUserName("optismart");              // Nom d'utilisateur
    db.setPassword("0000");             // Mot de passe

    if (db.open())
        test = true;

    return test;
}
