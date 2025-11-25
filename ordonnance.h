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
    bool ajouter();
    void afficher(QTableWidget *tableWidget);
    bool supprimer(QString cin);
    bool modifier(QString ancienCIN);  // NOUVELLE MÉTHODE
    
    // Méthodes métier
    void rechercherParCIN(QString cin, QTableWidget *tableWidget);
    bool exporterEnPDF(QTableWidget *tableWidget);
    void trierParNom(QTableWidget *tableWidget);
    void afficherStatistiques(QWidget *parent = nullptr);
};

#endif // ORDONNANCE_H
