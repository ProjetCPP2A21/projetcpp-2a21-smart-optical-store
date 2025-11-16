#include "gproduit.h"
#include "ui_gproduit.h"
#include "produit.h"
#include <QMessageBox>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

gproduit::gproduit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gproduit)
    , selectedIdProduit(-1)
    , Ptmp()
{
    ui->setupUi(this);
}

gproduit::~gproduit()
{
    delete ui;
}

void gproduit::refreshTable()
{
    ui->tableWidget_p_2->setModel(Ptmp.afficher());
}

void gproduit::on_ajouterButton_clicked()
{
    // === RÉCUPÉRATION ET VALIDATION DES CHAMPS ===
    QString type = ui->typeEdit->text().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Type ne peut pas être vide ❌"));
        return;
    }

    bool ok;
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Quantité invalide (doit être un entier > 0) ❌"));
        return;
    }

    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Prix invalide (doit être un nombre > 0) ❌"));
        return;
    }

    QString couleur = ui->couleurEdit->text().trimmed();
    if (couleur.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Couleur ne peut pas être vide ❌"));
        return;
    }

    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok || epaisseur < 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Épaisseur invalide (doit être un nombre >= 0) ❌"));
        return;
    }

    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Diamètre invalide (doit être un nombre > 0) ❌"));
        return;
    }

    int id_produit = ui->idEdit->text().trimmed().toInt(&ok);
    if (!ui->idEdit->text().isEmpty() && !ok) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID produit invalide (entier ou vide) ❌"));
        return;
    }

    int id_fournisseur = ui->idFEdit->text().trimmed().toInt(&ok);
    if (!ok || id_fournisseur <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID fournisseur invalide (entier > 0) ❌"));
        return;
    }

    int id_client = ui->idCEdit->text().trimmed().toInt(&ok);
    if (!ok || id_client <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID client invalide (entier > 0) ❌"));
        return;
    }

    int id_employe = ui->idEEdit->text().trimmed().toInt(&ok);
    if (!ok || id_employe <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID employé invalide (entier > 0) ❌"));
        return;
    }

    // === CONFIGURATION DE L'OBJET PRODUIT ===
    Ptmp.setIdProduit(id_produit);
    Ptmp.setType(type);
    Ptmp.setQuantite(quantite);
    Ptmp.setPrix(prix);
    Ptmp.setCouleur(couleur);
    Ptmp.setEpaisseur(epaisseur);
    Ptmp.setDiametre(diametre);
    Ptmp.setIdClient(id_client);
    Ptmp.setIdFournisseur(id_fournisseur);
    Ptmp.setIdEmploye(id_employe);

    // === AJOUT DANS LA BASE ===
    bool test = Ptmp.ajouter();  // LA LIGNE CRUCIALE

    if (test)
    {
        // Rafraîchir le tableau
        ui->tableWidget_p_2->setModel(Ptmp.afficher());

        // Générer QR Code automatiquement
        int nouvelId = Ptmp.getLastInsertedId();
        if (nouvelId > 0) {
            selectedIdProduit = nouvelId;
            on_genererQrButton_clicked();  // QR AUTO
        }

        // Message de succès
        QMessageBox::information(this, tr("Succès"), tr("Produit ajouté avec succès + QR Code généré ✅"));

        // Vider tous les champs
        ui->idEdit->clear();
        ui->typeEdit->clear();
        ui->quantiteEdit->clear();
        ui->prixEdit->clear();
        ui->couleurEdit->clear();
        ui->epaisseurEdit->clear();
        ui->diametreEdit->clear();
        ui->idFEdit->clear();
        ui->idCEdit->clear();
        ui->idEEdit->clear();

        // Mettre à jour les stats (si la fonction existe)
        on_statsButton_clicked();
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l’ajout dans la base de données ❌"));
    }
}

