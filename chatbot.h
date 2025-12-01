#ifndef CHATBOT_H
#define CHATBOT_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QTableWidget>
#include <QSqlQuery>
#include <QRegularExpression>

class Chatbot
{
public:
    Chatbot();
    
    // Traitement des messages utilisateur
    QString traiterMessage(const QString &message, QTableWidget *tableWidget = nullptr);
    
    // Détection d'anomalies
    QStringList detecterAnomalies();
    
    // Génération de rapports automatisés
    QString genererRapportActivite();
    
    // Auto-complétion contextuelle
    QStringList suggererAutoCompletion(const QString &textePartiel, int position);

private:
    // Analyse du langage naturel
    enum IntentType {
        RECHERCHE_MEDECIN,
        RECHERCHE_PATIENT,
        RECHERCHE_DATE,
        STATISTIQUE_NOMBRE,
        STATISTIQUE_DATE,
        STATISTIQUE_MEDECIN,
        ALERTE_ANOMALIES,
        RAPPORT_ACTIVITE,
        AIDE,
        INCONNU
    };
    
    IntentType analyserIntention(const QString &message);
    QString extraireParametre(const QString &message, const QString &motCle);
    
    // Fonctions de recherche intelligente
    QString rechercherParMedecin(const QString &medecin, QTableWidget *tableWidget);
    QString rechercherParPatient(const QString &nom, QTableWidget *tableWidget);
    QString rechercherParDate(const QString &dateStr, QTableWidget *tableWidget);
    
    // Fonctions de statistiques
    QString obtenirStatistiqueNombre(const QString &periode = "");
    QString obtenirStatistiqueDate(const QString &dateStr = "");
    QString obtenirStatistiqueMedecin(const QString &medecin = "");
    
    // Détection d'anomalies
    QStringList detecterDoublons();
    QStringList detecterCINInvalides();
    QStringList detecterDatesAnormales();
    
    // Utilitaires
    QDate parserDate(const QString &dateStr);
    bool estCINValide(const QString &cin);
    QString formaterDate(const QDate &date);
};

#endif // CHATBOT_H

