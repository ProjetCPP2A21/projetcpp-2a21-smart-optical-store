#ifndef GORDONNANCE_H
#define GORDONNANCE_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
#include <QTabWidget>
#include <QStatusBar>
#include "ordonnance.h"
#include "chatbot.h"
#include "arduino_o.h"
#include <QSqlQuery>
#include <QTimer>

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
    void on_btnModifier_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_10_clicked();
    void on_btnChatbotEnvoyer_clicked();
    void on_lineEditChatbot_returnPressed();

    // NOUVEAUX SLOTS POUR ARDUINO
    void lireDonneesArduino();
    void traiterBufferArduino();

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

    // ARDUINO
    Arduino_o arduino_o;
    QLabel *labelResultatRecherche;
    QTimer *timerArduino;
    QTimer *timeoutBuffer;
    QString bufferArduino;

    QString cinSelectionne;
    QTextEdit *textEditChat;
    QLineEdit *lineEditChatbot;
    QLabel *labelVolumeValeur;
    QLabel *labelVolumeDetail;
    QLabel *labelMedecinValeur;
    QLabel *labelMedecinDetail;
    QLabel *labelJourValeur;
    QLabel *labelJourDetail;
    int indexTabPrevision;

    void actualiserAffichage();
    void initialiserChatbot(QWidget *parentWidget);
    void initialiserPrevisions(QWidget *parentWidget);
    void mettreAJourPrevisions();
    PrevisionData calculerPrevisions() const;
    void ajouterMessageChat(const QString &message, bool estUtilisateur = false);
    void verifierAlertes();

    // NOUVELLES METHODES POUR ARDUINO
    void initialiserArduino();
    void rechercherEmployeParID(const QString &id);
    void afficherResultatRecherche(const QString &message, bool trouve);
    void extraireEtTraiterIDs(const QString &buffer);
};

#endif // GORDONNANCE_H
