#include "Gclient.h"
#include "ui_Gclient.h"
#include <QMessageBox>
#include "client.h"
#include "connection.h"
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
//pour stat
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QSqlQuery>
#include <QDate>
#include <QPixmap>
#include <QPainter>
#include<QColor>
#include <QTableWidgetItem>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


Gclient::Gclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gclient)
{
    qDebug() << "UI setup started";
    ui->setupUi(this);
    qDebug() << "UI setup done";
    connect(ui->tableWidget_c->horizontalHeader(), &QHeaderView::sectionClicked, this, &Gclient::recolorerToutesLesLignes);
    connect(ui->tableWidget_c, &QTableWidget::cellChanged, this, &Gclient::mettreAJourCategorie);

    // Configuration du tableWidget_c
    ui->tableWidget_c->setColumnCount(9);
    ui->tableWidget_c->setHorizontalHeaderLabels(QStringList()
                                                 << "ID Client" << "Nom" << "Prénom"
                                                 << "Date Naissance" << "Email" << "Téléphone"
                                                 << "Date Inscription" << "Points Fidélité" << "Catégorie");
    chargerClients();

    //  ajuster la taille des colonnes automatiquement
    ui->tableWidget_c->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // la connexion
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Base de données non ouverte !");
        return; // arrêt si la base n'est pas ouverte
    }



    // Afficher les clients
    afficher_client();
    //arduino
    int ret = AC.connect_arduino();

    switch(ret) {
    case 0: qDebug() << "Arduino connecté."; break;
    case 1: qDebug() << "Arduino trouvé mais impossible d'ouvrir."; break;
    case -1: qDebug() << "Arduino non détecté."; break;
    }

}

