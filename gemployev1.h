#ifndef GEMPLOYEV1_H
#define GEMPLOYEV1_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gemploye;
}
QT_END_NAMESPACE

class Gemploye : public QMainWindow
{
    Q_OBJECT

public:
    Gemploye(QWidget *parent = nullptr);
    ~Gemploye();

private:
    Ui::Gemploye *ui;
};
class Connection
{
public:
    Connection();
    bool createconnect();
};

#endif // GEMPLOYEV1_H
