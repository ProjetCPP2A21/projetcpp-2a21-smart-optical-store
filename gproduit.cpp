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

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QDialog>

#include "qrcodegen.hpp"
#include <QImage>
#include <QPixmap>
#include <QString>


#include <QBuffer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDateTime>
#include <QSet>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QFile>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QCoreApplication>
#include <windows.h>
#include <QMediaPlayer>     // ← Ajoute cette ligne en haut de gproduit.cpp
#include <QAudioOutput>
#include <QUrl>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>     // ← LÀ, C'EST ÇA QUI MANQUAIT !
#include <QEasingCurve>
#define SMS_GATEWAY_URL "https://api.sms.tn/v1"  // remplace par l'URL réelle de ton fournisseur SMS

using qrcodegen::QrCode;

gproduit::gproduit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gproduit)
    , Ptmp()                    // D'ABORD Ptmp
    , selectedIdProduit(-1)     // ENSUITE selectedIdProduit → plus d'avertissement
{
    ui->setupUi(this);

    // Si tu veux un placeholder utile pour guider l'utilisateur (LineEdit)
    ui->typeEdit->setPlaceholderText("Ex: Lunettes Homme / Femme / Enfant / Lentilles");
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
    QString type = ui->typeEdit->text().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez saisir un type"));
        return;
    }

    bool ok;
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide");
        return;
    }

    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, "Erreur", "Prix invalide");
        return;
    }

    QString couleur = ui->couleurEdit->text().trimmed();
    if (couleur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Couleur obligatoire");
        return;
    }

    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok || epaisseur < 0) {
        QMessageBox::warning(this, "Erreur", "Épaisseur invalide");
        return;
    }

    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) {
        QMessageBox::warning(this, "Erreur", "Diamètre invalide");
        return;
    }

    int id_produit = ui->idEdit->text().trimmed().toInt(&ok);
    if (!ui->idEdit->text().isEmpty() && !ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }

    int id_fournisseur = ui->idFEdit->text().trimmed().toInt(&ok);
    if (!ok || id_fournisseur <= 0) {
        QMessageBox::warning(this, "Erreur", "ID fournisseur invalide");
        return;
    }

    int id_client = ui->idCEdit->text().trimmed().toInt(&ok);
    if (!ok || id_client <= 0) {
        QMessageBox::warning(this, "Erreur", "ID client invalide");
        return;
    }

    int id_employe = ui->idEEdit->text().trimmed().toInt(&ok);
    if (!ok || id_employe <= 0) {
        QMessageBox::warning(this, "Erreur", "ID employé invalide");
        return;
    }

    // Préparation des données
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

    bool test = Ptmp.ajouter();
    if (test) {
        refreshTable();

        // Récupérer l'ID réel du produit ajouté
        int nouvelId = Ptmp.getLastInsertedId();
        if (nouvelId <= 0) nouvelId = id_produit;

        // MESSAGE SIMPLE ET PRO
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès !");

        // ALERTE + SMS AUTOMATIQUE SI STOCK CRITIQUE
        if (quantite <= 5) {
            jouerAlerteVocale(nouvelId, type, quantite);

            static QSet<int> alertesSMS;
            if (!alertesSMS.contains(nouvelId)) {
                alertesSMS.insert(nouvelId);
                QString sms = QString("ALERTE STOCK CRITIQUE !\n\nProduit ajouté : %1\nID : %2\nQuantité : %3 unité(s)\n\nRéapprovisionnement URGENT !\nOptiSmart")
                                  .arg(type).arg(nouvelId).arg(quantite);
                envoyerSMS("+21656568218", sms);
            }
        }

        // VIDER LES CHAMPS
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

        // RIEN NE S'OUVRE TOUT SEUL → QR et Stats restent manuels

    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l’ajout dans la base de données");
    }
}
void gproduit::on_supprimerButton_clicked()
{
    bool ok;
    int id = ui->idEdit->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }
    if (Ptmp.supprimer(id)) {
        refreshTable();
        QMessageBox::information(this, "Succès", "Produit supprimé");
        ui->idEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression échouée");
    }
}

