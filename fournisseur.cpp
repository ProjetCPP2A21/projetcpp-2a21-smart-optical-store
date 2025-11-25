#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>

fournisseur::fournisseur() {}

fournisseur::fournisseur(QString id, QString nom, QString adresse, QString email, QString telephone, QString condition_paiement)
{
    this->id = id;
    this->nom = nom;
    this->adresse = adresse;
    this->email = email;
    this->telephone = telephone;
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
    headers << "ID Fournisseur" << "Nom" << "Adresse" << "Email" << "Téléphone" << "Condition Paiement";
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
    query.prepare("INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, TELEPHONE, CONDITION_DE_PAIEMENT) "
                  "VALUES (:id, :nom, :adresse, :email, :telephone, :condition_paiement)");

    // Liaison des valeurs
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
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

bool fournisseur::supprimer(QString id)
{
    QSqlQuery query;

    // Requête préparée pour supprimer par ID
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID" << id << "supprimé avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

// ⭐ NOUVELLE MÉTHODE: Modifier un fournisseur
bool fournisseur::modifier(QString id, QString nom, QString adresse, QString email, QString telephone, QString condition_paiement)
{
    QSqlQuery query;

    // Requête préparée pour modifier
    query.prepare("UPDATE FOURNISSEUR SET "
                  "NOM = :nom, "
                  "ADRESSE = :adresse, "
                  "EMAIL = :email, "
                  "TELEPHONE = :telephone, "
                  "CONDITION_DE_PAIEMENT = :condition_paiement "
                  "WHERE ID_FOURNISSEUR = :id");

    // Liaison des valeurs
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":condition_paiement", condition_paiement);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID" << id << "modifié avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}
