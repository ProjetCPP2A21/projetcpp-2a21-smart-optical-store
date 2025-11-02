#include "Gclient.h"
#include "ui_Gclient.h"
#include <QMessageBox>
#include "client.h"
#include "connection.h"
Gclient::Gclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gclient)
{
    ui->setupUi(this);
    connect(ui->tableWidget_c, &QTableWidget::cellClicked,
            this, &Gclient::on_tableWidget_c_cellClicked);


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

