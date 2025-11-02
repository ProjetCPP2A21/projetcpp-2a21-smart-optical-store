#ifndef GCLIENT_H
#define GCLIENT_H
#include "client.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include <QMainWindow>

namespace Ui {
class Gclient;
}

class Gclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gclient(QWidget *parent = nullptr);
    ~Gclient();
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
    Ui::Gclient *ui;
     client c;
};

#endif // GCLIENT_H
