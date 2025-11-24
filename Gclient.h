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
#include <QTableWidgetItem>

namespace Ui {
class Gclient;
}

class Gclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gclient(QWidget *parent = nullptr);
    ~Gclient();
    void colorerCategorie(QTableWidgetItem *item);
    QString calculerCategorie(int point_fedelite);
private slots:
    void on_bajouter_c_clicked();
private slots:
     void on_bsupprimer_c_clicked();
     /*void afficher_client();*/
     void afficher_client(int id_selectionne = -1);
 private slots:
     void on_tableWidget_c_cellClicked(int row, int column);
     void on_bmodifier_c_clicked();
 private slots:
     void on_brechercher_c_clicked();
     void on_btrier_c_clicked();
     void on_bexporter_c_clicked();
 private slots:
     void on_bstatistique_c_clicked();
     void afficherStatistiques_client();
     /*void on_bstatistique_c_clicked();*/
     //void afficher_client_categorie();
     void chargerClients();
//couleur
 private slots:
     void on_tableWidget_c_cellChanged(int row, int column);
     void on_tableWidget_c_horizontalHeader_sectionClicked(int column);
     void mettreAJourCategorie(int row, int col);
     void recolorerToutesLesLignes();

private:
    Ui::Gclient *ui;
     client c;
};

#endif // GCLIENT_H
