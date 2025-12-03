#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString.h>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include <QObject>




class produit : public QObject
{
    Q_OBJECT

public:
    explicit produit(QObject *parent = nullptr);
    ~produit() = default;

    // Setters
    void setIdProduit(int id)               { id_produit = id; }
    void setType(const QString &t)           { type = t; }
    void setQuantite(int q)                  { quantite = q; }
    void setPrix(float p)                    { prix = p; }
    void setCouleur(const QString &c)        { couleur = c; }
    void setEpaisseur(float e)               { epaisseur = e; }
    void setDiametre(float d)                { diametre = d; }
    void setIdClient(int id)                 { id_client = id; }
    void setIdFournisseur(int id)            { id_fournisseur = id; }
    void setIdEmploye(int id)                { id_employe = id; }

    // Toutes les fonctions utilisées dans gproduit.cpp
    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();

    QSqlQueryModel* rechercherParId(int id);     // ← utilisé dans on_searchButton_clicked
    QSqlQuery getStatsByType();                  // ← utilisé dans on_statsButton_clicked
    QSqlQuery getProduitForQR(int id);           // ← utilisé dans on_genererQrButton_clicked
    QSqlQueryModel* trierParType();              // ← utilisé dans on_trierButton_clicked

    int getLastInsertedId();

private:
    int     id_produit = 0;
    QString type;
    int     quantite = 0;
    float   prix = 0.0f;
    QString couleur;
    float   epaisseur = 0.0f;
    float   diametre = 0.0f;
    int     id_client = 0;
    int     id_employe = 0;
    int     id_fournisseur = 0;

    void bindValues(QSqlQuery &query);
    void setFrenchHeaders(QSqlQueryModel *model);
};


#endif // PRODUIT_H