void gproduit::on_tableWidget_p_2_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    selectedIdProduit = ui->tableWidget_p_2->model()->index(row, 0).data().toInt();

    ui->idEdit->setText(ui->tableWidget_p_2->model()->index(row, 0).data().toString());
    ui->typeEdit->setText(ui->tableWidget_p_2->model()->index(row, 1).data().toString()); // LineEdit -> setText
    ui->quantiteEdit->setText(ui->tableWidget_p_2->model()->index(row, 2).data().toString());
    ui->prixEdit->setText(ui->tableWidget_p_2->model()->index(row, 3).data().toString());
    ui->couleurEdit->setText(ui->tableWidget_p_2->model()->index(row, 4).data().toString());
    ui->epaisseurEdit->setText(ui->tableWidget_p_2->model()->index(row, 5).data().toString());
    ui->diametreEdit->setText(ui->tableWidget_p_2->model()->index(row, 6).data().toString());
    ui->idCEdit->setText(ui->tableWidget_p_2->model()->index(row, 7).data().toString());
    ui->idEEdit->setText(ui->tableWidget_p_2->model()->index(row, 8).data().toString());
    ui->idFEdit->setText(ui->tableWidget_p_2->model()->index(row, 9).data().toString());
}

void gproduit::on_modifierButton_clicked()
{
    if (selectedIdProduit <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un produit dans le tableau");
        return;
    }

    QString type = ui->typeEdit->text().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Type obligatoire");
        return;
    }

    bool ok;
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide");
        return;
    }

    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, "Erreur", "Prix invalide");
        return;
    }

    QString couleur = ui->couleurEdit->text();
    if (couleur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Couleur obligatoire");
        return;
    }

    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Épaisseur invalide");
        return;
    }

    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) {
        QMessageBox::warning(this, "Erreur", "Diamètre invalide");
        return;
    }

    int id_f = ui->idFEdit->text().toInt(&ok);
    if (!ok || id_f <= 0) {
        QMessageBox::warning(this, "Erreur", "ID fournisseur invalide");
        return;
    }

    int id_c = ui->idCEdit->text().toInt(&ok);
    if (!ok || id_c <= 0) {
        QMessageBox::warning(this, "Erreur", "ID client invalide");
        return;
    }

    int id_e = ui->idEEdit->text().toInt(&ok);
    if (!ok || id_e <= 0) {
        QMessageBox::warning(this, "Erreur", "ID employé invalide");
        return;
    }

    // Mise à jour des données
    Ptmp.setIdProduit(selectedIdProduit);
    Ptmp.setType(type);
    Ptmp.setQuantite(quantite);
    Ptmp.setPrix(prix);
    Ptmp.setCouleur(couleur);
    Ptmp.setEpaisseur(epaisseur);
    Ptmp.setDiametre(diametre);
    Ptmp.setIdClient(id_c);
    Ptmp.setIdFournisseur(id_f);
    Ptmp.setIdEmploye(id_e);

    if (Ptmp.modifier()) {
        refreshTable();
        QMessageBox::information(this, "Succès", "Produit modifié avec succès !");

        // ALERTE + SMS SI STOCK CRITIQUE APRÈS MODIFICATION
        if (quantite <= 5) {
            jouerAlerteVocale(selectedIdProduit, type, quantite);

            static QSet<int> alertesSMS;
            if (!alertesSMS.contains(selectedIdProduit)) {
                alertesSMS.insert(selectedIdProduit);
                QString sms = QString("ALERTE APRÈS MODIFICATION !\n\nProduit : %1\nID : %2\nNouvelle quantité : %3 unité(s)\n\nAction immédiate requise !\nOptiSmart")
                                  .arg(type).arg(selectedIdProduit).arg(quantite);
                envoyerSMS("+21656568218", sms);
            }
        }

        // Nettoyage complet
        ui->typeEdit->clear();
        ui->quantiteEdit->clear();
        ui->prixEdit->clear();
        ui->couleurEdit->clear();
        ui->epaisseurEdit->clear();
        ui->diametreEdit->clear();
        ui->idFEdit->clear();
        ui->idCEdit->clear();
        ui->idEEdit->clear();
        ui->idEdit->clear();
        selectedIdProduit = -1;

    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification");
    }
}
void gproduit::on_searchButton_clicked()
{
    QString textId = ui->searchIdEdit->text().trimmed();

    // Si le champ est vide → afficher tous les produits
    if (textId.isEmpty()) {
        refreshTable();
        ui->idEdit->clear();
        ui->typeEdit->clear(); // LineEdit -> clear
        ui->quantiteEdit->clear();
        ui->prixEdit->clear();
        ui->couleurEdit->clear();
        ui->epaisseurEdit->clear();
        ui->diametreEdit->clear();
        ui->idCEdit->clear();
        ui->idEEdit->clear();
        ui->idFEdit->clear();
        return;
    }

    bool ok;
    int id = textId.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM produit WHERE id_produit = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(std::move(query));  // <-- ici on utilise std::move

        ui->tableWidget_p_2->setModel(model);

        ui->idEdit->setText(model->index(0,0).data().toString());
        ui->typeEdit->setText(model->index(0,1).data().toString()); // LineEdit -> setText
        ui->quantiteEdit->setText(model->index(0,2).data().toString());
        ui->prixEdit->setText(model->index(0,3).data().toString());
        ui->couleurEdit->setText(model->index(0,4).data().toString());
        ui->epaisseurEdit->setText(model->index(0,5).data().toString());
        ui->diametreEdit->setText(model->index(0,6).data().toString());
        ui->idCEdit->setText(model->index(0,7).data().toString());
        ui->idEEdit->setText(model->index(0,8).data().toString());
        ui->idFEdit->setText(model->index(0,9).data().toString());
    } else {
        QMessageBox::warning(this, "Introuvable", "Produit non trouvé");
        refreshTable();
    }

}

