
#include "gproduit.h"
#include "ui_gproduit.h"
#include "produit.h"
#include "arduino_produit.h"
#include <QSqlError>    // nécessaire pour query.lastError()
#include <QSqlDriver>
#include <QTimer>//
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>  // même si pas utilisé directem← Obligatoire ici aussi !

#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QDate>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <windows.h>
#include "qrcodegen.hpp"
#include <QPrinter>
#include <QPageSize>
#include <QPagedPaintDevice>


using qrcodegen::QrCode;

gproduit::gproduit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gproduit)
    , Ptmp()
    , selectedIdProduit(-1)
{
    ui->setupUi(this);
    connect(&arduinoProduit, &arduino_produit::carteDetectee, this, &gproduit::onCarteDetectee);


    ui->typeEdit->setPlaceholderText("Ex: Lunettes Homme / Femme / Enfant / Lentilles");
    refreshTable();
}

gproduit::~gproduit()
{
    delete ui;
}

void gproduit::refreshTable()
{
    ui->tableWidget_p_2->setModel(Ptmp.afficher());
    ui->tableWidget_p_2->setSortingEnabled(true);
}

/* ==================== AJOUTER ==================== */
void gproduit::on_ajouterButton_clicked()
{
    QString type = ui->typeEdit->text().trimmed();
    if (type.isEmpty()) { QMessageBox::warning(this, tr("Erreur"), tr("Veuillez saisir un type")); return; }

    bool ok;
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) { QMessageBox::warning(this, "Erreur", "Quantité invalide"); return; }

    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) { QMessageBox::warning(this, "Erreur", "Prix invalide"); return; }

    QString couleur = ui->couleurEdit->text().trimmed();
    if (couleur.isEmpty()) { QMessageBox::warning(this, "Erreur", "Couleur obligatoire"); return; }

    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok || epaisseur < 0) { QMessageBox::warning(this, "Erreur", "Épaisseur invalide"); return; }

    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) { QMessageBox::warning(this, "Erreur", "Diamètre invalide"); return; }

    int id_produit = ui->idEdit->text().trimmed().toInt(&ok);
    if (!ui->idEdit->text().isEmpty() && !ok) { QMessageBox::warning(this, "Erreur", "ID invalide"); return; }

    int id_fournisseur = ui->idFEdit->text().trimmed().toInt(&ok);
    if (!ok || id_fournisseur <= 0) { QMessageBox::warning(this, "Erreur", "ID fournisseur invalide"); return; }

    int id_client = ui->idCEdit->text().trimmed().toInt(&ok);
    if (!ok || id_client <= 0) { QMessageBox::warning(this, "Erreur", "ID client invalide"); return; }

    int id_employe = ui->idEEdit->text().trimmed().toInt(&ok);
    if (!ok || id_employe <= 0) { QMessageBox::warning(this, "Erreur", "ID employé invalide"); return; }

    // Préparation
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

    if (Ptmp.ajouter()) {
        refreshTable();
        int nouvelId = Ptmp.getLastInsertedId();
        if (nouvelId > 0) selectedIdProduit = nouvelId;

        QMessageBox::information(this, "Succès", "Produit ajouté avec succès !");

        if (quantite <= 5) {
            jouerAlerteVocale(nouvelId > 0 ? nouvelId : id_produit, type, quantite);
            static QSet<int> alertesSMS;
            if (!alertesSMS.contains(nouvelId)) {
                alertesSMS.insert(nouvelId);
                QString sms = QString("ALERTE STOCK CRITIQUE !\n\nProduit ajouté : %1\nID : %2\nQuantité : %3 unité(s)\n\nRéapprovisionnement URGENT !\nOptiSmart")
                                  .arg(type).arg(nouvelId).arg(quantite);
                envoyerSMS("+21656568218", sms);
            }
        }

        // Vider les champs
        ui->idEdit->clear(); ui->typeEdit->clear(); ui->quantiteEdit->clear(); ui->prixEdit->clear();
        ui->couleurEdit->clear(); ui->epaisseurEdit->clear(); ui->diametreEdit->clear();
        ui->idFEdit->clear(); ui->idCEdit->clear(); ui->idEEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l’ajout dans la base de données");
    }
}

