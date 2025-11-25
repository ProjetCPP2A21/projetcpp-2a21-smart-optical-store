#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QTableWidget>

class fournisseur
{
public:
    fournisseur();
    fournisseur(QString id_fournisseur, QString nom, QString adresse, QString email, QString numero_telephone, QString condition_paiement);

    // Méthodes
    void afficher(QTableWidget *tableWidget);
    bool ajouter();
    bool supprimer(QString id_fournisseur);
    bool modifier(QString id_fournisseur, QString nom, QString adresse, QString email, QString numero_telephone, QString condition_paiement);

    // Getters
    QString getIDFournisseur() const { return id_fournisseur; }
    QString getNom() const { return nom; }
    QString getAdresse() const { return adresse; }
    QString getEmail() const { return email; }
    QString getNumeroTelephone() const { return numero_telephone; }
    QString getConditionPaiement() const { return condition_paiement; }

    // Setters
    void setIDFournisseur(QString id_fournisseur) { this->id_fournisseur = id_fournisseur; }
    void setNom(QString nom) { this->nom = nom; }
    void setAdresse(QString adresse) { this->adresse = adresse; }
    void setEmail(QString email) { this->email = email; }
    void setNumeroTelephone(QString numero_telephone) { this->numero_telephone = numero_telephone; }
    void setConditionPaiement(QString condition_paiement) { this->condition_paiement = condition_paiement; }

private:
    QString id_fournisseur;
    QString nom;
    QString adresse;
    QString email;
    QString numero_telephone;
    QString condition_paiement;
};

#endif // FOURNISSEUR_H
