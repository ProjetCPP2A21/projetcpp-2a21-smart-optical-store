#include "ordonnance.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QMap>
#include <QDate>
#include <algorithm>
#include <QFileDialog>
#include <QDir>
#include <QPrinter>
#include <QTextDocument>
#include <QPageSize>
#include <QPageLayout>
#include <QMetaType>
#include <QBrush>
#include <QColor>

Ordonnance::Ordonnance() {}

Ordonnance::Ordonnance(QString cin, QString nom, QString prenom, QString medecin, QDate date)
    : cin(cin), nom(nom), prenom(prenom), medecin(medecin), date(date)
{
}

bool Ordonnance::ajouter()
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

void Ordonnance::afficher(QTableWidget *tableWidget)
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

bool Ordonnance::supprimer(QString cin)
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

bool Ordonnance::modifier(QString ancienCIN)
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

void Ordonnance::afficherStatistiques(QWidget *parent)
{
    // Créer une boîte de dialogue pour afficher les statistiques
    QDialog *dialog = new QDialog(parent);
    dialog->setWindowTitle("Statistiques des Ordonnances par Date");
    dialog->setMinimumSize(500, 600);
    dialog->setStyleSheet("QDialog { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a8d9d0, stop:0.5 #d3e9d4, stop:1 #f2e1c9); }");

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Titre
    QLabel *title = new QLabel("📊 Statistiques des Ordonnances par Date", dialog);
    title->setStyleSheet("font: bold 18pt 'Segoe UI'; color: #2c5f2d; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Section: Nombre d'ordonnances par date
    QLabel *label1 = new QLabel("📅 Nombre d'ordonnances par date:", dialog);
    label1->setStyleSheet("font: bold 12pt 'Segoe UI'; color: #2c5f2d; margin-top: 10px;");
    layout->addWidget(label1);

    QTableWidget *tableStats = new QTableWidget(dialog);
    tableStats->setColumnCount(2);
    QStringList headers;
    headers << "Date" << "Nombre d'ordonnances";
    tableStats->setHorizontalHeaderLabels(headers);
    // Forcer la couleur du texte en noir pour garantir la visibilité
    tableStats->setStyleSheet("QTableWidget { background-color: white; border: 1px solid #2c5f2d; color: black; } "
                              "QTableWidget::item { color: black; background-color: white; } "
                              "QTableWidget::item:selected { background-color: #87CEEB; color: black; } "
                              "QHeaderView::section { background-color: #a8d9d0; color: black; font-weight: bold; }");

    // Récupérer toutes les ordonnances et faire le groupement en C++
    // Cette approche garantit que toutes les dates sont traitées correctement
    QSqlQuery query("SELECT DATE_ORD FROM ordonnance");
    
    // Map pour stocker le nombre d'ordonnances par date
    QMap<QDate, int> statsParDate;
    
    qDebug() << "=== Récupération de toutes les ordonnances ===";
    int totalOrdonnances = 0;
    
    while (query.next()) {
        QVariant dateVariant = query.value("DATE_ORD");
        QDate date;
        
        // Essayer différentes méthodes pour obtenir la date
        if (dateVariant.typeId() == QMetaType::QDate || dateVariant.canConvert<QDate>()) {
            date = dateVariant.toDate();
        } else {
            QString dateStr = dateVariant.toString();
            // Essayer de parser la date
            date = QDate::fromString(dateStr, "yyyy-MM-dd");
            if (!date.isValid()) {
                // Essayer avec seulement les 10 premiers caractères (pour enlever l'heure)
                date = QDate::fromString(dateStr.left(10), "yyyy-MM-dd");
            }
            if (!date.isValid()) {
                // Dernier essai : toDate()
                date = dateVariant.toDate();
            }
        }
        
        if (date.isValid()) {
            // Normaliser la date (enlever l'heure si présente)
            QDate dateNormalisee = QDate(date.year(), date.month(), date.day());
            statsParDate[dateNormalisee]++;
            totalOrdonnances++;
            qDebug() << "✅ Date trouvée:" << dateNormalisee.toString("dd/MM/yyyy") << "- Total pour cette date:" << statsParDate[dateNormalisee];
        } else {
            qDebug() << "⚠️ Date invalide:" << dateVariant.toString();
        }
    }
    
    qDebug() << "📊 Total d'ordonnances traitées:" << totalOrdonnances;
    qDebug() << "📊 Nombre de dates différentes:" << statsParDate.size();

    // Remplir le tableau avec les statistiques
    int row = 0;
    int totalAffiche = 0;
    
    // Trier les dates par ordre décroissant
    QList<QDate> datesTriees = statsParDate.keys();
    std::sort(datesTriees.begin(), datesTriees.end(), [](const QDate &a, const QDate &b) {
        return a > b; // Tri décroissant
    });
    
    for (const QDate &date : datesTriees) {
        tableStats->insertRow(row);
        QString dateFormatee = date.toString("dd/MM/yyyy");
        int nombre = statsParDate[date];
        
        // Créer les items avec couleur noire explicite
        QTableWidgetItem *itemDate = new QTableWidgetItem(dateFormatee);
        itemDate->setForeground(QBrush(QColor(Qt::black)));
        itemDate->setTextAlignment(Qt::AlignCenter);
        
        QTableWidgetItem *itemNombre = new QTableWidgetItem(QString::number(nombre));
        itemNombre->setForeground(QBrush(QColor(Qt::black)));
        itemNombre->setTextAlignment(Qt::AlignCenter);
        
        tableStats->setItem(row, 0, itemDate);
        tableStats->setItem(row, 1, itemNombre);
        totalAffiche += nombre;
        
        qDebug() << "📊 Ligne" << row << ":" << dateFormatee << "-" << nombre << "ordonnance(s)";
        row++;
    }

    // Si aucune donnée trouvée
    if (row == 0) {
        tableStats->insertRow(0);
        QTableWidgetItem *itemVide1 = new QTableWidgetItem("Aucune donnée");
        itemVide1->setForeground(QBrush(QColor(Qt::black)));
        QTableWidgetItem *itemVide2 = new QTableWidgetItem("0");
        itemVide2->setForeground(QBrush(QColor(Qt::black)));
        tableStats->setItem(0, 0, itemVide1);
        tableStats->setItem(0, 1, itemVide2);
    }

    tableStats->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableStats->setAlternatingRowColors(true);
    tableStats->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableStats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // S'assurer que toutes les lignes sont visibles
    tableStats->setMinimumHeight(qMax(200, (row + 1) * 30));
    tableStats->verticalHeader()->setVisible(true);
    
    layout->addWidget(tableStats);

    // Afficher le total
    QLabel *labelTotal = new QLabel(QString("📊 Total: %1 ordonnance(s)").arg(totalAffiche), dialog);
    labelTotal->setStyleSheet("font: bold 11pt 'Segoe UI'; color: #2c5f2d; margin-top: 10px; padding: 5px;");
    layout->addWidget(labelTotal);

    // Bouton de fermeture
    QPushButton *btnClose = new QPushButton("Fermer", dialog);
    btnClose->setStyleSheet("QPushButton { background-color: rgb(168, 213, 186); font: 14pt 'Segoe UI'; color: rgb(51, 51, 51); padding: 10px; }");
    QObject::connect(btnClose, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(btnClose);

    // Afficher la boîte de dialogue
    dialog->exec();
    delete dialog;

    qDebug() << "✅ Statistiques par date affichées avec succès. Total: " << totalAffiche << " ordonnance(s).";
}

void Ordonnance::rechercherParCIN(QString cin, QTableWidget *tableWidget)
{
    // Vider le tableau existant
    tableWidget->setRowCount(0);

    // Définir les en-têtes de colonnes
    QStringList headers;
    headers << "CIN" << "Nom" << "Prénom" << "Médecin" << "Date";
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(headers);

    // Exécuter la requête SQL avec recherche par CIN
    QSqlQuery query;
    query.prepare("SELECT * FROM ordonnance WHERE CIN LIKE :cin");
    query.bindValue(":cin", "%" + cin + "%");  // Recherche partielle (contient le CIN)

    qDebug() << "=== Recherche d'ordonnance par CIN ===";
    qDebug() << "CIN recherché:" << cin;

    bool success = query.exec();

    if (!success) {
        qDebug() << "❌ Erreur de recherche:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de la recherche: " + query.lastError().text());
        return;
    }

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

    qDebug() << "✅ Recherche terminée. " << row << " résultat(s) trouvé(s).";
}

bool Ordonnance::exporterEnPDF(QTableWidget *tableWidget)
{
    // Vérifier si le tableau contient des données
    if (tableWidget->rowCount() == 0) {
        QMessageBox::warning(nullptr, "Export PDF",
                            "Aucune donnée à exporter. Le tableau est vide.");
        return false;
    }

    // Demander à l'utilisateur où sauvegarder le fichier
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/ordonnances.pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) {
        return false;  // L'utilisateur a annulé
    }

    // S'assurer que le fichier a l'extension .pdf
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Créer le printer pour le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    // Créer un document texte pour le PDF
    QTextDocument document;
    QString html;

    // En-tête du document
    html += "<html><head><meta charset='UTF-8'></head><body>";
    html += "<h1 style='text-align: center; color: #2c5f2d;'>Liste des Ordonnances</h1>";
    html += "<p style='text-align: right;'>Date d'export: " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<hr>";

    // Tableau HTML
    html += "<table border='1' cellpadding='5' cellspacing='0' width='100%' style='border-collapse: collapse;'>";
    
    // En-têtes de colonnes
    html += "<tr style='background-color: #a8d9d0; font-weight: bold;'>";
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QString header = tableWidget->horizontalHeaderItem(col) ? 
                        tableWidget->horizontalHeaderItem(col)->text() : 
                        QString("Colonne %1").arg(col + 1);
        html += "<th>" + header + "</th>";
    }
    html += "</tr>";

    // Données du tableau
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            QString text = item ? item->text() : "";
            html += "<td>" + text + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";

    // Pied de page
    html += "<hr>";
    html += "<p style='text-align: center; font-size: 10pt; color: #666;'>";
    html += "Total: " + QString::number(tableWidget->rowCount()) + " ordonnance(s)";
    html += "</p>";

    html += "</body></html>";

    // Définir le contenu HTML du document
    document.setHtml(html);

    // Imprimer le document dans le PDF
    document.print(&printer);

    qDebug() << "✅ Export PDF réussi: " << fileName;
    QMessageBox::information(nullptr, "Export PDF",
                            "Le fichier PDF a été créé avec succès!\n\n" + fileName);

    return true;
}

void Ordonnance::trierParNom(QTableWidget *tableWidget)
{
    // Vérifier si le tableau contient des données
    if (tableWidget->rowCount() == 0) {
        QMessageBox::information(nullptr, "Tri",
                                "Aucune donnée à trier. Le tableau est vide.");
        return;
    }

    // Trier le tableau selon la colonne "Nom" (colonne 1)
    // Qt::AscendingOrder = tri croissant (A-Z)
    tableWidget->sortItems(1, Qt::AscendingOrder);

    qDebug() << "✅ Tri par nom effectué. " << tableWidget->rowCount() << " ordonnance(s) triée(s).";
    QMessageBox::information(nullptr, "Tri",
                            "Les ordonnances ont été triées par ordre alphabétique selon le nom.");
}