/* ==================== SUPPRIMER ==================== */
void gproduit::on_supprimerButton_clicked()
{
    bool ok;
    int id = ui->idEdit->text().toInt(&ok);
    if (!ok || id <= 0) { QMessageBox::warning(this, "Erreur", "ID invalide"); return; }

    if (Ptmp.supprimer(id)) {
        refreshTable();
        QMessageBox::information(this, "Succès", "Produit supprimé");
        ui->idEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression échouée");
    }
}

/* ==================== DOUBLE CLIC TABLEAU ==================== */
void gproduit::on_tableWidget_p_2_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    selectedIdProduit = ui->tableWidget_p_2->model()->index(row, 0).data().toInt();

    ui->idEdit->setText(ui->tableWidget_p_2->model()->index(row, 0).data().toString());
    ui->typeEdit->setText(ui->tableWidget_p_2->model()->index(row, 1).data().toString());
    ui->quantiteEdit->setText(ui->tableWidget_p_2->model()->index(row, 2).data().toString());
    ui->prixEdit->setText(ui->tableWidget_p_2->model()->index(row, 3).data().toString());
    ui->couleurEdit->setText(ui->tableWidget_p_2->model()->index(row, 4).data().toString());
    ui->epaisseurEdit->setText(ui->tableWidget_p_2->model()->index(row, 5).data().toString());
    ui->diametreEdit->setText(ui->tableWidget_p_2->model()->index(row, 6).data().toString());
    ui->idCEdit->setText(ui->tableWidget_p_2->model()->index(row, 7).data().toString());
    ui->idEEdit->setText(ui->tableWidget_p_2->model()->index(row, 8).data().toString());
    ui->idFEdit->setText(ui->tableWidget_p_2->model()->index(row, 9).data().toString());
}

/* ==================== MODIFIER ==================== */
void gproduit::on_modifierButton_clicked()
{
    if (selectedIdProduit <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un produit dans le tableau");
        return;
    }

    QString type = ui->typeEdit->text().trimmed();
    if (type.isEmpty()) { QMessageBox::warning(this, "Erreur", "Type obligatoire"); return; }

    bool ok;
    int quantite = ui->quantiteEdit->text().toInt(&ok);
    if (!ok || quantite <= 0) { QMessageBox::warning(this, "Erreur", "Quantité invalide"); return; }

    float prix = ui->prixEdit->text().toFloat(&ok);
    if (!ok || prix <= 0) { QMessageBox::warning(this, "Erreur", "Prix invalide"); return; }

    QString couleur = ui->couleurEdit->text();
    if (couleur.isEmpty()) { QMessageBox::warning(this, "Erreur", "Couleur obligatoire"); return; }

    float epaisseur = ui->epaisseurEdit->text().toFloat(&ok);
    if (!ok) { QMessageBox::warning(this, "Erreur", "Épaisseur invalide"); return; }

    float diametre = ui->diametreEdit->text().toFloat(&ok);
    if (!ok || diametre <= 0) { QMessageBox::warning(this, "Erreur", "Diamètre invalide"); return; }

    int id_f = ui->idFEdit->text().toInt(&ok);
    if (!ok || id_f <= 0) { QMessageBox::warning(this, "Erreur", "ID fournisseur invalide"); return; }

    int id_c = ui->idCEdit->text().toInt(&ok);
    if (!ok || id_c <= 0) { QMessageBox::warning(this, "Erreur", "ID client invalide"); return; }

    int id_e = ui->idEEdit->text().toInt(&ok);
    if (!ok || id_e <= 0) { QMessageBox::warning(this, "Erreur", "ID employé invalide"); return; }

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

        // Nettoyage
        ui->typeEdit->clear(); ui->quantiteEdit->clear(); ui->prixEdit->clear();
        ui->couleurEdit->clear(); ui->epaisseurEdit->clear(); ui->diametreEdit->clear();
        ui->idFEdit->clear(); ui->idCEdit->clear(); ui->idEEdit->clear();
        ui->idEdit->clear();
        selectedIdProduit = -1;
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification");
    }
}