void gproduit::on_supprimerButton_clicked()
{
    bool ok;
    int id = ui->idEdit->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID invalide (doit être un entier > 0) ❌"));
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_produit FROM produit WHERE id_produit = :id");
    checkQuery.bindValue(":id", id);
    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucun produit avec cet ID n'existe ❌"));
        return;
    }

    bool test = Ptmp.supprimer(id);
    if (test)
    {
        ui->tableWidget_p_2->setModel(Ptmp.afficher());
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée ✅"));
        ui->idEdit->clear();
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Suppression non effectuée ❌"));
    }
}

void gproduit::on_tableWidget_p_2_doubleClicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    selectedIdProduit = ui->tableWidget_p_2->model()->index(selectedRow, 0).data().toInt(); // Stocker l'ID
    ui->idEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 0).data().toString());
    ui->typeEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 1).data().toString());
    ui->quantiteEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 2).data().toString());
    ui->prixEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 3).data().toString());
    ui->couleurEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 4).data().toString());
    ui->epaisseurEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 5).data().toString());
    ui->diametreEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 6).data().toString());
    ui->idCEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 7).data().toString());
    ui->idEEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 8).data().toString());
    ui->idFEdit->setText(ui->tableWidget_p_2->model()->index(selectedRow, 9).data().toString());
}

void gproduit::on_modifierButton_clicked()
{
    if (selectedIdProduit <= 0) { // Vérifier si un ID valide a été sélectionné
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez sélectionner un produit à modifier. ❌"));
        return;
    }

    bool ok;
    QString type = ui->typeEdit->text();
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Quantité invalide (doit être un entier > 0) ❌"));
        return;
    }
    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Prix invalide (doit être un nombre > 0) ❌"));
        return;
    }
    QString couleur = ui->couleurEdit->text();
    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok || epaisseur < 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Épaisseur invalide (doit être un nombre >= 0) ❌"));
        return;
    }
    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Diamètre invalide (doit être un nombre > 0) ❌"));
        return;
    }

    if (type.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Type ne peut pas être vide ❌"));
        return;
    }
    if (couleur.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Couleur ne peut pas être vide ❌"));
        return;
    }
    int id_fournisseur = ui->idFEdit->text().trimmed().toInt(&ok);
    if (!ok || id_fournisseur <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_fournisseur invalide (doit être un entier > 0) ❌"));
        return;
    }
    int id_client = ui->idCEdit->text().trimmed().toInt(&ok);
    if (!ok || id_client <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_client invalide (doit être un entier > 0) ❌"));
        return;
    }
    int id_employe = ui->idEEdit->text().trimmed().toInt(&ok);
    if (!ok || id_employe <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_employe invalide (doit être un entier > 0) ❌"));
        return;
    }

    Ptmp.setIdProduit(selectedIdProduit); // Utiliser l'ID stocké
    Ptmp.setType(type);
    Ptmp.setQuantite(quantite);
    Ptmp.setPrix(prix);
    Ptmp.setCouleur(couleur);
    Ptmp.setEpaisseur(epaisseur);
    Ptmp.setDiametre(diametre);
    Ptmp.setIdClient(id_client);
    Ptmp.setIdFournisseur(id_fournisseur);
    Ptmp.setIdEmploye(id_employe);

    bool test = Ptmp.modifier();
    if (test)
    {
        ui->tableWidget_p_2->setModel(Ptmp.afficher()); // Mettre à jour le tableau
        QMessageBox::information(this, tr("Succès"), tr("Produit modifié avec succès ✅"));
        ui->idEdit->clear();
        ui->typeEdit->clear();
        ui->quantiteEdit->clear();
        ui->prixEdit->clear();
        ui->couleurEdit->clear();
        ui->epaisseurEdit->clear();
        ui->diametreEdit->clear();
        ui->idFEdit->clear();
        ui->idCEdit->clear();
        ui->idEEdit->clear();
        selectedIdProduit = -1;
        on_statsButton_clicked();        // Réinitialiser l'ID après modification
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification du produit ❌"));
    }
}

