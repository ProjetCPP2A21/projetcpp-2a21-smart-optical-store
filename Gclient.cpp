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
Gclient::Gclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gclient)
{
    ui->setupUi(this);
    //stat
    /*QFont font("MS Serif", 9);
    font.setStyle(QFont::StyleNormal);
    ui->afficestat_c->setFont(font);
    connect(ui->tableWidget_c, &QTablechartContainer::cellClicked,
            this, &Gclient::on_tableWidget_c_cellClicked);*/


    // 🔹 Créer la connexion
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Base de données non ouverte !");
        return; // arrêt si la base n'est pas ouverte
    }

    // 🔹 Configurer le tableau
    ui->tableWidget_c->setColumnCount(8);
    ui->tableWidget_c->setHorizontalHeaderLabels(QStringList() << "ID Client" << "Nom" << "Prénom"
                                                               << "Date Naissance" << "Email" << "Téléphone" << "Date Inscription" << "Points Fidélité");

    // 🔹 Afficher les clients
    afficher_client();
}

Gclient::~Gclient()
{
    delete ui;
}
void Gclient::on_bajouter_c_clicked()
{
    // 🔹 Récupération des champs en QString
    QString idText = ui->lineid_c->text().trimmed();
    QString nom = ui->linenom_c->text().trimmed();
    QString prenom = ui->lineprenom_c->text().trimmed();
    QString date_naissance = ui->linedate_nais_c->text().trimmed();
    QString email = ui->lineemail_c->text().trimmed();
    QString numTelText = ui->linetel_c->text().trimmed();
    QString date_inscri = ui->linedate_inscri_c->text().trimmed();
    QString pointsText = ui->linepoints_c->text().trimmed();

    // 🔹 Test de chaque champ vide
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

    // 🔹 Conversion des champs numériques
    bool okId, okTel, okPoints;
    int id_client = idText.toInt(&okId);
    int num_tel = numTelText.toInt(&okTel);
    int point_fedelite = pointsText.toInt(&okPoints);

    // 🔹 Vérification de la validité des nombres
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

    // 🔹 Création du client et ajout
    client c(id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite);
    bool test = c.ajouter_client();

    // 🔹 Message de résultat
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
}
/*void Gclient::on_bsupprimer_c_clicked()
{
    int id =ui->lineid_c->text().toInt();
    bool test = c.supprimer_client(id);
    if (test) {
        //refresh
        afficher_client();
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("✅ suppression effectué.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("❌ suppression non effectué.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }


}*/
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

/*void Gclient::afficher_client()
{
    ui->tableWidget_c->setRowCount(0); // vider la table

    QSqlQuery query("SELECT id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite FROM client");

    int row = 0;
    while (query.next()) {
        ui->tableWidget_c->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget_c->setItem(row, col, item);
        }

        row++;}
}*/
void Gclient::afficher_client(int id_selectionne)
{
    ui->tableWidget_c->setRowCount(0);

    QSqlQuery query("SELECT id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite FROM client");

    int row = 0;
    int ligne_selection = -1;

    while (query.next()) {
        ui->tableWidget_c->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget_c->setItem(row, col, item);
        }

        if (query.value(0).toInt() == id_selectionne)
            ligne_selection = row;

        row++;
    }

    // Surligner la ligne modifiée
    for (int r = 0; r < ui->tableWidget_c->rowCount(); ++r) {
        for (int c = 0; c < 8; ++c) {
            if (r == ligne_selection)
                ui->tableWidget_c->item(r, c)->setBackground(Qt::yellow);
            else
                ui->tableWidget_c->item(r, c)->setBackground(Qt::white);
        }
    }

    if (ligne_selection != -1)
        ui->tableWidget_c->selectRow(ligne_selection);
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

    // 🔹 Remplir les lineEdit avec la ligne sélectionnée
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

    // 🔹 Confirmation avant modification
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer", "Voulez-vous vraiment modifier ce client ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    // 🔹 Création de l'objet client
    client c(id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite);

    // 🔹 Appel à la fonction modifier_client
    bool test = c.modifier_client(id_client, nom, prenom, date_naissance,
                                  email, num_tel, date_inscri, point_fedelite);

    // 🔹 Ici on met le test pour afficher le tableau et le message
    if (test) {
        afficher_client(id_client); // 🔹 affiche le tableau et surligne la ligne modifiée
        QMessageBox::information(this, "Succès", "✅ Modification effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Modification non effectuée.");
    }
}
void Gclient::on_brechercher_c_clicked()
{
    bool ok;
    int id = ui->lineEdit_recherche_c->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    client c;
    QSqlQueryModel *model = c.rechercher_client(id);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Résultat", "❌Aucun client trouvé !");
        return;
    }
    else{
        QMessageBox::information(this, "Résultat", "✅ Client trouvé !");
        return;
    }
    afficher_client();
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
/*void Gclient::on_bexporter_c_clicked()
{
    client c;
    if (c.exporter_client_pdf()) {
        QMessageBox::information(this, "Exportation réussie", "✅ Le fichier clients.pdf a été généré avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Impossible de générer le PDF.");
    }
}*/
void Gclient::on_bexporter_c_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (!fileName.isEmpty()) {
        client c;
        c.exporter_client_pdf(fileName);
    }
}
// Dans Gclient.cpp
/*void Gclient::afficherStatistiques_client()
{
    QSqlQuery query;
    if (!query.exec("SELECT TO_CHAR(TO_DATE(date_inscri, 'YYYY-MM-DD'), 'YYYY-MM') AS mois, COUNT(*) "
                     "FROM client GROUP BY TO_CHAR(TO_DATE(date_inscri, 'YYYY-MM-DD'), 'YYYY-MM')"))

    {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    QPieSeries *series = new QPieSeries();
    while(query.next())
    {
        QString mois = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(QString("%1 (%2)").arg(mois).arg(count), count);
    }

    if(series->isEmpty())
    {
        QMessageBox::information(this, "Statistiques", "Aucune donnée à afficher !");
        series->deleteLater();
        return;
    }

    for(auto slice : series->slices())
        slice->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par date d'inscription");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);

    // Pixmap pour mettre dans le QLabel
    QPixmap pix(ui->afficestat_c->size());
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    chartView.resize(ui->afficestat_c->size());
    chartView.render(&painter);

    ui->afficestat_c->setPixmap(pix);
}*/