void gproduit::on_statsButton_clicked()
{
    // ---------------- Récupération des statistiques ----------------
    QSqlQuery query;
    query.prepare("SELECT type, COUNT(*) FROM produit GROUP BY type");
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur",
                              "Impossible de récupérer les statistiques des produits :\n" + query.lastError().text());
        return;
    }

    QMap<QString, int> stats;
    int total = 0;

    while (query.next()) {
        QString type = query.value(0).toString().trimmed();
        int count = query.value(1).toInt();
        stats[type] = count;
        total += count;
    }

    if (total == 0) {
        QMessageBox::information(this, "Info", "Aucun produit trouvé dans la base !");
        return;
    }

    // ---------------- Création de la série (Donut Chart) ----------------
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.4); // Effet donut moderne

    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        QString typeBrut = it.key();
        int count = it.value();
        double pourcentage = (count * 100.0) / total;

        // Détermination du libellé affiché et de la couleur
        QString libelle;
        QColor couleur;

        if (typeBrut.contains("homme", Qt::CaseInsensitive)) {
            libelle = "Lunettes Homme";
            couleur = QColor("#3498db");      // Bleu masculin
        }
        else if (typeBrut.contains("femme", Qt::CaseInsensitive)) {
            libelle = "Lunettes Femme";
            couleur = QColor("#e91e63");      // Rose féminin
        }
        else if (typeBrut.contains("enfant", Qt::CaseInsensitive)) {
            libelle = "Lunettes Enfant";
            couleur = QColor("#ff9800");      // Orange vif
        }
        else if (typeBrut.contains("lentille", Qt::CaseInsensitive)) {
            libelle = "Lentilles de contact";
            couleur = QColor("#9c27b0");      // Violet
        }
        else {
            libelle = typeBrut.isEmpty() ? "Non renseigné" : typeBrut;
            couleur = QColor("#95a5a6");      // Gris par défaut
        }

        // Label complet avec nombre et pourcentage
        QString label = QString("%1 (%2) : %3%")
                            .arg(libelle)
                            .arg(count)
                            .arg(pourcentage, 0, 'f', 1);

        QPieSlice *slice = series->append(label, count);
        slice->setBrush(couleur);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelFont(QFont("Segoe UI", 9, QFont::Bold));

        // Effet hover : explosion + label toujours visible
        connect(slice, &QPieSlice::hovered, this, [slice](bool state) {
            slice->setExploded(state);
            slice->setLabelVisible(true);
        });
    }

    // ---------------- Création du graphique ----------------
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Répartition des produits par catégorie");
    chart->setTitleFont(QFont("Segoe UI", 15, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor("#185a9d")));

    // Fond transparent
    chart->setBackgroundVisible(false);
    chart->setPlotAreaBackgroundVisible(false);

    // Légende stylée
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Segoe UI", 10, QFont::Bold));
    chart->legend()->setLabelColor(QColor("#2c3e50"));

    // ---------------- Affichage dans un QDialog modal ----------------
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(650, 500);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques des Produits - Optismart");
    dialog->setModal(true);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    layout->setContentsMargins(10, 10, 10, 10);

    dialog->resize(700, 550);
    dialog->exec();

    // Nettoyage automatique grâce au parentage (this possède dialog)
}
// TRI ALPHABÉTIQUE
void gproduit::on_trierButton_clicked()
{
    // Créer un modèle avec la requête triée
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit ORDER BY type ASC");

    // Définir les noms des colonnes (en-têtes)
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Quantité");
    model->setHeaderData(3, Qt::Horizontal, "Prix");
    model->setHeaderData(4, Qt::Horizontal, "Couleur");
    model->setHeaderData(5, Qt::Horizontal, "Épaisseur");
    model->setHeaderData(6, Qt::Horizontal, "Diamètre");
    model->setHeaderData(7, Qt::Horizontal, "ID Client");
    model->setHeaderData(8, Qt::Horizontal, "ID Employé");
    model->setHeaderData(9, Qt::Horizontal, "ID Fournisseur");

    // Associer le modèle au QTableView
    ui->tableWidget_p_2->setModel(model);

    // Activer le tri par clic sur les en-têtes
    ui->tableWidget_p_2->setSortingEnabled(true);

    QMessageBox::information(this, "Tri effectué",
                             "Le tableau a été trié par type (ordre alphabétique A → Z).");
}



