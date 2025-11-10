#ifndef OPTISMART_H
#define OPTISMART_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"
#include "produit.h"
#include "fournisseur.h"
#include "ordonnance.h"  // ⭐ AJOUT: Inclure ordonnance.h

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

    //fournisseur
private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();

private:
    fournisseur fourn;
    void actualiserAffichage();
    void clearFields();

    //client
private slots:
    void on_bajouter_c_clicked();
    void on_bsupprimer_c_clicked();
    void afficher_client(int id_selectionne = -1);
    void on_tableWidget_c_cellClicked(int row, int column);
    void on_bmodifier_c_clicked();

    // produit
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_modifierButton_clicked();
    void on_tableWidget_p_2_doubleClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_exportPdfButton_clicked();
    void on_statsButton_clicked();
    void on_trierButton_clicked();

    // ⭐ AJOUT: SLOTS POUR ORDONNANCE
private slots:
    void on_bajouter_o_clicked();    // Bouton Ajouter ordonnance
    void on_bsupprimer_o_clicked();  // Bouton Supprimer ordonnance
    void on_bmodifier_o_clicked();   // Bouton Modifier ordonnance
    void on_bactualiser_o_clicked(); // Bouton Actualiser ordonnance
    void on_tableWidget_o_clicked(const QModelIndex &index); // Tableau ordonnance

private:
    Ui::optismart *ui;
    produit Ptmp;
    int selectedIdProduit;

    // ⭐ AJOUT: VARIABLES POUR ORDONNANCE
    Ordonnance ord;                   // Objet ordonnance
    QString cinSelectionne;          // Pour stocker le CIN sélectionné
    void actualiserAffichageOrdonnance(); // Fonction d'actualisation

    // ⭐ AJOUT: Fonction de validation du CIN
    bool validerCIN(const QString& cin);
    bool validerNomPrenom(const QString& texte, const QString& champ); // Nouvelle fonction

};

#endif // OPTISMART_H
