#include "connection.h"
#include <QSqlDatabase>

// Initialisation du pointeur statique à nullptr
Connection* Connection::p_instance = nullptr;

// Constructeur privé
Connection::Connection()
{
    // Initialisation si nécessaire
}

// Méthode statique pour obtenir l’instance unique
Connection* Connection::instance()
{
    if (p_instance == nullptr)
        p_instance = new Connection();
    return p_instance;
}

// Méthode pour établir la connexion à la base de données
bool Connection::createConnect()
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

// Destructeur privé pour fermer la connexion
Connection::~Connection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
        db.close();
}
