#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QTableWidget>
#include <QSqlError>
#include <QDebug>
#include <QVariantMap>
#include <QMap>
#include <QRegularExpression>
#include <algorithm>

class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT);

    // ==================== CRUD ====================
    bool ajouter();
    bool supprimer(QString ID_FOURNISSEUR);
    bool modifier(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT);
    void afficher(QTableWidget *tableWidget);

    // ==================== VALIDATION ====================
    static bool validerNom(const QString &nom);
    static bool validerEmail(const QString &email);
    static bool validerTelephone(const QString &telephone);
    static bool validerAdresse(const QString &adresse);
    static bool validerConditionPaiement(const QString &condition);
    static bool validerId(const QString &id);

    // ==================== RECHERCHE ET TRI ====================
    bool rechercherParId(QString ID_FOURNISSEUR, QTableWidget *tableWidget);
    void trierParIdNumerique(QTableWidget *tableWidget, bool ordreCroissant = true);

    // ==================== STATISTIQUES ====================
    QMap<QString, int> getStatistiquesParConditionPaiement();

    // ==================== CARTE DES FOURNISSEURS ====================
    QList<QVariantMap> getAllFournisseursForMap();  // ⭐ NOUVEAU

    // ==================== GETTERS ====================
    QString getID_FOURNISSEUR() const { return ID_FOURNISSEUR; }
    QString getNOM() const { return NOM; }
    QString getADRESSE() const { return ADRESSE; }
    QString getEMAIL() const { return EMAIL; }
    QString getNUMERO_TELEPHONE() const { return NUMERO_TELEPHONE; }
    QString getCONDITION_PAIEMENT() const { return CONDITION_PAIEMENT; }

    // ==================== SETTERS ====================
    void setID_FOURNISSEUR(QString ID_FOURNISSEUR) { this->ID_FOURNISSEUR = ID_FOURNISSEUR; }
    void setNOM(QString NOM) { this->NOM = NOM; }
    void setADRESSE(QString ADRESSE) { this->ADRESSE = ADRESSE; }
    void setEMAIL(QString EMAIL) { this->EMAIL = EMAIL; }
    void setNUMERO_TELEPHONE(QString NUMERO_TELEPHONE) { this->NUMERO_TELEPHONE = NUMERO_TELEPHONE; }
    void setCONDITION_PAIEMENT(QString CONDITION_PAIEMENT) { this->CONDITION_PAIEMENT = CONDITION_PAIEMENT; }

private:
    QString ID_FOURNISSEUR;
    QString NOM;
    QString ADRESSE;
    QString EMAIL;
    QString NUMERO_TELEPHONE;
    QString CONDITION_PAIEMENT;
};

#endif // FOURNISSEUR_H
