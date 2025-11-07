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
    QObject::connect(ui->bajouter_e, &QPushButton::clicked, this, [this]() {
        if (!this->verifierChamps()) return;
        this->chargerDepuisUI();
        if (this->ajouter())
            this->afficherDansTable();
    });
    /*QObject::connect(ui->bretour_stats_e, &QPushButton::clicked, this, [this]() {
        this->retourstats_e();
    });
    QObject::connect(ui->bquitter_e, &QPushButton::clicked, this, [this]() {
        this->quitter();
    });*/



}
void employe::quitter(){
    QApplication::quit();
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
// -------------------- Controle de saisie sur les champs --------------------

bool employe::verifierChamps()
{
    if (ui->lineid_e->text().isEmpty() ||
        ui->linenom_e->text().isEmpty() ||
        ui->lineprenon_e->text().isEmpty() ||
        ui->lineemail_e->text().isEmpty() ||
        ui->linetel_e->text().isEmpty()) {
        QMessageBox::warning(nullptr, "Champs obligatoires",
                             "Veuillez remplir tous les champs obligatoires.");
        return false;
    }

    // Validation email
    QRegularExpression regexEmail("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    if (!regexEmail.match(ui->lineemail_e->text()).hasMatch()) {
        QMessageBox::warning(nullptr, "Email invalide", "Veuillez entrer une adresse email valide.");
        return false;
    }

    // Validation numéro téléphone (ex: 8 chiffres)
    QRegularExpression regexTel("^\\d{8,10}$");
    if (!regexTel.match(ui->linetel_e->text()).hasMatch()) {
        QMessageBox::warning(nullptr, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir entre 8 et 10 chiffres.");
        return false;
    }

    return true;
}
// -------------------- Traduction erreurs oracle --------------------
QString employe::traduireErreurOracle(const QString &messageErreur)
{
    if (messageErreur.contains("ORA-00001"))
        return "Cet enregistrement existe déjà (violation de clé unique).";
    if (messageErreur.contains("ORA-01400"))
        return "Certains champs obligatoires ne sont pas remplis.";
    if (messageErreur.contains("ORA-02291"))
        return "Référence non valide : un champ lié n'existe pas.";
    if (messageErreur.contains("ORA-02292"))
        return "Impossible de supprimer cet élément car il est lié à d'autres enregistrements.";
    if (messageErreur.contains("ORA-12899"))
        return "La valeur saisie dépasse la taille maximale autorisée pour un champ.";
    if (messageErreur.contains("ORA-00904"))
        return "Une colonne ou une valeur utilisée est invalide.";
    if (messageErreur.contains("ORA-01017"))
        return "Identifiant ou mot de passe Oracle incorrect.";
    if (messageErreur.contains("ORA-12170"))
        return "Connexion au serveur Oracle impossible (délai d'attente dépassé).";

    // Par défaut : message brut mais plus lisible
    return "Erreur Oracle : " + messageErreur;
}
void employe::retourstats_e(){
    ui->stackedWidget->setCurrentWidget(ui->employe);

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
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
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
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
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
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
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
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
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
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
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
    // si tu veux toujours naviguer vers la page stats
    /*ui->stackedWidget->setCurrentWidget(ui->stats_e);*/

    // 1) Récupérer les données
    QSqlQuery query;
    if (!query.exec("SELECT poste, COUNT(*) FROM employe GROUP BY poste")) {
        QMessageBox::critical(nullptr, "Erreur SQL", traduireErreurOracle(query.lastError().text()));
        return;
    }

    // 2) Construire la série
    auto *series = new QPieSeries();
    while (query.next()) {
        const QString poste = query.value(0).toString();
        const int count = query.value(1).toInt();
        series->append(QString("%1 (%2)").arg(poste).arg(count), count);
    }

    if (series->isEmpty()) {
        QMessageBox::information(nullptr, "Statistiques", "Aucune donnée à afficher.");
        series->deleteLater();
        return;
    }

    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 9));
    }

    // 3) Créer le chart + view
    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 4) Injecter dans le QGroupBox (au lieu de stats_e directement)
   /* QGroupBox *box = ui->groupBox_stats; // 🔁 remplace par le nom exact si différent*/

    // Nettoyer l'ancien contenu/layout du groupbox
    /*if (QLayout *old = box->layout()) {
        QLayoutItem *it;
        while ((it = old->takeAt(0)) != nullptr) {
            if (QWidget *w = it->widget()) w->deleteLater();
            delete it;
        }
        delete old;
    }*/

    // Nouveau layout pour le groupbox
    auto *layout = new QVBoxLayout();
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);
    layout->addWidget(chartView);
    /*box->setLayout(layout);*/
}

