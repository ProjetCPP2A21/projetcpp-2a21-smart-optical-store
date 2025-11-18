#ifndef GFOURNISSEUR_H
#define GFOURNISSEUR_H

#include <QMainWindow>
#include "fournisseur.h"
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class gfournisseur;
}
QT_END_NAMESPACE

class gfournisseur : public QMainWindow
{
    Q_OBJECT

public:
    gfournisseur(QWidget *parent = nullptr);
    ~gfournisseur();

private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();

    // Nouveaux slots pour la validation en temps réel
    void on_nom_le_textChanged(const QString &text);
    void on_email_le_textChanged(const QString &text);
    void on_telephone_le_textChanged(const QString &text);

    // Nouveaux slots pour les fonctionnalités avancées
    void on_bstatistique_f_clicked();
    void on_bexporter_f_clicked();
    void on_btrier_f_clicked();
    void on_brechercher_f_clicked();
    void on_bnouveau_f_clicked();
    void on_tableWidget_4_itemClicked(QTableWidgetItem *item);

private:
    Ui::gfournisseur *ui;
    fournisseur fourn;
    void actualiserAffichage();
    void clearFields();
    void afficherGraphiqueStatistiques(); // Nouvelle méthode

    // Méthodes de validation
    bool validerNom(const QString &nom);
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    bool validerAdresse(const QString &adresse);
    void afficherErreurChamp(QLineEdit *champ, bool estValide, const QString &message = "");
};
#endif // GFOURNISSEUR_H
