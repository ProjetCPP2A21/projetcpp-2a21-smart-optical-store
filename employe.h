#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QDateTime>
#include <QStandardPaths>
#include <QFileInfo>
#include <QtPrintSupport/QPrinter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>

#include "ui_optismart.h"

class employe : public QObject
{
    Q_OBJECT

private:
    int id_employe;
    QString nom;
    QString prenom;
    QString adresse;
    QString email;
    QString num_tel;
    QString poste;
    QString login;
    QString password;

    Ui::optismart *ui;

public:
    explicit employe(Ui::optismart *ui, QObject *parent = nullptr);

    // --- Getters / Setters ---
    int getId() const { return id_employe; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getAdresse() const { return adresse; }
    QString getEmail() const { return email; }
    QString getNumTel() const { return num_tel; }
    QString getPoste() const { return poste; }
    QString getLogin() const { return login; }
    QString getPassword() const { return password; }

    void setId(int id);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setAdresse(const QString &adresse);
    void setEmail(const QString &email);
    void setNumTel(const QString &num_tel);
    void setPoste(const QString &poste);
    void setLogin(const QString &login);
    void setPassword(const QString &password);

    // --- Méthodes SQL ---
    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    void viderChamps();
    void rechercherParNom();
    QSqlQueryModel *rechercher(const QString &nom);
    bool exporterPdf(const QString &fichier);
    void afficherStatistiques();

    // --- Interaction UI ---
    void chargerDepuisUI();
    void afficherDansTable();

};

#endif // EMPLOYE_H
