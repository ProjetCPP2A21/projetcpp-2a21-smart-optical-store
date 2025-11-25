#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QTableWidget>

class fournisseur
{
public:
    fournisseur();
    fournisseur(QString id, QString nom, QString adresse, QString email, QString telephone, QString condition_paiement);

    // Méthodes
    void afficher(QTableWidget *tableWidget);
    bool ajouter();
    bool supprimer(QString id);
    bool modifier(QString id, QString nom, QString adresse, QString email, QString telephone, QString condition_paiement);  // ⭐ NOUVELLE MÉTHODE

    // Getters
    QString getID() const { return id; }
    QString getNom() const { return nom; }
    QString getAdresse() const { return adresse; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getConditionPaiement() const { return condition_paiement; }

    // Setters
    void setID(QString id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setAdresse(QString adresse) { this->adresse = adresse; }
    void setEmail(QString email) { this->email = email; }
    void setTelephone(QString telephone) { this->telephone = telephone; }
    void setConditionPaiement(QString condition_paiement) { this->condition_paiement = condition_paiement; }

private:
    QString id;
    QString nom;
    QString adresse;
    QString email;
    QString telephone;
    QString condition_paiement;
};

#endif // FOURNISSEUR_H
