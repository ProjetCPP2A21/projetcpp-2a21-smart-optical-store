#ifndef CLIENT_H
#define CLIENT_H

#include<QString.h>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(Ui::optismart *ui, QWidget *parent = nullptr);
    ~client();

    void chargerDonnees();
    void ajouterClient();
    void modifierClient();
    void supprimerClient();
    void rechercherClient(const QString &motCle);
    void exporterPdf();
    void afficherStatistiques();

private:
    Ui::optismart *ui;
};

#endif // CLIENT_H
