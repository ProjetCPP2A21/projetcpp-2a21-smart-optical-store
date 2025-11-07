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
     //client
private slots:
    void on_bajouter_c_clicked();
private slots:
    void on_bsupprimer_c_clicked();
    /*void afficher_client();*/
    void afficher_client(int id_selectionne = -1);
private slots:
    void on_tableWidget_c_cellClicked(int row, int column);
    void on_bmodifier_c_clicked();
private:
    Ui::optismart *ui;
};

#endif // OPTISMART_H
