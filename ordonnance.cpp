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
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

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

void Ordonnance::afficherStatistiques(QWidget *parent)
{
    // Créer une requête pour compter les ordonnances par médecin
    QSqlQuery query("SELECT MEDECIN, COUNT(*) FROM ordonnance GROUP BY MEDECIN");
    
    // Créer la série de données pour le camembert
    QPieSeries *series = new QPieSeries();
    int total = 0;
    
    while (query.next()) {
        QString medecin = query.value(0).toString();
        int count = query.value(1).toInt();
        if (medecin.isEmpty()) medecin = "Non spécifié";
        
        series->append(medecin, count);
        total += count;
    }
    
    if (total == 0) {
        QMessageBox::information(parent, "Statistiques", "Aucune ordonnance trouvée pour les statistiques.");
        return;
    }
    
    // Configurer les étiquettes des tranches
    // Configurer les étiquettes des tranches
    for (QPieSlice *slice : series->slices()) {
        double percentage = (slice->value() / total) * 100.0;
        slice->setLabel(QString("%1: %2 (%3%)")
                        .arg(slice->label())
                        .arg(slice->value())
                        .arg(QString::number(percentage, 'f', 1)));
        
        // Afficher l'étiquette pour toutes les tranches
        slice->setLabelVisible(true);
        
        // Mettre en valeur la plus grande tranche (la première)
        if (slice == series->slices().first()) {
            slice->setExploded();
            slice->setPen(QPen(Qt::darkGreen, 2));
            slice->setBrush(Qt::green);
        }
    }
    
    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Ordonnances par Médecin");
    chart->setTitleFont(QFont("Segoe UI", 14, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);
    
    // Créer la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    // Créer la boîte de dialogue
    QDialog *dialog = new QDialog(parent);
    dialog->setWindowTitle("Statistiques des Ordonnances");
    dialog->resize(800, 600);
    
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    
    // Bouton Fermer
    QPushButton *btnClose = new QPushButton("Fermer", dialog);
    btnClose->setStyleSheet("QPushButton { background-color: rgb(168, 213, 186); font: 12pt 'Segoe UI'; color: rgb(51, 51, 51); padding: 8px; }");
    QObject::connect(btnClose, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(btnClose);
    
    dialog->exec();
    delete dialog;
}

QList<QPair<QString, QDate>> Ordonnance::recupererDonneesPrevisions()
{
    QList<QPair<QString, QDate>> resultat;
    QSqlQuery query;

    if (!query.exec("SELECT MEDECIN, DATE_ORD FROM ordonnance ORDER BY DATE_ORD ASC")) {
        qWarning() << "Erreur lors de la récupération des données de prévisions:" << query.lastError();
        return resultat;
    }

    while (query.next()) {
        QString medecin = query.value("MEDECIN").toString();
        QVariant dateVariant = query.value("DATE_ORD");

        QDate date;

        // Essayer différentes méthodes pour obtenir la date
        if (dateVariant.typeId() == QMetaType::QDate || dateVariant.canConvert<QDate>()) {
            date = dateVariant.toDate();
        } else {
            QString dateStr = dateVariant.toString();
            date = QDate::fromString(dateStr.left(10), Qt::ISODate);
            if (!date.isValid()) {
                date = QDate::fromString(dateStr, "dd/MM/yyyy");
            }
            if (!date.isValid()) {
                date = QDate::fromString(dateStr, "yyyy-MM-dd");
            }
        }

        if (date.isValid()) {
            resultat.append(qMakePair(medecin, date));
        }
    }

    return resultat;
}
