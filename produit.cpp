// produit.cpp
#include "produit.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

produit::produit(QObject *parent) : QObject(parent)
{
    id_produit = id_client = id_employe = id_fournisseur = quantite = 0;
    prix = epaisseur = diametre = 0.0f;
}

bool produit::ajouter()
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO produit (id_produit, type, quantite, prix, couleur, epaisseur, diametre, id_client, id_employe, id_fournisseur)
        VALUES (:id_produit, :type, :quantite, :prix, :couleur, :epaisseur, :diametre, :id_client, :id_employe, :id_fournisseur)
    )");

    bindValues(query);
    if (!query.exec()) {
        qDebug() << "Erreur ajout :" << query.lastError().text();
        return false;
    }
    return true;
}

bool produit::modifier()
{
    QSqlQuery query;
    query.prepare(R"(
        UPDATE produit SET
            type = :type,
            quantite = :quantite,
            prix = :prix,
            couleur = :couleur,
            epaisseur = :epaisseur,
            diametre = :diametre,
            id_client = :id_client,
            id_employe = :id_employe,
            id_fournisseur = :id_fournisseur
        WHERE id_produit = :id_produit
    )");

    bindValues(query);
    query.bindValue(":id_produit", id_produit);

    return query.exec();
}

bool produit::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM produit WHERE id_produit = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* produit::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit");
    setFrenchHeaders(model);
    return model;
}

QSqlQueryModel* produit::rechercherParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("SELECT * FROM produit WHERE id_produit = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        model->setQuery(q);
        setFrenchHeaders(model);
    }
    return model;
}

QSqlQueryModel* produit::trierParType()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit ORDER BY type ASC");
    setFrenchHeaders(model);
    return model;
}

QSqlQuery produit::getStatsByType()
{
    QSqlQuery query;
    query.exec("SELECT type, COUNT(*) FROM produit GROUP BY type");
    return query;
}

QSqlQuery produit::getProduitForQR(int id)
{
    QSqlQuery query;
    query.prepare("SELECT type, couleur, quantite, prix FROM produit WHERE id_produit = :id");
    query.bindValue(":id", id);
    query.exec();
    return query;
}

int produit::getLastInsertedId()
{
    QSqlQuery q;
    q.exec("SELECT last_insert_rowid()");
    return q.next() ? q.value(0).toInt() : -1;
}

void produit::bindValues(QSqlQuery &query)
{
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
}

void produit::setFrenchHeaders(QSqlQueryModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, tr("ID Produit"));
    model->setHeaderData(1, Qt::Horizontal, tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, tr("Couleur"));
    model->setHeaderData(5, Qt::Horizontal, tr("Épaisseur"));
    model->setHeaderData(6, Qt::Horizontal, tr("Diamètre"));
    model->setHeaderData(7, Qt::Horizontal, tr("ID Client"));
    model->setHeaderData(8, Qt::Horizontal, tr("ID Employé"));
    model->setHeaderData(9, Qt::Horizontal, tr("ID Fournisseur"));
}
// Dans produit.cpp (à la fin du fichier)

QMap<QString, QVariant> produit::getProduitInfoByRFID(const QString &rfid) {
    QMap<QString, QVariant> result;
    result["found"] = false;

    QSqlQuery query;
    query.prepare("SELECT couleur, type, prix FROM produit WHERE rfid = :rfid");
    query.bindValue(":rfid", rfid);

    if (query.exec() && query.next()) {
        result["couleur"] = query.value(0).toString();
        result["type"] = query.value(1).toString();
        result["prix"] = query.value(2).toDouble();
        result["found"] = true;
    }

    return result;
}