// FONCTION 1 : EXPORT WORD (.doc) – OFFICIEL ESPRIT – Qt 6
void gproduit::on_exportPdfButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter vers Word",
        "Liste_Produits_Optismart.doc",
        "Documents Word (*.doc)"
        );
    if (fileName.isEmpty()) return;

    QSqlQueryModel *model = Ptmp.afficher();

    // Charger le logo réel 150x150 px et convertir en Base64
    QImage logo("C:/Users/azizi/Downloads/Gproduit 2/logo.png");
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    logo.save(&buffer, "PNG");
    QString base64Image = "data:image/png;base64," + QString(byteArray.toBase64());

    QString html =
        "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></head>"
        "<body style='font-family:Times; font-size:12px; margin:0; padding:0;'>"
        // En-tête : logo à gauche, titre centré
        "<div style='width:100%; display:flex; align-items:center; padding:5px 10px;'>"
        "<img src='" + base64Image + "' style='max-width:150px; max-height:150px; margin-right:10px;' />"
                        "<h1 style='color:#1e4620; text-align:center; flex-grow:1; margin:0;'>Optismart</h1>"
                        "</div>"
                        "<p style='text-align:center; color:#2c5f34; margin:5px 0;'>Date : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>"
                                                        // Tableau
                                                        "<table border='1' cellpadding='6' width='100%' style='border-collapse:collapse;'>"
                                                        "<tr style='background-color:#1e4620; color:white; text-align:center;'>"
                                                        "<th>ID</th><th>Type</th><th>Quantité</th><th>Prix</th><th>Couleur</th>"
                                                        "<th>Épaisseur</th><th>Diamètre</th><th>ID Client</th><th>ID Employé</th><th>ID Fournisseur</th>"
                                                        "</tr>";

    for (int i = 0; i < model->rowCount(); ++i) {
        QString bgColor = (i % 2 == 0) ? "#eaf4ea" : "#ffffff"; // alternance vert clair/blanc
        html += "<tr style='background-color:" + bgColor + ";'>";
        for (int j = 0; j < model->columnCount(); ++j) {
            html += "<td>" + model->data(model->index(i, j)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table><br>"
            "<p><strong>Total : " + QString::number(model->rowCount()) + " produits</strong></p>"
                                                   "<p style='text-align:right; font-style:italic; color:#2c5f34;'>Généré par Optismart</p>"
                                                   "</body></html>";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);
        out << html;
        file.close();
        QMessageBox::information(this, "Succès", "Export Word terminé !\nOuvrez avec Microsoft Word");
    }

    delete model;
}

