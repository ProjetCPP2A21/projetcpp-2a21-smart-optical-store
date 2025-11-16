#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>

class produit : public QObject
{
    Q_OBJECT

private:
    int id_produit;
    QString type;
    int quantite;
    float prix;
    QString couleur;
    float epaisseur;
    float diametre;
    int id_client;      // Ajouté pour ID_CLIENT
    int id_fournisseur;
    int id_employe;    // Ajouté pour ID_FOURNISSEUR

public:
    produit();
    produit( int id_produit,QString t, int q, float p, QString c, float e, float d, int id_c, int id_f);

    // Getters
    int getIdproduit() const{ return id_produit; }
    QString getType() const { return type; }
    int getQuantite() const { return quantite; }
    float getPrix() const { return prix; }
    QString getCouleur() const { return couleur; }
    float getEpaisseur() const { return epaisseur; }
    float getDiametre() const { return diametre; }
    int getIdClient() const { return id_client; }         // Nouveau
    int getIdFournisseur() const { return id_fournisseur; }
    int getIdemploye() const { return id_employe; }    // Nouveau

    // Setters
    void setIdProduit(int id) {  id_produit=id; }
    void setType(QString t) { type = t; }
    void setQuantite(int q) { quantite = q; }
    void setPrix(float p) { prix = p; }
    void setCouleur(QString c) { couleur = c; }
    void setEpaisseur(float e) { epaisseur = e; }
    void setDiametre(float d) { diametre = d; }
    void setIdClient(int id) { id_client = id; }         // Nouveau
    void setIdFournisseur(int id) { id_fournisseur = id; }
    void setIdEmploye(int id) { id_employe = id; }
      // Nouveau

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* trier();
    QSqlQueryModel* rechercher();
    int getLastInsertedId();  // NOUVEAU
};

#endif // PRODUIT_H
