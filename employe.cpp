#include "employe.h"



employe::employe(Ui::optismart *ui, QObject *parent)
    : QObject(parent), ui(ui)
{
    // 🔹 Connecter les boutons avec des lambdas claires
    QObject::connect(ui->bajouter_e, &QPushButton::clicked, this, [this]() {
        this->chargerDepuisUI();
        if (this->ajouter())
            this->afficherDansTable();
    });

    QObject::connect(ui->bmodifier_e, &QPushButton::clicked, this, [this]() {
        this->chargerDepuisUI();
        if (this->modifier())
            this->afficherDansTable();
    });

    QObject::connect(ui->bsupprimer_e, &QPushButton::clicked, this, [this]() {
        int id = this->ui->lineid_e->text().toInt();
        if (this->supprimer(id))
            this->afficherDansTable();
    });

    QObject::connect(ui->bexporter_e, &QPushButton::clicked, this, [this]() {
        this->exporterPdf("");
    });
    QObject::connect(ui->bannuler_e, &QPushButton::clicked, this, [this]() {
        this->viderChamps();
    });
    QObject::connect(ui->bafficher_e, &QPushButton::clicked, this, [this]() {
        this->afficherDansTable();
    });
    QObject::connect(ui->brechercher_e, &QPushButton::clicked, this, [this]() {

        this->rechercherParNom();
    });
    QObject::connect(ui->bstatistique_e, &QPushButton::clicked, this, [this]() {
        this->afficherStatistiques();

    });

}

// -------------------- Charger les données depuis l'UI --------------------
void employe::chargerDepuisUI()
{
    id_employe = ui->lineid_e->text().toInt();
    nom = ui->linenom_e->text();
    prenom = ui->lineprenon_e->text();
    adresse = ui->lineemail_e->text();
    email = ui->lineemail_e->text();
    num_tel = ui->linetel_e->text();
    poste = ui->lineposte_e->text();
    login = ui->linelogin_e->text();
    password = ui->linepassword_e->text();
}

void employe::rechercherParNom()
{
    QString nom = ui->linerechercher_e->text();
    if (nom.trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Recherche", "Veuillez entrer un nom à rechercher.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_employe, nom, prenom, email, num_tel, poste "
                  "FROM employe WHERE LOWER(nom) = LOWER(:nom)");
    query.bindValue(":nom", nom);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }

    if (query.next()) {
        QString info = QString(
                           "Employé trouvé :\n\n"
                           "ID : %1\nNom : %2\nPrénom : %3\nEmail : %4\nTéléphone : %5\nPoste : %6")
                           .arg(query.value("id_employe").toString())
                           .arg(query.value("nom").toString())
                           .arg(query.value("prenom").toString())
                           .arg(query.value("email").toString())
                           .arg(query.value("num_tel").toString())
                           .arg(query.value("poste").toString());

        QMessageBox::information(nullptr, "Résultat de la recherche", info);
    } else {
        QMessageBox::information(nullptr, "Résultat de la recherche",
                                 "Aucun employé trouvé avec ce nom.");
    }
}


// -------------------- Ajouter un employé --------------------
bool employe::ajouter()
{
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(nullptr, "Champs obligatoires", "Veuillez remplir le nom et le prénom.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO employe (id_employe, nom, prenom, adresse, email, num_tel, poste, login, password) "
                  "VALUES (:id, :nom, :prenom, :adresse, :email, :num_tel, :poste,:login, :password)");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":poste", poste);
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "Employé ajouté avec succès !");
    return true;
}

// -------------------- Modifier un employé --------------------
bool employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, adresse=:adresse, "
                  "email=:email, num_tel=:num_tel, poste=:poste WHERE id_employe=:id");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":poste", poste);


    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "Employé modifié avec succès !");
    return true;
}

// -------------------- Supprimer un employé --------------------
bool employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM optismart.employe WHERE id_employe=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "Employé supprimé !");
    return true;
}

// -------------------- Afficher les employés dans le tableau --------------------
void employe::afficherDansTable()
{
    ui->tableWidget_e->setRowCount(0);
    QSqlQuery query("SELECT id_employe, nom, prenom, email, num_tel, poste FROM optismart.employe");

    int row = 0;
    while (query.next()) {
        ui->tableWidget_e->insertRow(row);
        for (int col = 0; col < 6; ++col) {
            ui->tableWidget_e->setItem(row, col,
                                       new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }
}
void employe::viderChamps()
{
    ui->lineid_e->clear();
    ui->linenom_e->clear();
    ui->lineprenon_e->clear();
    ui->lineemail_e->clear();
    ui->lineemail_e->clear();
    ui->linetel_e->clear();
    ui->lineposte_e->clear();
    ui->linelogin_e->clear();
    ui->linepassword_e->clear();
}

// -------------------- Exporter en PDF --------------------
bool employe::exporterPdf(const QString &fichier)
{
    QSqlQuery query;
    if (!query.exec("SELECT id_employe, nom, prenom, email, num_tel, poste FROM employe ORDER BY id_employe")) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QString now = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm");
    QString html = "<html><head><meta charset='utf-8'><style>"
                   "body{font-family:Arial,Helvetica,sans-serif;}"
                   "table{width:100%;border-collapse:collapse;}"
                   "th,td{border:1px solid #888;padding:6px;text-align:left;}"
                   "th{background:#f0f0f0;}"
                   "tr:nth-child(even){background:#fafafa;}"
                   "</style></head><body>";
    html += "<h2>Liste des employés</h2><p>Généré le " + now + "</p><table>";
    html += "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Email</th><th>Téléphone</th><th>Poste</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int i = 0; i < 6; ++i)
            html += "<td>" + query.value(i).toString().toHtmlEscaped() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";

    QString outputPath = fichier;
    if (outputPath.isEmpty()) {
        outputPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/employes.pdf";
    }
    if (QFileInfo(outputPath).suffix().toLower() != "pdf")
        outputPath += ".pdf";

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(outputPath);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(nullptr, "PDF exporté", "Le fichier a été enregistré sous :\n" + outputPath);
    return true;
}



    void employe::afficherStatistiques()
{
    ui->stackedWidget->setCurrentWidget(ui->stats_e);
    // 1️⃣ Préparer les données
    QSqlQuery query;
    if (!query.exec("SELECT poste, COUNT(*) FROM employe GROUP BY poste")) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }


    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString poste = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(poste + " (" + QString::number(count) + ")", count);
    }

    if (series->isEmpty()) {
        QMessageBox::information(nullptr, "Statistiques", "Aucune donnée à afficher.");
        return;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Améliorer l’affichage
    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 9));
    }


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QLayout *oldLayout = ui->stats_e->layout();
    if (oldLayout) delete oldLayout;

    QVBoxLayout *layout = new QVBoxLayout(ui->stats_e);
    layout->addWidget(chartView);
}
