#ifndef GORDONNANCE_H
#define GORDONNANCE_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
#include <QTabWidget>
#include "ordonnance.h"
#include "chatbot.h"

namespace Ui {
class Gordonnance;
}

class Gordonnance : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gordonnance(QWidget *parent = nullptr);
    ~Gordonnance();

private slots:
    void on_btnActualiser_clicked();
    void on_btnAjouter_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();  // NOUVEAU SLOT
    void on_tableWidget_clicked(const QModelIndex &index);  // Pour sélectionner une ligne
    void on_pushButton_2_clicked();  // Bouton de recherche par CIN
    void on_pushButton_5_clicked();  // Bouton d'export PDF
    void on_pushButton_3_clicked();  // Bouton de tri par nom
    void on_pushButton_10_clicked();  // Bouton de statistiques
    void on_btnChatbotEnvoyer_clicked();  // Bouton d'envoi du chatbot
    void on_lineEditChatbot_returnPressed();  // Entrée dans le champ de chat

private:
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

    Ui::Gordonnance *ui;
    QTabWidget *tabWidgetPrincipal;
    Ordonnance ord;
    Chatbot chatbot;
    QString cinSelectionne;  // Pour stocker le CIN sélectionné
    QTextEdit *textEditChat;  // Zone de chat
    QLineEdit *lineEditChatbot;  // Champ de saisie du chatbot
    QLabel *labelVolumeValeur;
    QLabel *labelVolumeDetail;
    QLabel *labelMedecinValeur;
    QLabel *labelMedecinDetail;
    QLabel *labelJourValeur;
    QLabel *labelJourDetail;
    int indexTabPrevision;

    void actualiserAffichage();
    void initialiserChatbot(QWidget *parentWidget);  // Initialiser l'interface du chatbot
    void initialiserPrevisions(QWidget *parentWidget);  // Initialiser l'onglet prévisions
    void mettreAJourPrevisions();  // Rafraîchir les prévisions
    PrevisionData calculerPrevisions() const;  // Calculer les prévisions basées sur les données
    void ajouterMessageChat(const QString &message, bool estUtilisateur = false);
    void verifierAlertes();  // Vérifier les alertes en temps réel
};

#endif // GORDONNANCE_H