/*void Gclient::afficherStatistiques_client()
{
    QSqlQuery query;
    QString sql = R"(
        SELECT
            CASE
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) < 20 THEN '<20'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 20 AND 29 THEN '20-29'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 30 AND 39 THEN '30-39'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 40 AND 49 THEN '40-49'
                ELSE '50+'
            END AS tranche_age,
            COUNT(*) AS nb_clients
        FROM client
        WHERE REGEXP_LIKE(date_naissance, '^\d{2}/\d{2}/\d{4}$')
        GROUP BY
            CASE
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) < 20 THEN '<20'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 20 AND 29 THEN '20-29'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 30 AND 39 THEN '30-39'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 40 AND 49 THEN '40-49'
                ELSE '50+'
            END
        ORDER BY tranche_age
    )";

    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }

    // Création de la série pour le graphique
    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString tranche = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(QString("%1 (%2)").arg(tranche).arg(count), count);
    }

    if (series->isEmpty()) {
        QMessageBox::information(nullptr, "Statistiques", "Aucune donnée à afficher.");
        delete series;
        return;
    }

    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("MS Serif", 9));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par tranche d'âge");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPixmap pix(chartView->sizeHint());
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    chartView->render(&painter);
    painter.end();

    ui->afficestat_c->setPixmap(pix);
}*/
/*void Gclient::afficherStatistiques_client()                   marche!!!!!!!!
{
    QSqlQuery query;

    // Requête : extraire l'année à partir de la date_naissance (VARCHAR)
    QString sql = R"(
        SELECT TO_CHAR(TO_DATE(date_naissance, 'DD/MM/YYYY'), 'YYYY') AS annee_naissance,
               COUNT(*) AS nb_clients
        FROM client
        WHERE REGEXP_LIKE(date_naissance, '^\d{2}/\d{2}/\d{4}$')  -- ne prend que les dates bien formatées
        GROUP BY TO_CHAR(TO_DATE(date_naissance, 'DD/MM/YYYY'), 'YYYY')
        ORDER BY annee_naissance
    )";

    if (!query.exec(sql))
    {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    // Création du graphique circulaire
    QPieSeries *series = new QPieSeries();
    while (query.next())
    {
        QString annee = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(QString("%1 (%2)").arg(annee).arg(count), count);
    }

    if (series->isEmpty())
    {
        QMessageBox::information(this, "Statistiques", "Aucune donnée à afficher !");
        delete series;
        return;
    }

    // Afficher les labels sur chaque part du graphique
    for (auto slice : series->slices())
    {
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("MS Serif", 9));
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par année de naissance");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    chartView.resize(681, 281);

    // Rendu dans le QLabel
    QPixmap pix(ui->afficestat_c->size());
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    chartView.resize(ui->afficestat_c->size());
    chartView.render(&painter);

    //ui->afficestat_c->setPixmap(pix);
    ui->afficestat_c->setPixmap(pix.scaled(ui->afficestat_c->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}*/

/*void Gclient::afficherStatistiques_client()  taille cv
{
    // 1️⃣ Création du graphique
    QPieSeries *series = new QPieSeries();
    series->append("Employés", 40);
    series->append("Clients", 30);
    series->append("Fournisseurs", 20);
    series->append("Produits", 10);

    // 2️⃣ Création du graphique (QChart)
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des données OPTISMART");
    chart->setAnimationOptions(QChart::AllAnimations);

    // 3️⃣ Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 4️⃣ 🔹 Fixer la taille du graphique avant capture
    chartView->resize(681, 281);  // Taille de ta QLabel

    // 5️⃣ Capture du graphique dans une image
    QPixmap pixmap = QPixmap::fromImage(chartView->grab().toImage());

    // 6️⃣ Redimension du rendu pour bien remplir la QLabel
    ui->afficestat_c->setPixmap(pixmap.scaled(
        ui->afficestat_c->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));

    // 7️⃣ (Optionnel) Centrer l’image dans la QLabel
    ui->afficestat_c->setAlignment(Qt::AlignCenter);
}*/

