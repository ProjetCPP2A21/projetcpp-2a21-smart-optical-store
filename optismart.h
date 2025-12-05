#ifndef OPTISMART_H
#define OPTISMART_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
#include "qtextedit.h"
#include "ui_optismart.h"
#include "produit.h"
#include "fournisseur.h"
#include "ordonnance.h"
#include "client.h"
#include "employe.h"
#include "chatbot.h"
#include "arduino_client.h"
#include "arduino_produit.h"
// ⭐ AJOUTS POUR LA CARTE
#include <QQuickWidget>
#include <QQuickItem>
#include <QQmlContext>
#include <QDialog>
#include <QVBoxLayout>

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

private:
    Ui::optismart *ui;

    // ==================== FOURNISSEUR ====================
private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();
    void on_bnouveau_f_clicked();

    // ⭐ FONCTIONNALITÉS AVANCÉES
    void on_bstatistique_f_clicked();
    void on_bexporter_f_clicked();
    void on_btrier_f_clicked();
    void on_brechercher_f_clicked();
    void on_bcarte_f_clicked();  // ⭐ NOUVEAU BOUTON CARTE

    void on_nom_le_textChanged(const QString &text);
    void on_email_le_textChanged(const QString &text);
    void on_telephone_le_textChanged(const QString &text);
    void on_cp_le_textChanged(const QString &text);

    void on_tableWidget_4_itemClicked(QTableWidgetItem *item);

private:
    void actualiserAffichageFournisseur();
    void clearFieldsFournisseur();
    void setupInterfaceFournisseur();
    void afficherErreurChampFournisseur(QLineEdit *champ, bool estValide, const QString &message = "");
    void afficherGraphiqueStatistiques();
    void setupCarteFournisseurs();  // ⭐ NOUVEAU

    Fournisseur fourn;

    // ⭐ CARTE DES FOURNISSEURS
    QQuickWidget *m_mapWidget;
    QDialog *m_mapDialog;


    // ==================== CLIENT ====================
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

    void on_tableWidget_c_cellChanged(int row, int column);
    void on_tableWidget_c_horizontalHeader_sectionClicked(int column);
    void mettreAJourCategorie(int row, int col);
    void recolorerToutesLesLignes();
    //arduino
private:
    arduino_client AC;  // objet Arduino pour module client

private slots:
    void on_lineEdit_id_textChanged(const QString &arg1);

    // ==================== PRODUIT ====================
private slots:
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
    void onCarteDetectee(const QString &uid);

private:
    produit Ptmp;
    arduino_produit arduinoProduit;
    bool isFilteringProduits = false;       // if you don't already have it
    bool isFilteringFournisseurs = false;   // NEW
    bool isFilteringOrdonnances = false;    // NEW

    void chargerProduits();
    int selectedIdProduit;

    // ==================== ORDONNANCE ====================
private slots:
    void on_bajouter_o_clicked();
    void on_bsupprimer_o_clicked();
    void on_bmodifier_o_clicked();
    void on_bactualiser_o_clicked();
    void on_tableWidget_o_clicked(const QModelIndex &index);
    void on_brechercher_o_clicked();  // Recherche par CIN
    void on_bexporter_o_clicked();    // Export PDF
    void on_btrier_o_clicked();       // Tri par nom
    void on_bstatistique_o_clicked(); // Statistiques
    void on_bchatbot_o_clicked();     // Bouton Chatbot
    void on_bprevision_o_clicked();   // Bouton Prévisions

private:
    QString cinSelectionne;
    Ordonnance ord;
    Chatbot chatbot;
    void actualiserAffichageOrdonnance();
    bool validerCIN(const QString& cin);
    bool validerNomPrenom(const QString& texte, const QString& champ);

    // Fonctionnalités avancées
    void initialiserChatbot(QWidget *parentWidget);
    void initialiserPrevisions(QWidget *parentWidget);
    void mettreAJourPrevisions();

    // Structures pour les prévisions
    struct PrevisionData {
        QString volumeTexte;
        QString volumeDetail;
        QString medecinTexte;
        QString medecinDetail;
        QString jourTexte;
        QString jourDetail;
        bool hasVolume = false;
        bool hasMedecin = false;
        bool hasJour = false;
    };

    PrevisionData calculerPrevisions() const;

    // Widgets pour chatbot et prévisions
    QTextEdit *textEditChat;
    QLineEdit *lineEditChatbot;
    QLabel *labelVolumeValeur;
    QLabel *labelVolumeDetail;
    QLabel *labelMedecinValeur;
    QLabel *labelMedecinDetail;
    QLabel *labelJourValeur;
    QLabel *labelJourDetail;

    // Dialogues pour chatbot et prévisions
    QDialog *dialogChatbot;
    QDialog *dialogPrevision;

    // Slots pour chatbot
    void on_btnChatbotEnvoyer_clicked();
    void on_lineEditChatbot_returnPressed();
    void ajouterMessageChat(const QString &message, bool estUtilisateur = false);
    void verifierAlertes();
};

#endif // OPTISMART_H
