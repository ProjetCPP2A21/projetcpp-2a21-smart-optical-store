#ifndef OPTISMART_H
#define OPTISMART_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"




QT_BEGIN_NAMESPACE
namespace Ui {
class optismart;
}
QT_END_NAMESPACE

class optismart : public QMainWindow
{
    Q_OBJECT

public:
    optismart(QWidget *parent = nullptr);
    ~optismart();


private:
    Ui::optismart *ui;
};

#endif // OPTISMART_H