/* ==================== RECHERCHE PAR ID ==================== */
void gproduit::on_searchButton_clicked()
{
    QString text = ui->searchIdEdit->text().trimmed();
    if (text.isEmpty()) {
        refreshTable();
        return;
    }

    bool ok;
    int id = text.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide");
        return;
    }

    QSqlQueryModel* model = Ptmp.rechercherParId(id);
    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Introuvable", "Produit non trouvé");
        delete model;
        refreshTable();
        return;
    }

    ui->tableWidget_p_2->setModel(model);

    // Remplir les champs
    ui->idEdit->setText(model->data(model->index(0,0)).toString());
    ui->typeEdit->setText(model->data(model->index(0,1)).toString());
    ui->quantiteEdit->setText(model->data(model->index(0,2)).toString());
    ui->prixEdit->setText(model->data(model->index(0,3)).toString());
    ui->couleurEdit->setText(model->data(model->index(0,4)).toString());
    ui->epaisseurEdit->setText(model->data(model->index(0,5)).toString());
    ui->diametreEdit->setText(model->data(model->index(0,6)).toString());
    ui->idCEdit->setText(model->data(model->index(0,7)).toString());
    ui->idEEdit->setText(model->data(model->index(0,8)).toString());
    ui->idFEdit->setText(model->data(model->index(0,9)).toString());
}

/* ==================== STATISTIQUES ==================== */
void gproduit::on_statsButton_clicked()
{
    QSqlQuery query = Ptmp.getStatsByType();
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

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.4);

    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        QString typeBrut = it.key();
        int count = it.value();
        double pourcentage = (count * 100.0) / total;

        QString libelle = typeBrut;
        QColor couleur = QColor("#95a5a6");

        if (typeBrut.contains("homme", Qt::CaseInsensitive)) { libelle = "Lunettes Homme"; couleur = QColor("#3498db"); }
        else if (typeBrut.contains("femme", Qt::CaseInsensitive)) { libelle = "Lunettes Femme"; couleur = QColor("#e91e63"); }
        else if (typeBrut.contains("enfant", Qt::CaseInsensitive)) { libelle = "Lunettes Enfant"; couleur = QColor("#ff9800"); }
        else if (typeBrut.contains("lentille", Qt::CaseInsensitive)) { libelle = "Lentilles"; couleur = QColor("#9c27b0"); }

        QString label = QString("%1 (%2) : %3%").arg(libelle).arg(count).arg(pourcentage, 0, 'f', 1);
        QPieSlice *slice = series->append(label, count);
        slice->setBrush(couleur);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelFont(QFont("Segoe UI", 9, QFont::Bold));
        connect(slice, &QPieSlice::hovered, this, [slice](bool state) {
            slice->setExploded(state);
            slice->setLabelVisible(true);
        });
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des produits par catégorie");
    chart->setTitleFont(QFont("Segoe UI", 15, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor("#185a9d")));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Segoe UI", 10, QFont::Bold));
    chart->setBackgroundVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques - OptiSmart");
    dialog->setModal(true);
    dialog->resize(700, 550);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->exec();
}

/* ==================== TRI ==================== */
void gproduit::on_trierButton_clicked()
{
    ui->tableWidget_p_2->setModel(Ptmp.trierParType());
    QMessageBox::information(this, "Tri", "Tableau trié par type (A → Z)");
}

