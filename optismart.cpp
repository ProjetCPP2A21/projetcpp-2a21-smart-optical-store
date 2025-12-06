 #include "employe.h"
//#include "authentification.h"
#include "client.h"
#include "produit.h"
#include "fournisseur.h"
#include "ordonnance.h"
#include "optismart.h"
#include "ui_optismart.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>

optismart::optismart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::optismart)
{
    ui->setupUi(this);
    //---------------------------------------arduino----------------------------------------------
    serial->setPortName("COM3"); // adapte
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadOnly)) {
        connect(serial, &QSerialPort::readyRead,
                this, &optismart::onSerialDataReceived);
        ui->statusbar->showMessage("Port série ouvert");
    } else {
        ui->statusbar->showMessage("Erreur port série: " + serial->errorString());
    }

    ui->label->setText("En attente d'empreinte...");
    //--------------------------------------------------------------------------
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("sounds/button.mp3"));

    for (QPushButton *button : this->findChildren<QPushButton*>()) {
        connect(button, &QPushButton::clicked, this, [player]() {
            player->setPosition(0); // rewind
            player->play();
        });
    }
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index) {
        if (index == 1) {
            // Appel de ta fonction d’affichage automatique
            afficher_client();
        }

    }
            );


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
    connect(ui->bf_1, &QPushButton::clicked, this, [=]() { actualiserAffichagef(); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { actualiserAffichageo(); });

    // Page Client (menu 2)
    connect(ui->bem_3, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_3, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_3, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_3, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_3, &QPushButton::clicked, this, [=]() { setPage(4); });
    connect(ui->bf_3, &QPushButton::clicked, this, [=]() { actualiserAffichagef(); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { actualiserAffichageo(); });

    // Page Produit (menu 3)
    connect(ui->bem_4, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_4, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_4, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_4, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_4, &QPushButton::clicked, this, [=]() { setPage(4); });
    connect(ui->bf_4, &QPushButton::clicked, this, [=]() { actualiserAffichagef(); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { actualiserAffichageo(); });

    // Page Fournisseur (menu 4)
    connect(ui->bem_5, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_5, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_5, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_5, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_5, &QPushButton::clicked, this, [=]() { setPage(4); });
    connect(ui->bf_5, &QPushButton::clicked, this, [=]() { actualiserAffichagef(); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { actualiserAffichageo(); });

    // Page Ordonnance (menu 5)
    connect(ui->bem_6, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_6, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_6, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_6, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { setPage(4); });
    connect(ui->bf_6, &QPushButton::clicked, this, [=]() { actualiserAffichagef(); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { actualiserAffichageo(); });


    ui->stackedWidget->setCurrentIndex(5);

}
//--------------------------------------------------------------------------------------------------
void optismart::onSerialDataReceived()
{
    QByteArray data = serial->readAll();
    QString text = QString::fromUtf8(data).trimmed();

    // Exemple reçu : "FINGER_OK:ID=3"
    if (!text.startsWith("FINGER_OK:ID=")) {
        qDebug() << "Message non reconnu:" << text;
        return;
    }

    QString idStr = text.section('=', 1, 1);  // après le '='
    int idEmpreinte = idStr.toInt();

    ui->label->setText("Empreinte détectée, ID = " + idStr);

    // 1) On cherche l'employé correspondant
    QSqlQuery q;
    q.prepare(
        "SELECT e.ID_EMPLOYE, e.NOM, e.PRENOM "
        "FROM EMPLOYE e "
        "JOIN EMPREINTE_EMPLOYE ee ON e.ID_EMPLOYE = ee.ID_EMPLOYE "
        "WHERE ee.ID_EMPREINTE = :id"
        );
    q.bindValue(":id", idEmpreinte);

    int idEmploye = -1;
    QString nom, prenom;

    if (q.exec() && q.next()) {
        idEmploye = q.value("ID_EMPLOYE").toInt();
        nom = q.value("NOM").toString();
        prenom = q.value("PRENOM").toString();

        ui->label->setText(
            "Accès autorisé : " + prenom + " " + nom +
            " (empreinte " + idStr + ")"
            );

        // 2) Log ACCEPTE
        QSqlQuery log;
        log.prepare(
            "INSERT INTO JOURNAL_EMPREINTE "
            "  (ID_LOG, ID_EMPREINTE, ID_EMPLOYE, RESULTAT, MESSAGE) "
            "VALUES "
            "  (SEQ_JOURNAL_EMPREINTE.NEXTVAL, :idEmp, :idEmply, 'ACCEPTE', :msg)"
            );
        log.bindValue(":idEmp",   idEmpreinte);
        log.bindValue(":idEmply", idEmploye);
        log.bindValue(":msg",     "Empreinte reconnue");

        if (!log.exec()) {
            qDebug() << "Erreur INSERT log ACCEPTE:" << log.lastError().text();
        }

    } else {
        // Empreinte inconnue dans la table EMPREINTE_EMPLOYE
        ui->label->setText(
            "Empreinte inconnue (ID = " + idStr + "), accès refusé."
            );

        // Log REFUSE sans ID_EMPLOYE
        QSqlQuery log;
        log.prepare(
            "INSERT INTO JOURNAL_EMPREINTE "
            "  (ID_LOG, ID_EMPREINTE, ID_EMPLOYE, RESULTAT, MESSAGE) "
            "VALUES "
            "  (SEQ_JOURNAL_EMPREINTE.NEXTVAL, :idEmp, NULL, 'REFUSE', :msg)"
            );
        log.bindValue(":idEmp", idEmpreinte);
        log.bindValue(":msg",  "Empreinte non associée à un employé");

        if (!log.exec()) {
            qDebug() << "Erreur INSERT log REFUSE:" << log.lastError().text();
        }
    }
}

//-----------------------------------------------------------------------------------------------------
void optismart::actualiserAffichagep()
{}

//--------------------------------ordonnance------------------------------
void optismart::actualiserAffichageo()
{
    if (ui->tableWidget_5)
    ord.afficher(ui->tableWidget_5);
}

void optismart::on_btnActualiser_clicked()
{
    actualiserAffichageo();
    QMessageBox::information(this, "Actualisation", "Liste des ordonnances actualisée!");
}

void optismart::on_bajouter_o_clicked()
{
    // Récupération des informations saisies dans les champs
    QString cin = ui->linecin_o->text();
    QString nom = ui->linenom_o->text();
    QString prenom = ui->lineprenom_o->text();
    QString medecin = ui->linemedecin_o->text();
    QDate date = ui->linedate_o->date();

    // Validation des champs obligatoires
    if (cin.isEmpty() || nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    // Instancier un objet Ordonnance avec les informations saisies
    Ordonnance nouvelleOrdonnance(cin, nom, prenom, medecin, date);

    // Insérer l'objet dans la base de données
    bool test = nouvelleOrdonnance.ajouter();

    if (test) {
        // Si l'ajout réussit, actualiser l'affichage
        actualiserAffichageo();

        // Vider les champs de saisie
        ui->linecin_o->clear();
        ui->linenom_o->clear();
        ui->lineprenom_o->clear();
        ui->linemedecin_o->clear();
        ui->linedate_o->setDate(QDate::currentDate());

        QMessageBox::information(this, "Succès",
                                 "Ordonnance ajoutée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout de l'ordonnance!");
    }
}

void optismart::on_bsupprimer_o_clicked()
{
    // Récupération du CIN depuis le MÊME CHAMP
    QString cin = ui->linecin_o->text();

    // Validation du champ CIN
    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant",
                             "Veuillez saisir le CIN de l'ordonnance à supprimer!");
        return;
    }

    // Demande de confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de suppression",
                                  "Êtes-vous sûr de vouloir supprimer l'ordonnance avec CIN: " + cin + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    // Supprimer l'ordonnance
    bool test = ord.supprimer(cin);

    if (test) {
        // Si la suppression réussit, actualiser l'affichage
        actualiserAffichageo();

        // Vider tous les champs après suppression
        ui->linecin_o->clear();
        ui->linenom_o->clear();
        ui->lineprenom_o->clear();
        ui->linemedecin_o->clear();
        ui->linedate_o->setDate(QDate::currentDate());

        QMessageBox::information(this, "Succès",
                                 "Ordonnance supprimée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la suppression de l'ordonnance!\n"
                              "Vérifiez que le CIN existe dans la base de données.");
    }
}

void optismart::on_tableWidget_5_clicked(const QModelIndex &index)
{
    // Récupérer la ligne sélectionnée
    int row = index.row();

    // Remplir les champs avec les données de la ligne sélectionnée
    ui->linecin_o->setText(ui->tableWidget_5->item(row, 0)->text());
    ui->linenom_o->setText(ui->tableWidget_5->item(row, 1)->text());
    ui->lineprenom_o->setText(ui->tableWidget_5->item(row, 2)->text());
    ui->linemedecin_o->setText(ui->tableWidget_5->item(row, 3)->text());

    // Convertir la date du tableau vers QDate
    QString dateStr = ui->tableWidget_5->item(row, 4)->text();
    QDate date = QDate::fromString(dateStr, "dd-MM-yy");
    ui->linedate_o->setDate(date);

    // Stocker le CIN sélectionné pour la modification
    cinSelectionne = ui->tableWidget_5->item(row, 0)->text();
}

void optismart::on_bmodifier_o_clicked()
{
    // Vérifier qu'une ordonnance est sélectionnée
    if (cinSelectionne.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une ordonnance dans le tableau!");
        return;
    }

    // Récupération des nouvelles informations saisies
    QString nouveauCIN = ui->linecin_o->text();
    QString nom = ui->linenom_o->text();
    QString prenom = ui->lineprenom_o->text();
    QString medecin = ui->linemedecin_o->text();
    QDate date = ui->linedate_o->date();

    // Validation des champs obligatoires
    if (nouveauCIN.isEmpty() || nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    // Demande de confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de modification",
                                  "Êtes-vous sûr de vouloir modifier l'ordonnance avec CIN: " + cinSelectionne + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    // Créer un objet Ordonnance avec les nouvelles données
    Ordonnance ordonnanceModifiee(nouveauCIN, nom, prenom, medecin, date);

    // Modifier l'ordonnance dans la base de données
    bool test = ordonnanceModifiee.modifier(cinSelectionne);

    if (test) {
        // Si la modification réussit, actualiser l'affichage
        actualiserAffichageo();

        // Vider les champs et réinitialiser la sélection
        ui->linecin_o->clear();
        ui->linenom_o->clear();
        ui->lineprenom_o->clear();
        ui->linemedecin_o->clear();
        ui->linedate_o->setDate(QDate::currentDate());
        cinSelectionne = "";

        QMessageBox::information(this, "Succès",
                                 "Ordonnance modifiée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la modification de l'ordonnance!");
    }
}

//------------------------------fournisseur-------------------------------
void optismart::actualiserAffichagef()
{
    if (ui->tableWidget_4) {
        fourn.afficher(ui->tableWidget_4);
    }
}

void optismart::clearFields()
{
    ui->id_le->clear();
    ui->nom_le->clear();
    ui->adresse_le->clear();
    ui->email_le->clear();
    ui->telephone_le->clear();
    ui->cp_le->clear();
}

void optismart::on_bajouter_f_clicked()
{
    qDebug() << "=== CLICK SUR BAJOUTER_F ===";

    // Récupération des valeurs depuis les line edits
    QString id = ui->id_le->text();
    QString nom = ui->nom_le->text();
    QString adresse = ui->adresse_le->text();
    QString email = ui->email_le->text();
    QString telephone = ui->telephone_le->text();
    QString condition_paiement = ui->cp_le->text();

    qDebug() << "Valeurs récupérées:";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Email:" << email;
    qDebug() << "Téléphone:" << telephone;
    qDebug() << "Condition paiement:" << condition_paiement;

    // Validation des champs obligatoires
    if (id.isEmpty() || nom.isEmpty() || telephone.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir les champs ID, Nom et Téléphone!");
        return;
    }

    // Validation de la longueur des champs
    if (id.length() > 50) {
        QMessageBox::warning(this, "ID trop long", "L'ID ne doit pas dépasser 50 caractères!");
        return;
    }
    if (nom.length() > 50) {
        QMessageBox::warning(this, "Nom trop long", "Le nom ne doit pas dépasser 50 caractères!");
        return;
    }
    if (adresse.length() > 50) {
        QMessageBox::warning(this, "Adresse trop longue", "L'adresse ne doit pas dépasser 50 caractères!");
        return;
    }
    if (email.length() > 50) {
        QMessageBox::warning(this, "Email trop long", "L'email ne doit pas dépasser 50 caractères!");
        return;
    }
    if (telephone.length() > 50) {
        QMessageBox::warning(this, "Téléphone trop long", "Le téléphone ne doit pas dépasser 50 caractères!");
        return;
    }
    if (condition_paiement.length() > 50) {
        QMessageBox::warning(this, "Condition trop longue", "La condition de paiement ne doit pas dépasser 50 caractères!");
        return;
    }

    // Création d'un objet fournisseur
    fournisseur nouveauFournisseur(id, nom, adresse, email, telephone, condition_paiement);

    // Ajout dans la base de données
    if (nouveauFournisseur.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès!");

        // Actualiser l'affichage
        actualiserAffichagef();

        // Vider les champs
        clearFields();

        qDebug() << "✅ Fournisseur ajouté et affichage actualisé";
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout du fournisseur!\n"
                              "Vérifiez que:\n"
                              "- L'ID n'existe pas déjà\n"
                              "- Tous les champs sont valides");
        qDebug() << "❌ Erreur lors de l'ajout";
    }
}

void optismart::on_bsupprimer_f_clicked()
{
    qDebug() << "=== CLICK SUR BSUPPRIMER_F ===";

    // Récupérer l'ID à supprimer
    QString id = ui->id_le->text();

    // Validation
    if (id.isEmpty()) {
        QMessageBox::warning(this, "ID manquant",
                             "Veuillez entrer l'ID du fournisseur à supprimer!");
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer le fournisseur avec ID: " + id + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Supprimer le fournisseur
        if (fourn.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès!");

            // Actualiser l'affichage
            actualiserAffichagef();

            // Vider les champs
            clearFields();

            qDebug() << "✅ Fournisseur supprimé et affichage actualisé";
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la suppression!\n"
                                  "Vérifiez que l'ID existe dans la base de données.");
            qDebug() << "❌ Erreur lors de la suppression";
        }
    } else {
        qDebug() << "❌ Suppression annulée par l'utilisateur";
    }
}

// ⭐ NOUVELLE FONCTION: Modifier un fournisseur
void optismart::on_bmodifier_f_clicked()
{
    qDebug() << "=== CLICK SUR BMODIFIER_F ===";

    // Récupération des valeurs depuis les line edits
    QString id = ui->id_le->text();
    QString nom = ui->nom_le->text();
    QString adresse = ui->adresse_le->text();
    QString email = ui->email_le->text();
    QString telephone = ui->telephone_le->text();
    QString condition_paiement = ui->cp_le->text();

    qDebug() << "Valeurs pour modification:";
    qDebug() << "ID:" << id;
    qDebug() << "Nouveau Nom:" << nom;
    qDebug() << "Nouvelle Adresse:" << adresse;
    qDebug() << "Nouvel Email:" << email;
    qDebug() << "Nouveau Téléphone:" << telephone;
    qDebug() << "Nouvelle Condition:" << condition_paiement;

    // Validation des champs obligatoires
    if (id.isEmpty()) {
        QMessageBox::warning(this, "ID manquant",
                             "Veuillez entrer l'ID du fournisseur à modifier!");
        return;
    }
    if (nom.isEmpty() || telephone.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir les champs Nom et Téléphone!");
        return;
    }

    // Validation de la longueur des champs
    if (nom.length() > 50) {
        QMessageBox::warning(this, "Nom trop long", "Le nom ne doit pas dépasser 50 caractères!");
        return;
    }
    if (adresse.length() > 50) {
        QMessageBox::warning(this, "Adresse trop longue", "L'adresse ne doit pas dépasser 50 caractères!");
        return;
    }
    if (email.length() > 50) {
        QMessageBox::warning(this, "Email trop long", "L'email ne doit pas dépasser 50 caractères!");
        return;
    }
    if (telephone.length() > 50) {
        QMessageBox::warning(this, "Téléphone trop long", "Le téléphone ne doit pas dépasser 50 caractères!");
        return;
    }
    if (condition_paiement.length() > 50) {
        QMessageBox::warning(this, "Condition trop longue", "La condition de paiement ne doit pas dépasser 50 caractères!");
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir modifier le fournisseur avec ID: " + id + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Modifier le fournisseur
        if (fourn.modifier(id, nom, adresse, email, telephone, condition_paiement)) {
            QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès!");

            // Actualiser l'affichage
            actualiserAffichagef();

            // Vider les champs
            clearFields();

            qDebug() << "✅ Fournisseur modifié et affichage actualisé";
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la modification!\n"
                                  "Vérifiez que:\n"
                                  "- L'ID existe dans la base de données\n"
                                  "- Tous les champs sont valides");
            qDebug() << "❌ Erreur lors de la modification";
        }
    } else {
        qDebug() << "❌ Modification annulée par l'utilisateur";
    }
}
//------------------------------client------------------------------------
void optismart::on_bajouter_c_clicked()
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

    //  Test de chaque champ vide
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

    //  Conversion des champs numériques
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

    // Création du client et ajout
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
}

