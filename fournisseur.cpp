#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>

fournisseur::fournisseur() {}

fournisseur::fournisseur(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT)
{
    this->ID_FOURNISSEUR = ID_FOURNISSEUR;
    this->NOM = NOM;
    this->ADRESSE = ADRESSE;
    this->EMAIL = EMAIL;
    this->NUMERO_TELEPHONE = NUMERO_TELEPHONE;
    this->CONDITION_PAIEMENT = CONDITION_PAIEMENT;
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
    headers << "ID_FOURNISSEUR" << "NOM" << "ADRESSE" << "EMAIL" << "NUMERO_TELEPHONE" << "CONDITION_PAIEMENT";
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
                  "VALUES (:ID_FOURNISSEUR, :NOM, :ADRESSE, :EMAIL, :NUMERO_TELEPHONE, :CONDITION_PAIEMENT)");

    // Liaison des valeurs
    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);
    query.bindValue(":NOM", NOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    query.bindValue(":CONDITION_PAIEMENT", CONDITION_PAIEMENT);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur ajouté avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

bool fournisseur::supprimer(QString ID_FOURNISSEUR)
{
    QSqlQuery query;

    // Requête préparée pour supprimer par ID_FOURNISSEUR
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :ID_FOURNISSEUR");
    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID_FOURNISSEUR" << ID_FOURNISSEUR << "supprimé avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

bool fournisseur::modifier(QString ID_FOURNISSEUR, QString NOM, QString ADRESSE, QString EMAIL, QString NUMERO_TELEPHONE, QString CONDITION_PAIEMENT)
{
    QSqlQuery query;

    // Requête préparée pour modifier
    query.prepare("UPDATE FOURNISSEUR SET "
                  "NOM = :NOM, "
                  "ADRESSE = :ADRESSE, "
                  "EMAIL = :EMAIL, "
                  "NUMERO_TELEPHONE = :NUMERO_TELEPHONE, "
                  "CONDITION_PAIEMENT = :CONDITION_PAIEMENT "
                  "WHERE ID_FOURNISSEUR = :ID_FOURNISSEUR");

    // Liaison des valeurs
    query.bindValue(":ID_FOURNISSEUR", ID_FOURNISSEUR);
    query.bindValue(":NOM", NOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    query.bindValue(":CONDITION_PAIEMENT", CONDITION_PAIEMENT);

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Fournisseur avec ID_FOURNISSEUR" << ID_FOURNISSEUR << "modifié avec succès!";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}
