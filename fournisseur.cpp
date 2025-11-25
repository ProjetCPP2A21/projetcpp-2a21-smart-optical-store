#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>

fournisseur::fournisseur() {}

fournisseur::fournisseur(QString id_fournisseur, QString nom, QString adresse, QString email, QString numero_telephone, QString condition_paiement)
{
    this->id_fournisseur = id_fournisseur;
    this->nom = nom;
    this->adresse = adresse;
    this->email = email;
    this->numero_telephone = numero_telephone;
    this->condition_paiement = condition_paiement;
}

void fournisseur::afficher(QTableWidget *tableWidget)
{
    qDebug() << "=== DÉBUT DE AFFICHER() ===";

    if (!tableWidget) {
        qDebug() << "❌ ERREUR: tableWidget est null!";
        return;
    }

    // Vider le tableau existant
    tableWidget->setRowCount(0);

    // Définir les en-têtes de colonnes
    QStringList headers;
    headers << "ID Fournisseur" << "Nom" << "Adresse" << "Email" << "Numéro Téléphone" << "Condition Paiement";
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(headers);

    // Exécuter la requête SQL
    QSqlQuery query;
    if (!query.exec("SELECT * FROM FOURNISSEUR")) {
        qDebug() << "❌ Erreur requête:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

        // Remplir chaque colonne
        for (int col = 0; col < 6; col++) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }

    // Ajuster la largeur des colonnes
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

bool fournisseur::ajouter()
{
    QSqlQuery query;

    // Requête préparée pour éviter les injections SQL
    query.prepare("INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT) "
                  "VALUES (:id_fournisseur, :nom, :adresse, :email, :numero_telephone, :condition_paiement)");

    // Liaison des valeurs
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":numero_telephone", numero_telephone);
    query.bindValue(":condition_paiement", condition_paiement);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur ajouté avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

bool fournisseur::supprimer(QString id_fournisseur)
{
    QSqlQuery query;

    // Requête préparée pour supprimer par ID
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID" << id_fournisseur << "supprimé avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

bool fournisseur::modifier(QString id_fournisseur, QString nom, QString adresse, QString email, QString numero_telephone, QString condition_paiement)
{
    QSqlQuery query;

    // Requête préparée pour modifier
    query.prepare("UPDATE FOURNISSEUR SET "
                  "NOM = :nom, "
                  "ADRESSE = :adresse, "
                  "EMAIL = :email, "
                  "NUMERO_TELEPHONE = :numero_telephone, "
                  "CONDITION_PAIEMENT = :condition_paiement "
                  "WHERE ID_FOURNISSEUR = :id_fournisseur");

    // Liaison des valeurs
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":numero_telephone", numero_telephone);
    query.bindValue(":condition_paiement", condition_paiement);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID" << id_fournisseur << "modifié avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}