Gclient::~Gclient()
{
    delete ui;
}
void Gclient::on_bajouter_c_clicked()
{
    // Récupération des champs en QString
    QString idText = ui->lineid_c->text().trimmed();
    QString nom = ui->linenom_c->text().trimmed();
    QString prenom = ui->lineprenom_c->text().trimmed();
    QString date_naissance = ui->linedate_nais_c->text().trimmed();
    QString email = ui->lineemail_c->text().trimmed();
    QString numTelText = ui->linetel_c->text().trimmed();
    QString date_inscri = ui->linedate_inscri_c->text().trimmed();
    QString pointsText = ui->linepoints_c->text().trimmed();

    // Test de chaque champ vide
    if (idText.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir l'ID Client.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir le nom.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir le prénom.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (date_naissance.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir la date de naissance.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (email.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir l'email.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (numTelText.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir le numéro de téléphone.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (date_inscri.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir la date d'inscription.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (pointsText.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Veuillez remplir les points fidélité.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }

    // Conversion des champs numériques
    bool okId, okTel, okPoints;
    int id_client = idText.toInt(&okId);
    int num_tel = numTelText.toInt(&okTel);
    int point_fedelite = pointsText.toInt(&okPoints);

    // Vérification de la validité des nombres
    if (!okId) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ L'ID Client doit être un nombre valide.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (!okTel) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Le numéro de téléphone doit être un nombre valide.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }
    if (!okPoints) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("⚠️ Les points fidélité doivent être un nombre valide.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return;
    }

    //  Création du client et ajout
    client c(id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite);
    bool test = c.ajouter_client();

    //  Message de résultat
    if (test) {
        //refresh
        afficher_client();
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("✅ Ajouter effectué.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("❌ Ajouter non effectué.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
    int row = ui->tableWidget_c->rowCount();
    ui->tableWidget_c->insertRow(row);
    // Calculer la catégorie selon le nombre de points du client
    QString categorie = calculerCategorie(point_fedelite);

    // Créer un item pour la colonne catégorie (ici index 8 si c'est la 9ᵉ colonne)
    QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
    ui->tableWidget_c->setItem(row, 8, catItem);

    // Appliquer la couleur selon la catégorie
    colorerCategorie(catItem);

}

void Gclient::on_bsupprimer_c_clicked()
{
    int id = ui->lineid_c->text().toInt();
    client temp;
    bool test = temp.supprimer_client(id);
    // 🔹 Confirmation avant suppression
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer", "Voulez-vous vraiment supprimer ce client ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;
    if (test) {
        afficher_client(); // rafraîchir le tableau
        QMessageBox::information(this, "OK", "✅ Suppression effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Suppression non effectuée.");
    }


}
void Gclient::on_tableWidget_c_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->tableWidget_c->selectRow(row);

    for (int r = 0; r < ui->tableWidget_c->rowCount(); ++r) {
        for (int c = 0; c < ui->tableWidget_c->columnCount(); ++c) {
            if (r == row)
                ui->tableWidget_c->item(r, c)->setBackground(Qt::yellow);
            else
                ui->tableWidget_c->item(r, c)->setBackground(Qt::white);
        }
    }

    //Remplir les lineEdit avec la ligne sélectionnée
    ui->lineid_c->setText(ui->tableWidget_c->item(row,0)->text());
    ui->linenom_c->setText(ui->tableWidget_c->item(row,1)->text());
    ui->lineprenom_c->setText(ui->tableWidget_c->item(row,2)->text());
    ui->linedate_nais_c->setText(ui->tableWidget_c->item(row,3)->text());
    ui->lineemail_c->setText(ui->tableWidget_c->item(row,4)->text());
    ui->linetel_c->setText(ui->tableWidget_c->item(row,5)->text());
    ui->linedate_inscri_c->setText(ui->tableWidget_c->item(row,6)->text());
    ui->linepoints_c->setText(ui->tableWidget_c->item(row,7)->text());
}
void Gclient::on_bmodifier_c_clicked()
{
    int id_client = ui->lineid_c->text().toInt();
    QString nom = ui->linenom_c->text().trimmed();
    QString prenom = ui->lineprenom_c->text().trimmed();
    QString date_naissance = ui->linedate_nais_c->text().trimmed();
    QString email = ui->lineemail_c->text().trimmed();
    int num_tel = ui->linetel_c->text().toInt();
    QString date_inscri = ui->linedate_inscri_c->text().trimmed();
    int point_fedelite = ui->linepoints_c->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer", "Voulez-vous vraiment modifier ce client ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    client c(id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite);
    bool test = c.modifier_client(id_client, nom, prenom, date_naissance,
                                  email, num_tel, date_inscri, point_fedelite);

    if (test) {
        // Rafraîchir le tableau
        afficher_client(id_client);

        // Appliquer la couleur sur toute la ligne modifiée
        int ligne_selection = -1;
        for (int row = 0; row < ui->tableWidget_c->rowCount(); ++row) {
            if (ui->tableWidget_c->item(row, 0)->text().toInt() == id_client) {
                ligne_selection = row;
                break;
            }
        }

        if (ligne_selection != -1) {
            int points = ui->tableWidget_c->item(ligne_selection, 7)->text().toInt();
            QString categorie = calculerCategorie(points);
            QColor couleur;
            if (categorie == "VIP") couleur = QColor(144,238,144);
            else if (categorie == "Régulier") couleur = QColor(173,216,230);
            else couleur = QColor(211,211,211);

            for (int c = 0; c < ui->tableWidget_c->columnCount(); ++c) {
                ui->tableWidget_c->item(ligne_selection, c)->setBackground(couleur);
            }
        }
        afficher_client();
        QMessageBox::information(this, "Succès", "✅ Modification effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Modification non effectuée.");
    }
}


void Gclient::on_brechercher_c_clicked()
{
    bool ok;
    int id = ui->lineEdit_recherche_c->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    client c;
    QSqlQueryModel *model = c.rechercherClientParId(id);
    ui->tableWidget_c->setRowCount(0);  // vider

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Résultat", "❌ Aucun client trouvé !");
        delete model;
        return;
    }

    // Afficher la ligne trouvée
    ui->tableWidget_c->insertRow(0);

    // Calculer la catégorie
    int points = model->data(model->index(0, 7)).toInt();
    QString categorie = calculerCategorie(points);

    // Remplir les 8 premières colonnes
    for (int col = 0; col < 8; ++col) {
        ui->tableWidget_c->setItem(0, col, new QTableWidgetItem(model->data(model->index(0, col)).toString()));
    }

    // Ajouter la colonne catégorie
    QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
    ui->tableWidget_c->setItem(0, 8, catItem);

    // Appliquer la couleur à toute la ligne
    QColor couleur;
    if (categorie == "VIP")
        couleur = QColor(144, 238, 144);
    else if (categorie == "Régulier")
        couleur = QColor(173, 216, 230);
    else
        couleur = QColor(211, 211, 211);

    for (int col = 0; col < ui->tableWidget_c->columnCount(); ++col) {
        ui->tableWidget_c->item(0, col)->setBackground(couleur);
    }

    QMessageBox::information(this, "Résultat", "✅ Client trouvé !");

    delete model;
}

void Gclient::on_btrier_c_clicked()
{
    client c;
    QSqlQueryModel *model = c.trier_client();

    ui->tableWidget_c->setRowCount(0);
    for (int i = 0; i < model->rowCount(); i++) {
        ui->tableWidget_c->insertRow(i);
        for (int j = 0; j < model->columnCount(); j++) {
            ui->tableWidget_c->setItem(i, j, new QTableWidgetItem(model->data(model->index(i, j)).toString()));

        }
    }
}

void Gclient::on_bexporter_c_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (!fileName.isEmpty()) {
        client c;
        c.exporter_client_pdf(fileName);
    }
}


void Gclient::afficherStatistiques_client()
{
    client c;
    QMap<QString, int> stats = c.getStatistiquesAge();  // ← Requête propre dans client.cpp

    // On récupère les valeurs depuis le modèle (plus de SQL ici !)
    int moins25     = stats["Moins de 25 ans"];
    int entre25et40 = stats["25 - 40 ans"];
    int entre40et60 = stats["40 - 60 ans"];
    int plus60      = stats["Plus de 60 ans"];

    QPieSeries *series = new QPieSeries();
    series->append("Moins de 25 ans", moins25);
    series->append("25 - 40 ans", entre25et40);
    series->append("40 - 60 ans", entre40et60);
    series->append("Plus de 60 ans", plus60);

    // Ton style actuel (tu le gardes à 100%)
    for (auto slice : series->slices())
        slice->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients selon leur âge");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoyage propre de l'ancien graphique
    QLayout *layout = ui->chartContainer->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->chartContainer);
    } else {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    layout->addWidget(chartView);
    ui->chartContainer->setLayout(layout);
}


void Gclient::on_bstatistique_c_clicked()
{
    afficherStatistiques_client();
}
//categorie

QString Gclient::calculerCategorie(int points)
{
    if (points > 500)
        return "VIP";
    else if (points >= 100)
        return "Régulier";
    else
        return "Nouveau";
}

void Gclient::colorerCategorie(QTableWidgetItem *item)
{
    if (!item) return;

    if (item->text() == "VIP") {
        item->setBackground(QColor(144, 238, 144)); // vert clair
    } else if (item->text() == "Régulier") {
        item->setBackground(QColor(173, 216, 230)); // bleu clair
    } else if (item->text() == "Nouveau") {
        item->setBackground(QColor(211, 211, 211)); // gris clair
    }
}


//model
void Gclient::afficher_client(int id_selectionne)
{
    client c;
    QSqlQueryModel *model = c.afficherTousClients();

    ui->tableWidget_c->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget_c->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget_c->setItem(row, col, new QTableWidgetItem(data));
        }

        // Colonne 8 : Catégorie
        int points = model->data(model->index(row, 7)).toInt();
        QString categorie = calculerCategorie(points);
        QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
        ui->tableWidget_c->setItem(row, 8, catItem);

        // Couleur de ligne
        QColor couleur = (categorie == "VIP") ? QColor(144,238,144) :
                             (categorie == "Régulier") ? QColor(173,216,230) :
                             QColor(211,211,211);

        for (int col = 0; col < 9; ++col)
            ui->tableWidget_c->item(row, col)->setBackground(couleur);
    }
    // activer tri et désactiver alternance automatique
    ui->tableWidget_c->setSortingEnabled(true);
    ui->tableWidget_c->setAlternatingRowColors(false);

    delete model; // important
}


