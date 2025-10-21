#include "connection.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

Connection::Connection()
{

}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("raef");
    db.setPassword("raef123");

    if (db.open()) {
        qDebug() << " Connexion réussie à Oracle Database!";
        return true;
    } else {
        qDebug() << " Erreur de connexion:" << db.lastError().text();
        return false;
    }
}

