#include "connection.h"

Connection* Connection::p_instance = nullptr;

Connection::Connection()
{

}

Connection* Connection::instance()
{
    if (p_instance == nullptr) {
        p_instance = new Connection();
    }
    return p_instance;
}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DS_optismart");
    db.setUserName("optismart");
    db.setPassword("0000");

    if (db.open())
        test=true;

    return test;
}

Connection::~Connection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
    }
}
