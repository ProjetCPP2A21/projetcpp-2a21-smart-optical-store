#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection
{
private:
    Connection(); // Private constructor
    static Connection* instance;
    QSqlDatabase db; // Persistent database connection

public:
    static Connection& getInstance();
    bool createconnect();
    void close();

    // Prevent copies
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};

#endif // CONNECTION_H
