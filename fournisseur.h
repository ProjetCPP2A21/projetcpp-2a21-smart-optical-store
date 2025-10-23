#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"

class fournisseur : public QWidget
{
    Q_OBJECT

public:
    explicit fournisseur(Ui::optismart *ui, QWidget *parent = nullptr);
    ~fournisseur();

    void chargerDonnees();
    void ajouterFournisseur();
    void modifierFournisseur();
    void supprimerFournisseur();
    void rechercherFournisseur(const QString &motCle);
    void exporterPdf();

private:
    Ui::optismart *ui;
};



#endif // FOURNISSEUR_H
