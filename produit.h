#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString.h>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"
class produit : public QWidget
{
    Q_OBJECT

public:
    explicit produit(Ui::optismart *ui, QWidget *parent = nullptr);
    ~produit();

    void chargerDonnees();
    void ajouterProduit();
    void modifierProduit();
    void supprimerProduit();
    void rechercherProduit(const QString &motCle);
    void exporterPdf();

private:
    Ui::optismart *ui;
};

#endif // PRODUIT_H