/* ==================== EXPORT WORD ==================== */
void gproduit::on_exportPdfButton_clicked()
{
    // Demander où sauvegarder le PDF
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/liste_produits.pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    // Récupérer les données des produits
    QSqlQueryModel *model = Ptmp.afficher();
    if (!model) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les produits.");
        return;
    }

    // Créer le document PDF
    QTextDocument document;

    // Construire le contenu HTML simple (exactement comme les fournisseurs)
    QString htmlContent;
    htmlContent += "<html><body>";
    htmlContent += "<h1 align='center'>LISTE DES PRODUITS</h1>";
    htmlContent += "<p align='center'><i>Exporté le: " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</i></p>";
    htmlContent += "<table border='1' cellpadding='5' width='100%'>";
    htmlContent += "<tr style='background-color: #f0f0f0; font-weight: bold;'>";
    htmlContent += "<th>ID Produit</th><th>Type</th><th>Quantité</th><th>Prix</th><th>Couleur</th>";
    htmlContent += "<th>Épaisseur</th><th>Diamètre</th><th>ID Client</th><th>ID Employé</th><th>ID Fournisseur</th>";
    htmlContent += "</tr>";

    // Remplir avec les données du modèle
    for (int row = 0; row < model->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();
            htmlContent += "<td>" + text + "</td>";
        }
        htmlContent += "</tr>";
    }

    htmlContent += "</table>";
    htmlContent += "<p><br>Total produits: " + QString::number(model->rowCount()) + "</p>";
    htmlContent += "</body></html>";

    // Appliquer le HTML au document
    document.setHtml(htmlContent);

    // Générer le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));

    document.print(&printer);

    // Nettoyage
    delete model;

    // Message de succès
    QMessageBox::information(this, "Export PDF",
                             "Liste exportée en PDF avec succès!\nFichier: " + fileName);
}

/* ==================== QR CODE ==================== */
QImage generateQR(const QString &text, int size = 200)
{
    QrCode qr = QrCode::encodeText(text.toUtf8().constData(), QrCode::Ecc::LOW);
    int s = qr.getSize();
    int margin = 4;
    int scale = size / (s + 2 * margin);
    if (scale < 1) scale = 1;
    int imgSize = (s + 2 * margin) * scale;

    QImage img(imgSize, imgSize, QImage::Format_RGB32);
    img.fill(Qt::white);
    for (int y = 0; y < s; ++y)
        for (int x = 0; x < s; ++x)
            if (qr.getModule(x, y)) {
                QColor c = Qt::black;
                for (int dy = 0; dy < scale; ++dy)
                    for (int dx = 0; dx < scale; ++dx)
                        img.setPixel((x + margin) * scale + dx, (y + margin) * scale + dy, c.rgb());
            }
    return img;
}

void gproduit::on_genererQrButton_clicked()
{
    if (selectedIdProduit <= 0) {
        QMessageBox::warning(this, "QR Code", "Sélectionnez un produit !");
        return;
    }

    QSqlQuery q = Ptmp.getProduitForQR(selectedIdProduit);
    if (!q.next()) {
        QMessageBox::critical(this, "Erreur", "Produit non trouvé");
        return;
    }

    QString texte = QString("OPTISMART\nID Produit: %1\nType: %2\nCouleur: %3\nQuantité: %4\nPrix: %5 DT")
                        .arg(selectedIdProduit)
                        .arg(q.value(0).toString())
                        .arg(q.value(1).toString())
                        .arg(q.value(2).toString())
                        .arg(q.value(3).toString());

    ui->qrCodeLabel->setPixmap(QPixmap::fromImage(generateQR(texte, 200)));
    QMessageBox::information(this, "Succès", "QR Code généré !");
}