void optismart::on_bsupprimer_c_clicked()
{
    int id = ui->lineid_c->text().toInt();
    client temp;
    bool test = temp.supprimer_client(id);
    // Confirmation avant suppression
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

    //  Remplir les lineEdit avec la ligne sélectionnée
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

    //  Confirmation avant modification
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer", "Voulez-vous vraiment modifier ce client ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    // Création de l'objet client
    client c(id_client, nom, prenom, date_naissance, email, num_tel, date_inscri, point_fedelite);

    // Appel à la fonction modifier_client
    bool test = c.modifier_client(id_client, nom, prenom, date_naissance,
                                  email, num_tel, date_inscri, point_fedelite);

    // Ici on met le test pour afficher le tableau et le message
    if (test) {
        afficher_client(id_client); // 🔹 affiche le tableau et surligne la ligne modifiée
        QMessageBox::information(this, "Succès", "✅ Modification effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Modification non effectuée.");
    }
}
void optismart::on_ajouterButton_clicked()
{
    QString type = ui->typeEdit->text();
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
    bool okId;
    int id_produit = ui->idEdit->text().trimmed().toInt(&okId);
    if (!okId && !ui->idEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_produit invalide (doit être un entier ou vide) ❌"));
        return;
    }
    int id_fournisseur = ui->idFEdit->text().trimmed().toInt(&okId);
    if (!okId || id_fournisseur <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_fournisseur invalide (doit être un entier > 0) ❌"));
        return;
    }
    int id_client = ui->idCEdit->text().trimmed().toInt(&okId);
    if (!okId || id_client <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_client invalide (doit être un entier > 0) ❌"));
        return;
    }
    int id_employe = ui->idEEdit->text().trimmed().toInt(&okId);
    if (!okId || id_employe <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("id_employe invalide (doit être un entier > 0) ❌"));
        return;
    }

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
    if (test)
    {
        ui->tableWidget_p_2->setModel(Ptmp.afficher());
        QMessageBox::information(this, tr("Succès"), tr("Produit ajouté avec succès ✅"));
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
        on_statsButton_clicked();
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l’ajout du produit ❌"));
    }
}

void optismart::on_supprimerButton_clicked()
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

void optismart::on_tableWidget_p_2_doubleClicked(const QModelIndex &index)
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

void optismart::on_modifierButton_clicked()
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

void optismart::on_searchButton_clicked()
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

void optismart::on_exportPdfButton_clicked()
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
void optismart::on_statsButton_clicked()
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
void optismart::on_trierButton_clicked()
{
    // ÉTAPE 1 : Recharge toutes les données du tableau
    ui->tableWidget_p_2->setModel(Ptmp.afficher());

    // ÉTAPE 2 : Trie les lignes par la colonne "type" (colonne 1)
    ui->tableWidget_p_2->sortByColumn(1, Qt::AscendingOrder);
}
optismart::~optismart()
{
    if (serial->isOpen())
        serial->close();
    delete ui;
}