QImage generateQR(const QString &text, int labelSize = 200)
{
    QrCode qr = QrCode::encodeText(text.toUtf8().constData(), QrCode::Ecc::LOW);
    int size = qr.getSize();
    int margin = 4; // marge blanche autour du QR

    // Calcul de l'échelle pour que le QR tienne dans labelSize
    int scale = labelSize / (size + 2*margin);
    if (scale < 1) scale = 1; // au moins 1 px par module

    int imgSize = (size + 2*margin) * scale;
    QImage img(imgSize, imgSize, QImage::Format_RGB32);
    img.fill(Qt::white); // fond blanc

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            bool module = qr.getModule(x, y);
            QColor color = module ? Qt::black : Qt::white;
            for (int dy = 0; dy < scale; dy++)
                for (int dx = 0; dx < scale; dx++)
                    img.setPixel((x + margin) * scale + dx, (y + margin) * scale + dy, color.rgb());
        }
    }

    return img;
}

void gproduit::on_genererQrButton_clicked()
{
    if (selectedIdProduit <= 0) {
        QMessageBox::warning(this, "QR Code", "Sélectionnez un produit dans le tableau !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT type, couleur, quantite, prix FROM produit WHERE id_produit = :id");
    query.bindValue(":id", selectedIdProduit);
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Produit non trouvé !");
        return;
    }

    QString texte = QString(
                        "OPTISMART\n"
                        "ID Produit: %1\n"
                        "Type: %2\n"
                        "Couleur: %3\n"
                        "Quantité: %4\n"
                        "Prix: %5 DT"
                        )
                        .arg(selectedIdProduit)
                        .arg(query.value(0).toString())
                        .arg(query.value(1).toString())
                        .arg(query.value(2).toString())
                        .arg(query.value(3).toString());

    QImage qrImage = generateQR(texte, 200); // largeur/hauteur label 200px
    ui->qrCodeLabel->setPixmap(QPixmap::fromImage(qrImage));

    QMessageBox::information(this, "Succès",
                             "QR Code généré et scannable !");
}




