#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"


class authentification : public QWidget
{
    Q_OBJECT

public:
    explicit authentification(Ui::optismart *ui, QWidget *parent = nullptr);
    ~authentification();

    void seConnecter();
    void annuler();

private:
    Ui::optismart *ui;
};


#endif // AUTHENTIFICATION_H