/*void Gclient::afficherStatistiques_client()
{
    // 1️⃣ Requête SQL : calcul des tranches d'âge
    QSqlQuery query;
    QString sql = R"(
        SELECT
            CASE
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) < 20 THEN '<20'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 20 AND 29 THEN '20-29'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 30 AND 39 THEN '30-39'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 40 AND 49 THEN '40-49'
                ELSE '50+'
            END AS tranche_age,
            COUNT(*) AS nb_clients
        FROM client
        WHERE REGEXP_LIKE(date_naissance, '^\d{2}/\d{2}/\d{4}$')
        GROUP BY
            CASE
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) < 20 THEN '<20'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 20 AND 29 THEN '20-29'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 30 AND 39 THEN '30-39'
                WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, TO_DATE(date_naissance, 'DD/MM/YYYY'))/12) BETWEEN 40 AND 49 THEN '40-49'
                ELSE '50+'
            END
        ORDER BY tranche_age
    )";

    if (!query.exec(sql)) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    // 2️⃣ Création de la série pour le camembert
    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString tranche = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(QString("%1 (%2)").arg(tranche).arg(count), count);
    }

    if (series->isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée à afficher !");
        delete series;
        return;
    }

    // 3️⃣ Affichage des labels des slices
    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("MS Serif", 10));
    }

    // 4️⃣ Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par tranche d'âge");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 5️⃣ Création du ChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 6️⃣ Supprimer l'ancien graphique s'il existe
    if (ui->layout_graphique->count() > 0) {
        QLayoutItem *item = ui->layout_graphique->takeAt(0);
        delete item->chartContainer();  // supprime l'ancien QChartView
        delete item;
    }

    // 7️⃣ Ajouter le nouveau graphique au layout
    ui->layout_graphique->addchartContainer(chartView);

    // 8️⃣ Optionnel : définir une taille pour le graphique
    chartView->setMinimumSize(400, 400);  // tu peux adapter selon ton UI
    chartView->show();
}*/
/*void Gclient::afficherStatistiques_client()            affiche dans un autre fenetre
{
    int moins25 = 0, entre25et40 = 0, entre40et60 = 0, plus60 = 0;

    QSqlQuery query("SELECT date_naissance FROM client");
    while (query.next())
    {
        QString dateStr = query.value(0).toString().trimmed();
        QDate dateNais = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (!dateNais.isValid())
            dateNais = QDate::fromString(dateStr, "yyyy-MM-dd");
        if (!dateNais.isValid())
            continue;

        int age = dateNais.daysTo(QDate::currentDate()) / 365;

        if (age < 25)
            moins25++;
        else if (age < 40)
            entre25et40++;
        else if (age < 60)
            entre40et60++;
        else
            plus60++;
    }

    QPieSeries *series = new QPieSeries();
    series->append("Moins de 25 ans", moins25);
    series->append("25 - 40 ans", entre25et40);
    series->append("40 - 60 ans", entre40et60);
    series->append("Plus de 60 ans", plus60);

    for (auto slice : series->slices())
    {
        double pct = slice->percentage() * 100;
        slice->setLabel(QString("%1 (%2%)").arg(slice->label()).arg(QString::number(pct, 'f', 1)));
        slice->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients selon leur âge");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // ✅ Fenêtre popup pour afficher le graphique
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques des clients");
    dialog->resize(700, 400);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addchartContainer(chartView);
    dialog->setLayout(layout);

    dialog->exec();
}*/
void Gclient::afficherStatistiques_client()
{
    int moins25 = 0, entre25et40 = 0, entre40et60 = 0, plus60 = 0;

    QSqlQuery query("SELECT date_naissance FROM client");
    while (query.next())
    {
        QString dateStr = query.value(0).toString().trimmed();
        QDate dateNais = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (!dateNais.isValid())
            dateNais = QDate::fromString(dateStr, "yyyy-MM-dd");
        if (!dateNais.isValid())
            continue;

        int age = dateNais.daysTo(QDate::currentDate()) / 365;

        if (age < 25)
            moins25++;
        else if (age < 40)
            entre25et40++;
        else if (age < 60)
            entre40et60++;
        else
            plus60++;
    }

    QPieSeries *series = new QPieSeries();
    series->append("Moins de 25 ans", moins25);
    series->append("25 - 40 ans", entre25et40);
    series->append("40 - 60 ans", entre40et60);
    series->append("Plus de 60 ans", plus60);

    for (auto slice : series->slices())
        slice->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients selon leur âge");
    chart->setAnimationOptions(QChart::AllAnimations);

    // Création du QChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Supprimer l'ancien contenu s'il existe
    QLayout *layout = ui->chartContainer->layout();
    if (!layout)
        layout = new QVBoxLayout(ui->chartContainer);
    else
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr)
        {
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




