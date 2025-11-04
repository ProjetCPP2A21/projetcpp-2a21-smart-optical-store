#include "connection.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

// Define the static member
Connection* Connection::instance = nullptr;

// Private constructor: configure DB here
Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("DS_optismart");
    db.setUserName("optismart");
    db.setPassword("0000");
}

// Singleton access method
Connection& Connection::getInstance()
{
    if (!instance) {
        instance = new Connection();
    }
    return *instance;
}

// Open the connection
bool Connection::createconnect()
{
    qDebug() << "=== QT CONNECTION ATTEMPT ===";
    qDebug() << "Trying to connect to:";
    qDebug() << "Host:" << db.hostName();
    qDebug() << "Database:" << db.databaseName();
    qDebug() << "Username:" << db.userName();

    if (db.open()) {
        qDebug() << "✅ CONNECTION SUCCESSFUL to DS_optismart!";

        // Get actual connection details from database
        QSqlQuery query;
        if (query.exec("SELECT SYS_CONTEXT('USERENV', 'SESSION_USER'), SYS_CONTEXT('USERENV', 'DB_NAME') FROM DUAL")) {
            if (query.next()) {
                qDebug() << "Connected as user:" << query.value(0).toString();
                qDebug() << "Connected to database:" << query.value(1).toString();
            }
        }
        return true;
    } else {
        qDebug() << "❌ CONNECTION FAILED:" << db.lastError().text();
        return false;
    }
}

// Optional: close connection
void Connection::close()
{
    if (db.isOpen()) {
        db.close();
    }
}