void gproduit::jouerAlerteVocale(int idProduit, const QString &nomProduit, int quantite)
{
    static QSet<int> dejaAlerte;
    if (quantite > 5) { dejaAlerte.remove(idProduit); return; }
    if (dejaAlerte.contains(idProduit)) return;

    // Son
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    audio->setVolume(1.0f);
    player->setSource(QUrl("qrc:/alerte.mp3"));
    player->play();

    // Fenêtre magnifique avec emoji
    QDialog *d = new QDialog(this);
    d->setFixedSize(600,800);
    d->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    d->setAttribute(Qt::WA_DeleteOnClose);
    d->setStyleSheet(R"(
        background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
            stop:0 #667eea, stop:1 #764ba2);
        border-radius: 30px;
    )");

    QVBoxLayout *v = new QVBoxLayout(d);
    v->setContentsMargins(35,35,35,35);
    v->setSpacing(18);

    // Titre avec emoji
    QLabel *titre = new QLabel("RUPTURE DE STOCK");
    titre->setStyleSheet("color:white; font:bold 32px 'Segoe UI'; background:transparent;");
    titre->setAlignment(Qt::AlignCenter);

    // Logo + badge emoji
    QLabel *logo = new QLabel;
    logo->setPixmap(QPixmap(":/logo.png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    logo->setStyleSheet("background:rgba(255,255,255,0.2); border-radius:50px; padding:15px;");
    logo->setAlignment(Qt::AlignCenter);

    // Card produit
    QFrame *card = new QFrame;
    card->setStyleSheet("background:rgba(255,255,255,0.15); border-radius:22px;");
    QVBoxLayout *c = new QVBoxLayout(card);

    QLabel *p = new QLabel("Produit : " + nomProduit);
    p->setStyleSheet("color:#fff59d; font:bold 26px 'Segoe UI'; margin:8px;");
    p->setAlignment(Qt::AlignCenter);

    QLabel *id = new QLabel("ID : " + QString::number(idProduit));
    id->setStyleSheet("color:#bbdefb; font:18px 'Segoe UI';");
    id->setAlignment(Qt::AlignCenter);

    c->addWidget(p);
    c->addWidget(id);

    // Quantité GÉANTE + emoji feu
    QLabel *stock = new QLabel(QString::number(quantite));
    stock->setStyleSheet("color:#ff5252; font:bold 140px 'Segoe UI'; background:transparent;");
    stock->setAlignment(Qt::AlignCenter);

    QLabel *unites = new QLabel("unités restantes");
    unites->setStyleSheet("color:white; font:22px 'Segoe UI'; margin-top:-8px;");
    unites->setAlignment(Qt::AlignCenter);

    // Ligne avec emoji
    QLabel *msg = new QLabel("Réapprovisionnement IMMÉDIAT requis");
    msg->setStyleSheet("color:#ff6b6b; font:bold 22px 'Segoe UI'; margin:20px;");
    msg->setAlignment(Qt::AlignCenter);

    // Bouton stylé
    QPushButton *btn = new QPushButton("FERMER");
    btn->setFixedSize(220, 60);
    btn->setStyleSheet(R"(
        background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #ff6b6b, stop:1 #f06292);
        color:white; font:bold 24px 'Segoe UI'; border-radius:30px; border:none;
        QPushButton:hover{background:#ff5252;}
    )");
    connect(btn, &QPushButton::clicked, d, &QDialog::accept);

    // Assemblage final
    v->addWidget(titre);
    v->addSpacing(15);
    v->addWidget(logo);
    v->addSpacing(20);
    v->addWidget(card);
    v->addSpacing(30);
    v->addWidget(stock);
    v->addWidget(unites);
    v->addSpacing(10);
    v->addWidget(msg);
    v->addStretch();
    v->addWidget(btn, 0, Qt::AlignCenter);
    v->addSpacing(25);

    d->show();
    MessageBeep(MB_ICONEXCLAMATION);
    d->exec();

    dejaAlerte.insert(idProduit);
}
// FONCTION SMS TWILIO – VERSION 100% FONCTIONNELLE AVEC TON COMPTE
void gproduit::envoyerSMS(const QString &numeroDestinataire, const QString &message)
{
    const QString ACCOUNT_SID     = "";
    const QString AUTH_TOKEN      = "978ee18f7bdee06909ce5540efe15bcd";                // ← À REMPLIR
    const QString MSG_SERVICE_SID = "MGce8dd6df56372f7630a085dba368562c";

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + ACCOUNT_SID + "/Messages.json");

    QUrlQuery params;
    params.addQueryItem("To", numeroDestinataire);                    // ICI : on utilise la variable !
    params.addQueryItem("MessagingServiceSid", MSG_SERVICE_SID);
    params.addQueryItem("Body", message);

    QByteArray data = params.query().toUtf8();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString auth = ACCOUNT_SID + ":" + AUTH_TOKEN;
    request.setRawHeader("Authorization", "Basic " + auth.toUtf8().toBase64());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply, manager, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "SMS", "SMS envoyé avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur SMS", "Échec :\n" + reply->errorString());
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}
