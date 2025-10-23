#ifndef ORDONNANCE_H
#define ORDONNANCE_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include <QWidget>
#include "ui_optismart.h"

class ordonnance : public QWidget
{
    Q_OBJECT

public:
    explicit ordonnance(Ui::optismart *ui, QWidget *parent = nullptr);
    ~ordonnance();

    void chargerDonnees();
    void ajouterOrdonnance();
    void modifierOrdonnance();
    void supprimerOrdonnance();
    void rechercherOrdonnance(const QString &motCle);
    void exporterPdf();

private:
    Ui::optismart *ui;
};


#endif // ORDONNANCE_H
