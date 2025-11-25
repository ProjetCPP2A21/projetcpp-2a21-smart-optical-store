#include "produit.h"
#include <QSqlQuery>
#include <QtDebug>

produit::produit()
{
}

bool produit::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO produit (id_produit, type, quantite, prix, couleur, epaisseur, diametre, id_client, id_employe, id_fournisseur) "
                  "VALUES (:id_produit, :type, :quantite, :prix, :couleur, :epaisseur, :diametre, :id_client, :id_employe, :id_fournisseur)");

    query.bindValue(":id_produit", id_produit);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":couleur", couleur);
    query.bindValue(":epaisseur", epaisseur);
    query.bindValue(":diametre", diametre);
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":id_client", id_client);
    query.bindValue(":id_employe", id_employe);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur SQL dans ajouter() : Opération échouée.";
    }

    return success;
}

bool produit::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM produit WHERE id_produit = :id");
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur SQL dans supprimer() : Opération échouée.";
    }

    return success;
}

bool produit::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE produit SET type = :type, quantite = :quantite, prix = :prix, couleur = :couleur, "
                  "epaisseur = :epaisseur, diametre = :diametre, id_client = :id_client, id_employe = :id_employe, "
                  "id_fournisseur = :id_fournisseur WHERE id_produit = :id_produit");

    query.bindValue(":id_produit", id_produit);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":couleur", couleur);
    query.bindValue(":epaisseur", epaisseur);
    query.bindValue(":diametre", diametre);
    query.bindValue(":id_client", id_client);
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":id_fournisseur", id_fournisseur);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur SQL dans modifier() : Opération échouée.";
    }

    return success;
}

QSqlQueryModel* produit::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit");
    return model;
}
QSqlQueryModel* produit::trier() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit ORDER BY type");
    return model;
}
QSqlQueryModel* produit::rechercher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("SELECT * FROM produit WHERE type LIKE :type");
    q.bindValue(":type", "%" + type + "%");
    q.exec();
    model->setQuery(q);
    return model;
}