/* ==================== ALERTE VOCALE ==================== */
void gproduit::jouerAlerteVocale(int idProduit, const QString &nomProduit, int quantite)
{
    static QSet<int> dejaAlerte;
    if (quantite > 5) { dejaAlerte.remove(idProduit); return; }
    if (dejaAlerte.contains(idProduit)) return;

    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    audio->setVolume(1.0);
    player->setSource(QUrl("qrc:/alerte.mp3"));
    player->play();

    QDialog *d = new QDialog(this);
    d->setFixedSize(600, 800);
    d->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    d->setAttribute(Qt::WA_DeleteOnClose);
    d->setStyleSheet("background: qlineargradient(x1:0,y1:0,x2:0,y2:1, stop:0 #667eea, stop:1 #764ba2); border-radius:30px;");

    QVBoxLayout *v = new QVBoxLayout(d);
    v->setContentsMargins(35,35,35,35);
    v->setSpacing(18);

    QLabel *titre = new QLabel("RUPTURE DE STOCK");
    titre->setStyleSheet("color:white; font:bold 32px 'Segoe UI';");
    titre->setAlignment(Qt::AlignCenter);

    QLabel *logo = new QLabel;
    logo->setPixmap(QPixmap(":/logo.png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    logo->setStyleSheet("background:rgba(255,255,255,0.2); border-radius:50px; padding:15px;");
    logo->setAlignment(Qt::AlignCenter);

    QFrame *card = new QFrame;
    card->setStyleSheet("background:rgba(255,255,255,0.15); border-radius:22px;");
    QVBoxLayout *c = new QVBoxLayout(card);
    QLabel *p = new QLabel("Produit : " + nomProduit);
    p->setStyleSheet("color:#fff59d; font:bold 26px 'Segoe UI';");
    p->setAlignment(Qt::AlignCenter);
    QLabel *id = new QLabel("ID : " + QString::number(idProduit));
    id->setStyleSheet("color:#bbdefb; font:18px 'Segoe UI';");
    id->setAlignment(Qt::AlignCenter);
    c->addWidget(p); c->addWidget(id);

    QLabel *stock = new QLabel(QString::number(quantite));
    stock->setStyleSheet("color:#ff5252; font:bold 140px 'Segoe UI';");
    stock->setAlignment(Qt::AlignCenter);
    QLabel *unites = new QLabel("unités restantes");
    unites->setStyleSheet("color:white; font:22px 'Segoe UI'; margin-top:-8px;");
    unites->setAlignment(Qt::AlignCenter);

    QLabel *msg = new QLabel("Réapprovisionnement IMMÉDIAT requis");
    msg->setStyleSheet("color:#ff6b6b; font:bold 22px 'Segoe UI';");
    msg->setAlignment(Qt::AlignCenter);

    QPushButton *btn = new QPushButton("FERMER");
    btn->setFixedSize(220, 60);
    btn->setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #ff6b6b, stop:1 #f06292);"
                       "color:white; font:bold 24px 'Segoe UI'; border-radius:30px;");
    connect(btn, &QPushButton::clicked, d, &QDialog::accept);

    v->addWidget(titre); v->addSpacing(15); v->addWidget(logo); v->addSpacing(20);
    v->addWidget(card); v->addSpacing(30); v->addWidget(stock); v->addWidget(unites);
    v->addSpacing(10); v->addWidget(msg); v->addStretch(); v->addWidget(btn, 0, Qt::AlignCenter);
    v->addSpacing(25);

    d->show();
    MessageBeep(MB_ICONEXCLAMATION);
    d->exec();
    dejaAlerte.insert(idProduit);
}

/* ==================== SMS TWILIO ==================== */
void gproduit::envoyerSMS(const QString &numeroDestinataire, const QString &message)
{
    const QString ACCOUNT_SID = "";
    const QString AUTH_TOKEN = "";
    const QString MSG_SERVICE_SID = "MGce8dd6df56372f7630a085dba368562c";

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + ACCOUNT_SID + "/Messages.json");
    QUrlQuery params;
    params.addQueryItem("To", numeroDestinataire);
    params.addQueryItem("MessagingServiceSid", MSG_SERVICE_SID);
    params.addQueryItem("Body", message);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QString auth = ACCOUNT_SID + ":" + AUTH_TOKEN;
    request.setRawHeader("Authorization", "Basic " + auth.toUtf8().toBase64());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    connect(reply, &QNetworkReply::finished, this, [reply, manager, this]() {
        if (reply->error() == QNetworkReply::NoError)
            QMessageBox::information(this, "SMS", "SMS envoyé !");
        else
            QMessageBox::warning(this, "Erreur SMS", reply->errorString());
        reply->deleteLater();
        manager->deleteLater();
    });
}
void gproduit::onCarteDetectee(const QString &uid) {
    QString rfid = uid.trimmed().toUpper();
    if (rfid.length() != 8) return;

    produit p;

    // Récupérer les infos du produit via RFID
    QMap<QString, QVariant> prod = p.getProduitInfoByRFID(rfid);

    if (!prod.value("found").toBool()) {
        QMessageBox::information(this, "Carte inconnue",
                                 "Produit non enregistré\nUID : " + rfid);
        return;
    }

    // Récupérer les 3 informations
    QString couleur = prod["couleur"].toString();
    QString type = prod["type"].toString();
    double prix = prod["prix"].toDouble();

    // Création de la fenêtre QDialog
    QDialog *d = new QDialog(this);
    d->setFixedSize(550, 400);  // Plus grande pour afficher 3 infos
    d->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    d->setAttribute(Qt::WA_DeleteOnClose);

    // Style avec dégradé
    d->setStyleSheet(
        "QDialog {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "  stop:0 #1e3a5f, stop:1 #0f172a);"
        "  border-radius: 20px;"
        "  color: white;"
        "}"
        );

    QVBoxLayout *layout = new QVBoxLayout(d);
    layout->setContentsMargins(40, 30, 40, 30);
    layout->setSpacing(20);

    // Titre
    QLabel *titre = new QLabel("🕶️ LUNETTE DÉTECTÉE");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font: bold 28px 'Segoe UI'; color: #00e676;");
    layout->addWidget(titre);

    // --- COULEUR ---
    QLabel *couleurLabel = new QLabel("Couleur : " + couleur);
    couleurLabel->setAlignment(Qt::AlignCenter);
    couleurLabel->setStyleSheet(
        "font: bold 20px;"
        "color: #e0f2fe;"
        "background: rgba(0,230,118,0.2);"
        "padding: 10px;"
        "border-radius: 12px;"
        "border: 2px solid #00e676;"
        );
    layout->addWidget(couleurLabel);

    // --- TYPE ---
    QLabel *typeLabel = new QLabel("Type : " + type);
    typeLabel->setAlignment(Qt::AlignCenter);
    typeLabel->setStyleSheet(
        "font: bold 15px;"
        "color: #e0f2fe;"
        "background: rgba(96,165,250,0.2);"
        "padding: 10px;"
        "border-radius: 10px;"
        "border: 2px solid #60a5fa;"
        );
    layout->addWidget(typeLabel);

    // --- PRIX ---
    QLabel *prixLabel = new QLabel(QString("Prix : %1 DT").arg(prix, 0, 'f', 2));
    prixLabel->setAlignment(Qt::AlignCenter);
    prixLabel->setStyleSheet(
        "font: bold 24px;"
        "color: #ffd700;"
        "background: rgba(255,215,0,0.15);"
        "padding: 15px;"
        "border-radius: 12px;"
        "border: 2px solid #ffd700;"
        );
    layout->addWidget(prixLabel);

    // Affichage du numéro de carte RFID
    QLabel *carteLabel = new QLabel("📇 Carte : " + rfid);
    carteLabel->setAlignment(Qt::AlignCenter);
    carteLabel->setStyleSheet("font: 14px; color: #94a3b8; margin-top: 10px;");
    layout->addWidget(carteLabel);

    // Bouton Fermer
    QPushButton *okButton = new QPushButton("✓ Fermer");
    okButton->setFixedSize(220, 50);
    okButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #1e40af;"
        "  color: white;"
        "  font: bold 18px;"
        "  border-radius: 25px;"
        "  border: 3px solid #60a5fa;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2563eb;"
        "}"
        );
    connect(okButton, &QPushButton::clicked, d, &QDialog::close);
    layout->addWidget(okButton, 0, Qt::AlignCenter);

    // Animation sur le prix (car c'est l'info importante)
    QPropertyAnimation *zoom = new QPropertyAnimation(prixLabel, "geometry");
    QRect start = prixLabel->geometry();
    QRect big = start.adjusted(-15, -8, 15, 8);
    zoom->setDuration(700);
    zoom->setStartValue(start);
    zoom->setKeyValueAt(0.5, big);
    zoom->setEndValue(start);
    zoom->setEasingCurve(QEasingCurve::OutElastic);
    zoom->start(QAbstractAnimation::DeleteWhenStopped);

    d->exec();
}
