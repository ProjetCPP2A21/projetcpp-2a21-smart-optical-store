#ifndef ORDONNANCE_H
#define ORDONNANCE_H

#include <QString>
#include <QSqlQuery>
#include <QTableWidget>
#include <QDate>

class Ordonnance
{
private:
    QString cin;
    QString nom;
    QString prenom;
    QString medecin;
    QDate date;

public:
    Ordonnance();
    Ordonnance(QString cin, QString nom, QString prenom, QString medecin, QDate date);

    // Getters
    QString getCIN() const { return cin; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getMedecin() const { return medecin; }
    QDate getDate() const { return date; }

    // Setters
    void setCIN(QString c) { cin = c; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setMedecin(QString m) { medecin = m; }
    void setDate(QDate d) { date = d; }

    // Méthodes CRUD
    bool ajouterOrdonnance();
    void afficherOrdonnance(QTableWidget *tableWidget);
    bool supprimerOrdonnance(QString cin);
    bool modifierOrdonnance(QString ancienCIN);  // NOUVELLE MÉTHODE
};

#endif // ORDONNANCE_H
