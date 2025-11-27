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
#include "ordonnance.h" // AJOUT: Inclure ordonnance.h

QT_BEGIN_NAMESPACE
namespace Ui { class optismart; }
QT_END_NAMESPACE

class optismart : public QMainWindow
{
    Q_OBJECT

public:
    optismart(QWidget *parent = nullptr);
    ~optismart();

    //client
    void colorerCategorie(QTableWidgetItem *item);
    QString calculerCategorie(int point_fedelite);
    //produit
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
    void on_brechercher_c_clicked();
    void on_btrier_c_clicked();
    void on_bexporter_c_clicked();
    void on_bstatistique_c_clicked();
    void afficherStatistiques_client();
    void chargerClients();

    //couleur
private slots:
    void on_tableWidget_c_cellChanged(int row, int column);
    void on_tableWidget_c_horizontalHeader_sectionClicked(int column);
    void mettreAJourCategorie(int row, int col);
    void recolorerToutesLesLignes();

    // produit → JE GARDE EXACTEMENT TES NOMS DE SLOTS
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_modifierButton_clicked();
    void on_tableWidget_p_2_doubleClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_exportPdfButton_clicked();
    void on_statsButton_clicked();
    void on_trierButton_clicked();
    void on_genererQrButton_clicked();
    void jouerAlerteVocale(int idProduit, const QString &nomProduit, int quantite);
    void envoyerSMS(const QString &numeroDestinataire, const QString &message);

    // AJOUT: SLOTS POUR ORDONNANCE
private slots:
    void on_bajouter_o_clicked();
    void on_bsupprimer_o_clicked();
    void on_bmodifier_o_clicked();
    void on_bactualiser_o_clicked();
    void on_tableWidget_o_clicked(const QModelIndex &index);

private:
    Ui::optismart *ui;

    produit Ptmp;
    QString cinSelectionne;           // UNE SEULE FOIS ICI

    void chargerProduits();           // ta fonction de refresh
    int selectedIdProduit;

    // AJOUT: VARIABLES POUR ORDONNANCE
    Ordonnance ord;
    void actualiserAffichageOrdonnance();

    // AJOUT: Fonction de validation du CIN
    bool validerCIN(const QString& cin);
    bool validerNomPrenom(const QString& texte, const QString& champ);
};

#endif // OPTISMART_H