void Gclient::chargerClients()
{
    QSqlQuery query;
    query.prepare("SELECT id, nom, prenom, date_naissance, email, telephone, date_inscription, points_fidelite FROM clients");

    if(!query.exec()) {
        qDebug() << "Erreur lors de la récupération des clients:" << query.lastError();
        return;
    }

    int row = 0;
    while(query.next()) {
        ui->tableWidget_c->insertRow(row);
        for (int col = 0; col < 8; ++col) { // les 8 colonnes de la base
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget_c->setItem(row, col, item);
        }

        // Calculer la catégorie selon les points fidélité (colonne 7)
        int points = query.value(7).toInt();
        QString categorie = calculerCategorie(points);

        QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
        ui->tableWidget_c->setItem(row, 8, catItem);
        colorerCategorie(catItem);

        row++;
    }
}
void Gclient::on_tableWidget_c_cellChanged(int row, int column)
{
    // Si ce n’est PAS la colonne des points → ne rien faire
    if (column != 7) return;

    // Récupérer les nouveaux points
    int points = ui->tableWidget_c->item(row, 7)->text().toInt();

    // Recalculer la catégorie
    QString categorie = calculerCategorie(points);

    // Mettre à jour la colonne catégorie (col 8)
    QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
    ui->tableWidget_c->setItem(row, 8, catItem);

    // Appliquer la couleur
    colorerCategorie(catItem);
}
void Gclient::on_tableWidget_c_horizontalHeader_sectionClicked(int column)
{
    // Qt trie automatiquement → NOUS devons juste corriger les couleurs

    for (int row = 0; row < ui->tableWidget_c->rowCount(); row++)
    {
        // Lire les points (colonne 7)
        int points = ui->tableWidget_c->item(row, 7)->text().toInt();

        // Recalculer la catégorie
        QString categorie = calculerCategorie(points);

        // Mettre dans colonne 8
        QTableWidgetItem *catItem = new QTableWidgetItem(categorie);
        ui->tableWidget_c->setItem(row, 8, catItem);

        // Recolorer
        colorerCategorie(catItem);
    }
}
void Gclient::mettreAJourCategorie(int row, int col)
{
    if (col != 7) return; // ne traiter que la colonne "points"

    ui->tableWidget_c->blockSignals(true); // Bloquer les signals pour éviter boucle

    int points = ui->tableWidget_c->item(row, 7)->text().toInt();

    QString categorie;
    QColor couleur;

    if (points >= 500) { categorie = "VIP"; couleur = QColor(144,238,144); }
    else if (points >= 100) { categorie = "Régulier"; couleur = QColor(173,216,230); }
    else { categorie = "Nouveau"; couleur = QColor(211,211,211); }

    ui->tableWidget_c->item(row, 8)->setText(categorie);
    //  Appliquer la couleur sur toute la ligne
    for (int c = 0; c < ui->tableWidget_c->columnCount(); ++c)
        ui->tableWidget_c->item(row, c)->setBackground(couleur);

    ui->tableWidget_c->blockSignals(false);
}

