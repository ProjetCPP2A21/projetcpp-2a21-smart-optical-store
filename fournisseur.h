#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QTableWidget>

class fournisseur
{
public:
    fournisseur();
    fournisseur(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT);

    // Méthodes
    void afficher(QTableWidget *tableWidget);
    bool ajouter();
    bool supprimer(QString ID_FOURNISSEUR);
    bool modifier(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT);

    // Getters
    QString getID_FOURNISSEUR() const { return ID_FOURNISSEUR; }
    QString getNOM() const { return NOM; }
    QString getADRESSE() const { return ADRESSE; }
    QString getEMAIL() const { return EMAIL; }
    QString getNUMERO_TELEPHONE() const { return NUMERO_TELEPHONE; }
    QString getCONDITION_PAIEMENT() const { return CONDITION_PAIEMENT; }

    // Setters
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