void gproduit::on_searchButton_clicked()
{
    bool ok;
    int id = ui->searchIdEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("ID invalide (doit être un entier > 0) ❌"));
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM produit WHERE id_produit = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucun produit avec cet ID n'existe ❌"));
        return;
    }

    // Créer un modèle temporaire pour afficher le résultat
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query)); // Utiliser std::move pour éviter l'avertissement
    ui->tableWidget_p_2->setModel(model);

    // Remplir les champs avec les données trouvées
    ui->idEdit->setText(model->index(0, 0).data().toString());
    ui->typeEdit->setText(model->index(0, 1).data().toString());
    ui->quantiteEdit->setText(model->index(0, 2).data().toString());
    ui->prixEdit->setText(model->index(0, 3).data().toString());
    ui->couleurEdit->setText(model->index(0, 4).data().toString());
    ui->epaisseurEdit->setText(model->index(0, 5).data().toString());
    ui->diametreEdit->setText(model->index(0, 6).data().toString());
    ui->idCEdit->setText(model->index(0, 7).data().toString());
    ui->idEEdit->setText(model->index(0, 8).data().toString());
    ui->idFEdit->setText(model->index(0, 9).data().toString());
    on_statsButton_clicked();
}

void gproduit::on_exportPdfButton_clicked()
{
    // Demander à l'utilisateur de choisir l'emplacement et le nom du fichier PDF
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer en PDF"), QString(), tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return; // L'utilisateur a annulé
    }
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Créer un objet QPdfWriter pour générer le PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMargins(20, 20, 20, 20)); // Marges en points (1/72 pouce)
    QPainter painter(&pdfWriter);

    // Obtenir le modèle actuel de tableWidget_p_2
    QAbstractItemModel* model = ui->tableWidget_p_2->model();
    if (!model) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucun modèle de données disponible. ❌"));
        return;
    }

    // Définir la police et les dimensions
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    // Titre du document
    painter.drawText(20, 40, tr("Liste des Produits - Exporté le ") + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"));
    painter.drawLine(20, 60, 570, 60); // Ligne sous le titre (A4 = 595x842 points)

    // Calculer la position de départ pour le tableau
    int yPos = 80;
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();

    // Définir des largeurs de colonnes adaptées (ajustez selon vos besoins)
    int columnWidths[] = {60, 80, 50, 50, 60, 50, 50, 50, 50, 60}; // Ajustez ces valeurs
    int totalWidth = 0;
    for (int col = 0; col < columnCount; ++col) {
        totalWidth += columnWidths[col];
    }

    // Dessiner les en-têtes de colonnes
    int xPos = 20;
    painter.drawLine(xPos, yPos, xPos + totalWidth, yPos);
    for (int col = 0; col < columnCount; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xPos + 5, yPos + 15, header);
        painter.drawLine(xPos + columnWidths[col], yPos, xPos + columnWidths[col], yPos + 20);
        xPos += columnWidths[col];
    }
    painter.drawLine(20, yPos + 20, 20 + totalWidth, yPos + 20);
    yPos += 20;

    // Dessiner les données
    for (int row = 0; row < rowCount; ++row) {
        xPos = 20;
        painter.drawLine(xPos, yPos, xPos + totalWidth, yPos);
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->index(row, col).data().toString();
            painter.drawText(xPos + 5, yPos + 15, data);
            painter.drawLine(xPos + columnWidths[col], yPos, xPos + columnWidths[col], yPos + 20);
            xPos += columnWidths[col];
        }
        painter.drawLine(20, yPos + 20, 20 + totalWidth, yPos + 20);
        yPos += 20;
    }
    painter.drawLine(20, yPos, 20 + totalWidth, yPos);

    // Fin du dessin
    painter.end();

    QMessageBox::information(this, tr("Succès"), tr("Exportation en PDF réussie ! Fichier sauvegardé : %1").arg(fileName));
}
void gproduit::on_statsButton_clicked()
{
    QSqlQuery query;
    query.exec("SELECT type, SUM(quantite) FROM produit GROUP BY type ORDER BY SUM(quantite) DESC");

    // === DONNÉES ===
    QStringList types;
    QList<int> quantites;
    int maxQty = 0;
    while (query.next()) {
        types << query.value(0).toString().left(10);
        int qty = query.value(1).toInt();
        quantites << qty;
        if (qty > maxQty) maxQty = qty;
    }

    if (maxQty == 0) {
        ui->statcanvas->clear();
        ui->statcanvas->setRowCount(1);
        ui->statcanvas->setColumnCount(1);
        ui->statcanvas->setItem(0, 0, new QTableWidgetItem("AUCUN STOCK"));
        return;
    }

    // === CONFIG ===
    int rows = 20;  // Hauteur max
    int barWidth = 3;
    int spacing = 2;
    int cols = types.size() * (barWidth + spacing) + 2;
    ui->statcanvas->clear();
    ui->statcanvas->setRowCount(rows + 3);
    ui->statcanvas->setColumnCount(cols);
    ui->statcanvas->setShowGrid(true);

    // === COULEUR VERTE ===
    QColor barColor = QColor("#2e8b57");  // Vert foncé

    // === DESSINER LES BARRES ===
    for (int i = 0; i < types.size(); ++i) {
        int colStart = 1 + i * (barWidth + spacing);
        int qty = quantites[i];
        int height = (qty * rows) / (maxQty + 1);  // +1 pour éviter division par 0

        // Barre
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < barWidth; ++w) {
                QTableWidgetItem *item = new QTableWidgetItem("");
                item->setBackground(barColor);
                ui->statcanvas->setItem(rows - h - 1, colStart + w, item);
            }
        }

        // Valeur en haut
        QTableWidgetItem *valItem = new QTableWidgetItem(QString::number(qty));
        valItem->setTextAlignment(Qt::AlignCenter);
        valItem->setBackground(Qt::white);
        ui->statcanvas->setItem(rows - height - 1, colStart + 1, valItem);

        // Étiquette en bas
        QTableWidgetItem *labelItem = new QTableWidgetItem(types[i]);
        labelItem->setTextAlignment(Qt::AlignCenter);
        ui->statcanvas->setItem(rows + 1, colStart + 1, labelItem);
    }

    // === ÉCHELLE VERTICALE ===
    ui->statcanvas->setItem(rows, 0, new QTableWidgetItem("0"));
    for (int r = 5; r <= rows; r += 5) {
        int val = (r * maxQty) / rows;
        ui->statcanvas->setItem(rows - r, 0, new QTableWidgetItem(QString::number(val)));
    }

    // === TITRE ===
    ui->statcanvas->setItem(rows + 2, 0, new QTableWidgetItem("Option frequency"));

    ui->statcanvas->resizeColumnsToContents();
    ui->statcanvas->resizeRowsToContents();
}
void gproduit::on_trierButton_clicked()
{
    // ÉTAPE 1 : Recharge toutes les données du tableau
    ui->tableWidget_p_2->setModel(Ptmp.afficher());

    // ÉTAPE 2 : Trie les lignes par la colonne "type" (colonne 1)
    ui->tableWidget_p_2->sortByColumn(1, Qt::AscendingOrder);
}
void gproduit::on_genererQrButton_clicked()
{
    if (selectedIdProduit <= 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un produit !");
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT type, quantite, prix FROM produit WHERE id_produit = :id");
    q.bindValue(":id", selectedIdProduit);
    if (!q.exec() || !q.next()) return;

    QString type = q.value(0).toString();
    int quantite = q.value(1).toInt();
    float prix = q.value(2).toFloat();

    QString data = QString("ID: %1\nType: %2\nQté: %3\nPrix: %4 DT")
                       .arg(selectedIdProduit).arg(type).arg(quantite).arg(prix, 0, 'f', 2);

    QString url = "https://api.qrserver.com/v1/create-qr-code/?size=200x200&data="
                  + QUrl::toPercentEncoding(data);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap qr;
            qr.loadFromData(reply->readAll());
            ui->qrCodeLabel->setPixmap(qr.scaled(200, 200, Qt::KeepAspectRatio));
            QMessageBox::information(this, "QR", "Généré ! Scannez avec votre téléphone");
        }
        reply->deleteLater();
    });
    manager->get(QNetworkRequest(QUrl(url)));
}