void Gclient::recolorerToutesLesLignes()
{
    for (int row = 0; row < ui->tableWidget_c->rowCount(); row++)
    {
        int points = ui->tableWidget_c->item(row, 7)->text().toInt();

        QString categorie;
        QColor couleur;

        if (points >= 500) { categorie = "VIP"; couleur = QColor(144,238,144); }
        else if (points >= 100) { categorie = "Régulier"; couleur = QColor(173,216,230); }
        else { categorie = "Nouveau"; couleur = QColor(211,211,211); }

        ui->tableWidget_c->item(row, 8)->setText(categorie);

        for (int col = 0; col < ui->tableWidget_c->columnCount(); col++) {
            ui->tableWidget_c->item(row, col)->setBackground(couleur);
        }
    }
}











/*void Gclient::on_lineEdit_id_textChanged(const QString &arg1)
{
    bool ok;
    int id_client = arg1.toInt(&ok);

    if(!ok || id_client <= 0)
        return; // éviter les erreurs

    QSqlQuery query;
    query.prepare("SELECT nom, points FROM client WHERE id = :id");
    query.bindValue(":id", id_client);
    query.exec();

    if(query.next())
    {
        QString nom = query.value("nom").toString();
        int points = query.value("points").toInt();

        QString msg = "NOM:" + nom + ";POINTS:" + QString::number(points) + "\n";

        AC.write_to_arduino(msg.toUtf8());

        qDebug() << "Envoyé à Arduino :" << msg;
    }
}*/
/*void Gclient::on_lineEdit_id_textChanged(const QString &arg1)
{
    bool ok;
    int id_client = arg1.toInt(&ok);

    if (!ok || id_client <= 0)
        return; // éviter erreurs si vide ou non-numérique

    QSqlQuery query;
    query.prepare("SELECT nom, point_fedelite FROM client WHERE id = :id");
    query.bindValue(":id", id_client);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError();
        return;
    }

    if (query.next()) {
        QString nom = query.value("nom").toString();
        int points = query.value("point_fidelite").toInt();

        // Format attendu par Arduino : NOM|POINTS
        QString message = nom + "|" + QString::number(points) + "\n";

        AC.write_to_arduino(message.toUtf8());

        qDebug() << "Envoyé à Arduino :" << message;
    }
}*/
//grock marche 100%
/*void Gclient::on_lineEdit_id_textChanged(const QString &arg1)
{
    bool ok;
    int id_client = arg1.toInt(&ok);
    if (!ok || id_client <= 0)
        return;

    QSqlQuery query;
    // Attention aux vrais noms des colonnes dans ta table Oracle !
    query.prepare("SELECT NOM, POINT_FEDELITE FROM client WHERE ID_CLIENT = :id");

    query.bindValue(":id", id_client);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        qDebug() << "Requête exécutée :" << query.lastQuery();
        qDebug() << "Valeurs bindées : id =" << id_client;
        return;
    }

    if (query.next()) {
        QString nom = query.value("NOM").toString();           // ou query.value(0)
        int points = query.value("POINT_FEDELITE").toInt();    // ou query.value(1)

        QString message = nom + "|" + QString::number(points) + "\n";
        AC.write_to_arduino(message.toUtf8());
        qDebug() << "Envoyé à Arduino :" << message;
    } else {
        qDebug() << "Aucun client trouvé avec ID_CLIENT =" << id_client;
    }
}*/
//sans requette
void Gclient::on_lineEdit_id_textChanged(const QString &arg1)
{
    bool ok;
    int id_client = arg1.toInt(&ok);
    if (!ok || id_client <= 0)
        return;

    // Utilisation de la classe client
    client c;
    QPair<QString, int> resultat = c.rechercherNomEtPointsParId(id_client);

    QString nom = resultat.first;
    int points = resultat.second;

    // Si le client n'existe pas → on peut envoyer un message clair à l'Arduino
    if (nom == "INCONNU") {
        QString message = "ERREUR|0\n";  // ou "CLIENT INEXISTANT|0\n"
        AC.write_to_arduino(message.toUtf8());
        qDebug() << "Client non trouvé pour ID:" << id_client;
        return;
    }

    // Format : NOM|POINTS\n
    QString message = nom + "|" + QString::number(points) + "\n";
    AC.write_to_arduino(message.toUtf8());
    qDebug() << "Envoyé à Arduino :" << message;
}




