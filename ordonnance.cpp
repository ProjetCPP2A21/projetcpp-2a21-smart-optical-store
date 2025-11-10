#include "ordonnance.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
#include <QMessageBox>

Ordonnance::Ordonnance() {}

Ordonnance::Ordonnance(QString cin, QString nom, QString prenom, QString medecin, QDate date)
    : cin(cin), nom(nom), prenom(prenom), medecin(medecin), date(date)
{
}

bool Ordonnance::ajouterOrdonnance()
{
    QSqlQuery query;

    query.prepare("INSERT INTO ordonnance (CIN, NOM, PRENOM, MEDECIN, DATE_ORD) "
                  "VALUES (:cin, :nom, :prenom, :medecin, :date_ord)");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":medecin", medecin);
    query.bindValue(":date_ord", date);

    qDebug() << "=== Tentative d'ajout d'ordonnance ===";
    qDebug() << "CIN:" << cin;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Médecin:" << medecin;
    qDebug() << "Date:" << date.toString("yyyy-MM-dd");

    bool success = query.exec();

    if (!success) {
        qDebug() << "❌ Erreur d'ajout:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de l'ajout: " + query.lastError().text());
    } else {
        qDebug() << "✅ Ajout réussi!";
    }

    return success;
}

void Ordonnance::afficherOrdonnance(QTableWidget *tableWidget)
{
    // Vider le tableau existant
    tableWidget->setRowCount(0);

    // Définir les en-têtes de colonnes
    QStringList headers;
    headers << "CIN" << "Nom" << "Prénom" << "Médecin" << "Date";
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(headers);

    // Exécuter la requête SQL
    QSqlQuery query("SELECT * FROM ordonnance");

    int row = 0;
    while (query.next()) {
        // Ajouter une nouvelle ligne
        tableWidget->insertRow(row);

        // Remplir les cellules avec les données
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MEDECIN").toString()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATE_ORD").toString()));

        row++;
    }

    // Ajuster la largeur des colonnes
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

bool Ordonnance::supprimerOrdonnance(QString cin)
{
    QSqlQuery query;

    // REQUÊTE PRÉPARÉE pour éviter les injections SQL
    query.prepare("DELETE FROM ordonnance WHERE CIN = :cin");

    // Liaison de la valeur (Bind Value)
    query.bindValue(":cin", cin);

    qDebug() << "=== Tentative de suppression d'ordonnance ===";
    qDebug() << "CIN à supprimer:" << cin;

    bool success = query.exec();

    if (!success) {
        qDebug() << "❌ Erreur de suppression:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de la suppression: " + query.lastError().text());
    } else {
        qDebug() << "✅ Suppression réussie!";
    }

    return success;
}

bool Ordonnance::modifierOrdonnance(QString ancienCIN)
{
    QSqlQuery query;

    // REQUÊTE PRÉPARÉE pour la modification
    query.prepare("UPDATE ordonnance SET CIN = :nouveau_cin, NOM = :nom, PRENOM = :prenom, "
                  "MEDECIN = :medecin, DATE_ORD = :date_ord WHERE CIN = :ancien_cin");

    // Liaison des valeurs (Bind Values)
    query.bindValue(":nouveau_cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":medecin", medecin);
    query.bindValue(":date_ord", date);
    query.bindValue(":ancien_cin", ancienCIN);

    qDebug() << "=== Tentative de modification d'ordonnance ===";
    qDebug() << "Ancien CIN:" << ancienCIN;
    qDebug() << "Nouveau CIN:" << cin;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Médecin:" << medecin;
    qDebug() << "Date:" << date.toString("yyyy-MM-dd");

    bool success = query.exec();

    if (!success) {
        qDebug() << "❌ Erreur de modification:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de la modification: " + query.lastError().text());
    } else {
        qDebug() << "✅ Modification réussie!";
    }

    return success;
}
