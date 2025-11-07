#include "employe.h"
#include "authentification.h"
#include "client.h"
#include "produit.h"
#include "fournisseur.h"
#include "ordonnance.h"
#include "optismart.h"
#include "ui_optismart.h"

optismart::optismart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::optismart)
{
    ui->setupUi(this);
    /*ui->stackedWidget->setCurrentIndex(1); // Page 1
    connect(ui->tableWidget_c, &QTableWidget::cellClicked,
            this, &optismart::on_tableWidget_c_cellClicked);
    afficher_client();  // affiche automatiquement les clients à l’ouverture*/
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index) {
        if (index == 1) {
            // Appel de ta fonction d’affichage automatique
            afficher_client();
        }
    });


    // ---- Initialiser la classe employe ----
    // On relie l'interface à la logique du modèle employe
    employe *employePage = new employe(ui, this);
    employePage->afficherDansTable(); // charge les données existantes au démarrage

    // ---- Appliquer un fond dégradé à la fenêtre principale ----
    QLinearGradient gradient(0, 0, 0, this->height());
    gradient.setColorAt(0.0, QColor(168, 230, 207));  // Mint
    gradient.setColorAt(1.0, QColor(255, 211, 182));  // Peach

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window, QBrush(gradient));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // ---- Navigation entre les pages du stackedWidget ----
    auto setPage = [=](int index) {
        ui->stackedWidget->setCurrentIndex(index);
    };

    // Page Employé (menu 1)
    connect(ui->bem_1, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_1, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_1, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_1, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_1, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Client (menu 2)
    connect(ui->bem_3, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_3, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_3, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_3, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_3, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Produit (menu 3)
    connect(ui->bem_4, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_4, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_4, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_4, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_4, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Fournisseur (menu 4)
    connect(ui->bem_5, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_5, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_5, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_5, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_5, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Ordonnance (menu 5)
    connect(ui->bem_6, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_6, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_6, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_6, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { setPage(4); });


    /*ui->stackedWidget->setCurrentIndex(5);*/

}
//Client
void optismart::on_bajouter_c_clicked()
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

void optismart::on_bsupprimer_c_clicked()
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


void optismart::afficher_client(int id_selectionne)
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



void optismart::on_tableWidget_c_cellClicked(int row, int column)
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


void optismart::on_bmodifier_c_clicked()
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


optismart::~optismart()
{
    delete ui;
}
