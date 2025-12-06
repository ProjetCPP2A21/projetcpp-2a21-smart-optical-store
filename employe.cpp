#include "employe.h"
#include "performance.h"
#include "planninghoraire.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

employe::employe(Ui::optismart *ui, QObject *parent)
    : QObject(parent), ui(ui)
{

    this->ui->tableWidget_e->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableWidget_e->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->tableWidget_e->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget_e->setStyleSheet(
        "QTableWidget::item:selected {"
        "    background-color: rgb(0, 120, 215);"  // bleu style Windows
        "}"
        );
    // 🔹 Connecter les boutons avec des lambdas claires
    // Ouvrir la page planning pour l'employé sélectionné
    //------------------------------------Planning----------------------------------------------------------------------------------------
    QObject::connect(this->ui->bplanning_e, &QPushButton::clicked, this, [this]() {

        int row = this->ui->tableWidget_e->currentRow();
        if (row < 0) {
            QMessageBox::warning(nullptr, tr("Attention"),
                                 tr("Veuillez d'abord sélectionner un employé."));
            return;
        }

        QTableWidgetItem *itemId = this->ui->tableWidget_e->item(row, 0);
        if (!itemId) {
            QMessageBox::warning(nullptr, tr("Erreur"),
                                 tr("Impossible de récupérer l'identifiant de l'employé."));
            return;
        }
        int idEmp = itemId->text().toInt();

        // (Optionnel) afficher le nom de l'employé sur la page planning
        QTableWidgetItem *itemNom    = this->ui->tableWidget_e->item(row, 1);
        QTableWidgetItem *itemPrenom = this->ui->tableWidget_e->item(row, 2);
        QString nomComplet = QString("%1 %2")
                                 .arg(itemPrenom ? itemPrenom->text() : "")
                                 .arg(itemNom ? itemNom->text() : "");
        // si tu as un label :
         this->ui->label_emp_planning->setText(nomComplet);

        // Sauver l'ID employé dans un label caché ou une propriété (plus propre : membre de la classe)
        // Pour faire simple ici, on va le stocker dans un QLineEdit non éditable si tu veux :
        // this->ui->lineEdit_idEmp_planning->setText(QString::number(idEmp));

        // Charger planning du jour actuel pour cet employé
        QDate today = QDate::currentDate();
        QSqlQueryModel *model = PlanningHoraire::afficherSemaineEmploye(idEmp, today.addDays(-(today.dayOfWeek()-1))); // lundi de la semaine
        this->ui->tableView_planning_e->setModel(model);
        this->ui->tableView_planning_e->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->ui->stackedWidget->setCurrentWidget(this->ui->page_planning_e);
    });
    QObject::connect(this->ui->bajouter_planning_e, &QPushButton::clicked, this, [this]() {

        int row = this->ui->tableWidget_e->currentRow();
        if (row < 0) {
            QMessageBox::warning(nullptr, tr("Attention"),
                                 tr("Veuillez sélectionner un employé dans la page employé avant."));
            return;
        }

        QTableWidgetItem *itemId = this->ui->tableWidget_e->item(row, 0);
        if (!itemId) {
            QMessageBox::warning(nullptr, tr("Erreur"),
                                 tr("Impossible de récupérer l'identifiant de l'employé."));
            return;
        }
        int idEmp = itemId->text().toInt();

        QDate dateJour = this->ui->dateEdit_planning->date();
        QString shift = this->ui->comboShift_planning->currentText();
        QString hDeb = this->ui->timeEdit_debut_planning->time().toString("HH:mm");
        QString hFin = this->ui->timeEdit_fin_planning->time().toString("HH:mm");

        PlanningHoraire pl(idEmp, dateJour, shift, hDeb, hFin);

        if (!pl.ajouter()) {
            QMessageBox::critical(nullptr, tr("Erreur"),
                                  tr("Erreur lors de l'ajout du shift au planning."));
            return;
        }

        QMessageBox::information(nullptr, tr("Succès"), tr("Shift ajouté au planning."));

        // Rafraîchir immédiatement la vue (semaine de la date choisie)
        QDate lundi = dateJour.addDays(-(dateJour.dayOfWeek() - 1));
        QSqlQueryModel *model = PlanningHoraire::afficherSemaineEmploye(idEmp, lundi);

        this->ui->tableView_planning_e->setModel(model);
        this->ui->tableView_planning_e->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    });

    QObject::connect(this->ui->bretour_planning_e, &QPushButton::clicked, this, [this]() {
        this->retour();
    });
    QObject::connect(this->ui->comboShift_planning,
                     QOverload<int>::of(&QComboBox::currentIndexChanged),
                     this,
                     [this](int index) {

                         QString shift = this->ui->comboShift_planning->currentText();

                         if (shift == "MATIN") {
                             this->ui->timeEdit_debut_planning->setTime(QTime(8, 0));   // 08:00
                             this->ui->timeEdit_fin_planning->setTime(QTime(12, 0));    // 12:00
                         }
                         else if (shift == "APRES-MIDI") {
                             this->ui->timeEdit_debut_planning->setTime(QTime(13, 0));  // 13:00
                             this->ui->timeEdit_fin_planning->setTime(QTime(17, 0));    // 17:00
                         }
                         else if (shift == "SOIR") {
                             this->ui->timeEdit_debut_planning->setTime(QTime(18, 0));  // 18:00
                             this->ui->timeEdit_fin_planning->setTime(QTime(22, 0));    // 22:00
                         }
                     });
    QObject::connect(this->ui->bgenerer_semaine_e, &QPushButton::clicked, this, [this]() {

        // 1) Vérifier qu'un employé est sélectionné dans le tableau des employés
        int row = this->ui->tableWidget_e->currentRow();
        if (row < 0) {
            QMessageBox::warning(nullptr, tr("Attention"),
                                 tr("Veuillez d'abord sélectionner un employé dans la liste."));
            return;
        }

        QTableWidgetItem *itemId = this->ui->tableWidget_e->item(row, 0); // col 0 = ID_EMPLOYE
        if (!itemId) {
            QMessageBox::warning(nullptr, tr("Erreur"),
                                 tr("Impossible de récupérer l'identifiant de l'employé."));
            return;
        }
        int idEmp = itemId->text().toInt();

        // 2) Déterminer la semaine
        //    - soit tu utilises la date du QDateEdit
        //    - soit tu peux remplacer par QDate::currentDate()
        QDate dateRef = this->ui->dateEdit_planning->date();
        if (!dateRef.isValid())
            dateRef = QDate::currentDate();

        // Lundi de la semaine (1 = lundi)
        QDate lundi = dateRef.addDays(-(dateRef.dayOfWeek() - 1));

        // 3) (Optionnel) Vider le planning existant de cette semaine pour cet employé
        {
            QSqlQuery q;
            q.prepare(
                "DELETE FROM OPTISMART.PLANNING_HORAIRE "
                "WHERE ID_EMPLOYE = :id_emp "
                "  AND DATE_JOUR BETWEEN :d_lundi AND :d_dimanche"
                );
            q.bindValue(":id_emp", idEmp);
            q.bindValue(":d_lundi", lundi);
            q.bindValue(":d_dimanche", lundi.addDays(6));
            q.exec();
        }

        // 4) Générer automatiquement 1 shift aléatoire par jour (lundi → dimanche)
        //    Shifts possibles + heures associées
        struct ShiftInfo {
            QString nom;
            QTime   debut;
            QTime   fin;
        };

        QVector<ShiftInfo> shifts = {
            { "MATIN",      QTime(8,  0), QTime(12, 0) },
            { "APRES-MIDI", QTime(13, 0), QTime(17, 0) },
            { "SOIR",       QTime(18, 0), QTime(22, 0) }
        };

        for (int i = 0; i < 5; ++i) {  // 7 jours ; mets 5 pour lundi–vendredi si tu veux
            QDate jour = lundi.addDays(i);

            // Choisir un shift aléatoire parmi les 3
            int idx = QRandomGenerator::global()->bounded(shifts.size());
            const ShiftInfo &s = shifts[idx];

            QString hDebStr = s.debut.toString("HH:mm");
            QString hFinStr = s.fin.toString("HH:mm");

            PlanningHoraire pl(idEmp, jour, s.nom, hDebStr, hFinStr);
            if (!pl.ajouter()) {
                qWarning() << "Erreur lors de l'ajout du planning pour" << jour;
            }
        }

        // 5) Afficher immédiatement le planning de la semaine pour cet employé
        QSqlQueryModel *model = PlanningHoraire::afficherSemaineEmploye(idEmp, lundi);
        this->ui->tableView_planning_e->setModel(model);
        this->ui->tableView_planning_e->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

        QMessageBox::information(nullptr, tr("Planning généré"),
                                 tr("Le planning de la semaine a été généré automatiquement pour cet employé."));
    });



//-------------------------------------------performmance------------------------------------------------------
    QObject::connect(ui->bcalculer_prime_e, &QPushButton::clicked, this, [this]() {

        // 🟦 1) Récupérer l’employé sélectionné dans tableWidget_e
        int row = this->ui->tableWidget_e->currentRow();
        if (row < 0) {
            QMessageBox::warning(nullptr, tr("Attention"),
                                 tr("Veuillez sélectionner un employé dans le tableau."));
            return;
        }

        // On suppose que la colonne 0 = ID_EMPLOYE
        QTableWidgetItem *itemId = this->ui->tableWidget_e->item(row, 0);
        if (!itemId) {
            QMessageBox::warning(nullptr, tr("Erreur"),
                                 tr("Impossible de récupérer l'identifiant de l'employé."));
            return;
        }
        int idEmp = itemId->text().toInt();

        // 🟦 2) Récupérer les paramètres de performance depuis l'IHM
        int mois  = this->ui->combomois_prime_e->currentIndex() + 1;   // Janvier = 1
        int annee = this->ui->spinannee_prime_e->value();

        int nbVentes  = this->ui->spinnb_ventes_e->value();
        int nbRetards = this->ui->spinnb_retards_e->value();
        double note   = this->ui->dspinnote_resp_e->value();

        // 🟦 3) Charger ou créer l'objet Performance
        Performance perf;
        if (Performance::chargerPour(idEmp, mois, annee, perf)) {
            // Déjà existant : mettre à jour les champs
            perf.setNbVentes(nbVentes);
            perf.setNbRetards(nbRetards);
            perf.setNoteResp(note);
        } else {
            // Nouveau
            perf = Performance(idEmp, mois, annee, nbVentes, nbRetards, note);
        }

        // 🟦 4) Calculer le score & la prime
        perf.calculerScoreEtPrime(300.0); // 300 = prime max (modifiable)

        // 🟦 5) Enregistrer : INSERT ou UPDATE
        bool ok = false;
        if (perf.getIdPerf() == -1) {
            ok = perf.ajouter();
        } else {
            ok = perf.mettreAJour();
        }

        if (!ok) {
            QMessageBox::critical(nullptr, tr("Erreur"),
                                  tr("Erreur lors de l'enregistrement de la performance."));
            return;
        }

        // 🟦 6) Feedback à l'utilisateur
        QMessageBox::information(
            nullptr,
            tr("Prime calculée"),
            tr("Score global : %1\nPrime calculée : %2")
                .arg(perf.getScoreGlobal())
                .arg(perf.getPrimeCalculee())
            );
        QTimer::singleShot(0, this, [this, idEmp]() {
            QSqlQueryModel *model = Performance::afficherParEmploye(idEmp);
            this->ui->tableView_primes_e->setModel(model);
            this->ui->tableView_primes_e->horizontalHeader()
                ->setSectionResizeMode(QHeaderView::Stretch);
        });
    });
    QObject::connect(ui->bafficher_primes_e, &QPushButton::clicked, this, [this]() {

        int mois  = this->ui->combomois_prime_e->currentIndex() + 1;
        int annee = this->ui->spinannee_prime_e->value();

        QSqlQueryModel *model = Performance::afficherParMois(mois, annee);

        this->ui->tableView_primes_e->setModel(model);
        this->ui->tableView_primes_e->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->ui->tableView_primes_e->resizeColumnsToContents();
    });


    QObject::connect(ui->bperformance_e, &QPushButton::clicked, this, [this]() {
        QObject::connect(this->ui->bperformance_e, &QPushButton::clicked, this, [this]() {

            // 1) Récupérer la ligne sélectionnée dans le tableau des employés
            int row = this->ui->tableWidget_e->currentRow();
            if (row < 0) {
                QMessageBox::warning(nullptr, tr("Attention"),
                                     tr("Veuillez d'abord sélectionner un employé."));
                return;
            }

            // 2) Récupérer l'ID de l'employé (colonne 0 = ID)
            QTableWidgetItem *itemId = this->ui->tableWidget_e->item(row, 0);
            if (!itemId) {
                QMessageBox::warning(nullptr, tr("Erreur"),
                                     tr("Impossible de récupérer l'identifiant de l'employé."));
                return;
            }
            int idEmp = itemId->text().toInt();

            // (optionnel) récupérer nom/prénom pour afficher dans un label
            QTableWidgetItem *itemNom    = this->ui->tableWidget_e->item(row, 1);
            QTableWidgetItem *itemPrenom = this->ui->tableWidget_e->item(row, 2);
            QString nomComplet = QString("%1 %2")
                                     .arg(itemPrenom ? itemPrenom->text() : "")
                                     .arg(itemNom ? itemNom->text() : "");
            // si tu as un label sur la page performance :
            this->ui->label_emp_perf->setText(nomComplet);

            // 3) Charger uniquement les performances de cet employé
            QSqlQueryModel *model = Performance::afficherParEmploye(idEmp);
            this->ui->tableView_primes_e->setModel(model);

            // 4) Adapter les colonnes à la largeur du tableau
            this->ui->tableView_primes_e->horizontalHeader()
                ->setSectionResizeMode(QHeaderView::Stretch);

            // 5) Passer à la page "performance" dans le QStackedWidget
            this->ui->stackedWidget->setCurrentWidget(this->ui->performance_e);
        });


    });
    QObject::connect(this->ui->bretour_performance_e, &QPushButton::clicked, this, [this]() {
        this->retour();
    });


    QObject::connect(ui->bajouter_e, &QPushButton::clicked, this, [this]() {
        this->chargerDepuisUI();
        if (!this->verifierChamps()) return;
        if (this->ajouter()){
            this->verif();
            this->afficherDansTable();}
    });
    QObject::connect(ui->bmodifier_e, &QPushButton::clicked, this, [this]() {
        this->chargerDepuisUI();
        if (this->modifier())
            this->afficherDansTable();
    });
    QObject::connect(this->ui->tableWidget_e, &QTableWidget::cellClicked,
                     this, [this](int /*row*/, int /*column*/) {
                         this->remplirChampsDepuisTable();
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

    QObject::connect(ui->linerechercher_e, &QLineEdit::textChanged,
                     this, [this](const QString &) {
                         this->rechercherParNom();
                     });

    QObject::connect(ui->bstatistique_e, &QPushButton::clicked, this, [this]() {
        this->afficherStatistiques();

    });

    QObject::connect(ui->bretour_stats_e, &QPushButton::clicked, this, [this]() {
        this->retour();
    });
    QObject::connect(ui->bquitter_e, &QPushButton::clicked, this, [this]() {
        this->quitter();
    });
    QObject::connect(ui->bconnexion, &QPushButton::clicked, this, [this]() {
        this->seConnecter();
    });
    QObject::connect(ui->bannulercnx, &QPushButton::clicked, this, [this]() {
        this->annulercnx();
    });
    QObject::connect(ui->bquitter, &QPushButton::clicked, this, [this]() {
        this->quitter();
    });
    QTimer::singleShot(0, this, [this]() {
        qDebug() << "Appel automatique de afficherDansTable() au démarrage";
        this->afficherDansTable();
    });
    QObject::connect(ui->bverifier_code, &QPushButton::clicked, this, [this]() {
        this->verifierCodeConfirmation();
    });





}
void employe::verif(){
    ui->stackedWidget->setCurrentIndex(6);
}
void employe::quitter(){
    QApplication::quit();
}
// --------------------- Se Connecter -------------------------------
void employe::seConnecter()
{
    // Récupération et nettoyage des champs
    QString id = ui->lineid_e_3->text().trimmed();
    QString password = ui->linepassword->text().trimmed();

    // Vérifications de base
    if (id.isEmpty()) {
        QMessageBox::warning(nullptr, "Authentification", "Veuillez entrer votre id.");
        return;
    }
    if (password.isEmpty()) {
        QMessageBox::warning(nullptr, "Authentification", "Veuillez entrer un mot de passe.");
        return;
    }

    // Préparation de la requête
    QSqlQuery query;
    query.prepare("SELECT id_employe, nom, prenom, email, num_tel, poste "
                  "FROM employe "
                  "WHERE id_employe = :id AND password = :password");
    query.bindValue(":id", id.toInt());
    query.bindValue(":password", password);

    // Exécution
    if (!query.exec()) {
        QString message = traduireErreurOracle(query.lastError().text());
        QMessageBox::critical(nullptr, "Erreur SQL", message);
        return;
    }
    if (query.next()) {
        // Connexion réussie
        QMessageBox::information(nullptr, "Authentification", "Connexion réussie !");
        ui->stackedWidget->setCurrentIndex(0);
        return;
    } else {
        // Aucun résultat → mauvais id/mot de passe
        QMessageBox::warning(nullptr, "Authentification", "ID ou mot de passe incorrect.");
    }
}
void employe::annulercnx(){
    ui->lineid_e_3->clear();
    ui->linepassword->clear();
    return;
}





// -------------------- Charger les données depuis l'UI --------------------
void employe::chargerDepuisUI()
{
    id_employe = ui->lineid_e->text().toInt();
    nom = ui->linenom_e->text();
    prenom = ui->lineprenon_e->text();
    email = ui->lineemail_e->text();
    num_tel = ui->linetel_e->text();
    poste = ui->lineposte_e->text();
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
    qDebug() << "Email saisi =" << email;
    QRegularExpression regexEmail(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
    if (!regexEmail.match(email).hasMatch()) {
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
void employe::retour(){
    ui->stackedWidget->setCurrentWidget(ui->employe);

}


void employe::rechercherParNom()
{
    QString nom = ui->linerechercher_e->text().trimmed();

    // Si la zone de recherche est vide → on réaffiche toute la liste
    if (nom.isEmpty()) {
        this->afficherDansTable();
        return;
    }

    QSqlQuery query;
    query.prepare(
        "SELECT id_employe, nom, prenom, email, num_tel, poste "
        "FROM employe "
        "WHERE LOWER(nom) LIKE LOWER(:nom)"
        );

    // Recherche "caractère par caractère" → préfixe
    // "a" → tous les noms qui commencent par "a"
    query.bindValue(":nom", nom + "%");

    if (!query.exec()) {
        QString message = traduireErreurOracle(query.lastError().text());
        QMessageBox::critical(nullptr, "Erreur SQL", message);
        return;
    }

    // Vider le tableau puis le remplir avec les résultats filtrés
    ui->tableWidget_e->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tableWidget_e->insertRow(row);
        for (int col = 0; col < 6; ++col) {
            ui->tableWidget_e->setItem(
                row,
                col,
                new QTableWidgetItem(query.value(col).toString())
                );
        }
        row++;
    }
}


// -------------------- Ajouter un employé --------------------
bool employe::ajouter()
{
    if(verifierChamps()){

    // 2) Générer un code de confirmation (6 chiffres)
    int code = QRandomGenerator::global()->bounded(100000, 999999);
    QString codeStr = QString::number(code);


    QSqlQuery query;
    query.prepare("INSERT INTO employe (id_employe, nom, prenom, email, num_tel, poste, password,email_verifie, code_confirmation) "
                  "VALUES (:id, :nom, :prenom, :email, :num_tel, :poste, :password, 0, :code)");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":poste", poste);
    query.bindValue(":password", password);
    query.bindValue(":code", codeStr);


    if (!query.exec()) {
        QString message = traduireErreurOracle(query.lastError().text());
    QMessageBox::critical(nullptr, "Erreur SQL", message);
        return false;
    }
    if (!envoyerMailConfirmation(email, codeStr)) {
        QMessageBox::warning(nullptr, "Email",
                             "Employé ajouté, mais impossible d'envoyer l'email de confirmation.");
    } else {
        QMessageBox::information(nullptr, "Email",
                                 "Employé ajouté.\nUn email de confirmation a été envoyé.");
    }

    QMessageBox::information(nullptr, "Succès", "Employé ajouté avec succès !");
    return true;
    }
    else {return false;}
}
bool employe::envoyerMailConfirmation(const QString &destEmail, const QString &code)
{
    // *** CONFIG GMAIL ***
    const QString smtpHost = "smtp.gmail.com";        // ***
    const int smtpPort = 465;                         // *** SSL direct
    const QString smtpUser = "ademo.belkhiro@gmail.com";   // *** ton adresse Gmail
    const QString smtpPass = "xjns kcrt fjce wmeh";    // *** mot de passe d'application

    QSslSocket socket;

    // Connexion SSL directe (pas STARTTLS)
    socket.connectToHostEncrypted(smtpHost, smtpPort);
    if (!socket.waitForEncrypted(10000)) {
        QMessageBox::critical(nullptr, "SMTP",
                              "Impossible de se connecter au serveur SMTP : "
                                  + socket.errorString());
        return false;
    }

    auto lireReponse = [&socket]() {
        if (!socket.waitForReadyRead(10000))
            return QByteArray();
        QByteArray all = socket.readAll();
        // qDebug() << "SMTP RECV:" << all;
        return all;
    };

    auto envoyerLigne = [&socket, &lireReponse](const QString &line) {
        // qDebug() << "SMTP SEND:" << line;
        socket.write(line.toUtf8() + "\r\n");
        socket.flush();
        return lireReponse();
    };

    // 1) Bannière
    lireReponse();

    // 2) EHLO
    envoyerLigne("EHLO qt-client");

    // 3) AUTH LOGIN
    envoyerLigne("AUTH LOGIN");
    envoyerLigne(smtpUser.toUtf8().toBase64());
    envoyerLigne(smtpPass.toUtf8().toBase64());

    // 4) MAIL FROM / RCPT TO / DATA
    envoyerLigne("MAIL FROM:<" + smtpUser + ">");
    envoyerLigne("RCPT TO:<" + destEmail + ">");
    envoyerLigne("DATA");

    // 5) Corps du mail
    QString message;
    message += "Subject: Confirmation de votre compte\r\n";
    message += "From: <" + smtpUser + ">\r\n";
    message += "To: <" + destEmail + ">\r\n";
    message += "MIME-Version: 1.0\r\n";
    message += "Content-Type: text/plain; charset=UTF-8\r\n";
    message += "\r\n";  // ligne vide = début du corps
    message += "Bonjour,\r\n\r\n";
    message += "Votre code de confirmation est : " + code + "\r\n\r\n";
    message += "Merci.\r\n";

    socket.write(message.toUtf8());
    socket.write("\r\n.\r\n");
    socket.flush();
    lireReponse();  // réponse après DATA

    // 6) QUIT
    envoyerLigne("QUIT");
    socket.disconnectFromHost();


    return true;
}

void employe::verifierCodeConfirmation()
{
    QString idStr   = ui->lineid_conf->text().trimmed();      // QLineEdit pour l'id
    QString codeStr = ui->linecode_conf->text().trimmed();    // QLineEdit pour le code
    qDebug() << "code saisi =" << codeStr;
    if (idStr.isEmpty() || codeStr.isEmpty()) {
        QMessageBox::warning(nullptr, "Confirmation",
                             "Veuillez saisir votre ID et le code de confirmation.");
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT code_confirmation FROM employe WHERE id_employe = :id");
    q.bindValue(":id", idStr);

    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de la vérification du code : " + q.lastError().text());
        return;
    }

    if (!q.next()) {
        QMessageBox::warning(nullptr, "Confirmation",
                             "Aucun employé trouvé avec cet ID.");
        return;
    }

    QString codeBD = q.value(0).toString().trimmed();

    if (codeBD == codeStr) {
        // Optionnel : marquer l'email comme vérifié
        QSqlQuery update;
        update.prepare("UPDATE employe SET email_verifie = 1 WHERE id_employe = :id");
        update.bindValue(":id", idStr);
        if (!update.exec()) {
            QMessageBox::warning(nullptr, "Confirmation",
                                 "Code correct, mais impossible de mettre à jour le statut : "
                                     + update.lastError().text());
        } else {
            QMessageBox::information(nullptr, "Confirmation",
                                     "Email confirmé avec succès ✅");
        }
    } else {
        QMessageBox::warning(nullptr, "Confirmation",
                             "Code de confirmation incorrect ❌");
    }
    this->retour();
}
// -------------------- Modifier un employé --------------------
bool employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, "
                  "email=:email, num_tel=:num_tel, poste=:poste WHERE id_employe=:id");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":poste", poste.toUpper());



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
    ui->stackedWidget->setCurrentWidget(ui->stats_e);

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
    QGroupBox *box = ui->groupBox_stats; // 🔁 remplace par le nom exact si différent

    // Nettoyer l'ancien contenu/layout du groupbox
    if (QLayout *old = box->layout()) {
        QLayoutItem *it;
        while ((it = old->takeAt(0)) != nullptr) {
            if (QWidget *w = it->widget()) w->deleteLater();
            delete it;
        }
        delete old;
    }

    // Nouveau layout pour le groupbox
    auto *layout = new QVBoxLayout();
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);
    layout->addWidget(chartView);
    box->setLayout(layout);
}
void employe::remplirChampsDepuisTable()
{
    int row = this->ui->tableWidget_e->currentRow();
    if (row < 0)
        return;  // rien sélectionné

    // Récupérer chaque cellule de la ligne
    QTableWidgetItem *itemId     = this->ui->tableWidget_e->item(row, 0);
    QTableWidgetItem *itemNom    = this->ui->tableWidget_e->item(row, 1);
    QTableWidgetItem *itemPrenom = this->ui->tableWidget_e->item(row, 2);
    QTableWidgetItem *itemEmail  = this->ui->tableWidget_e->item(row, 3);
    QTableWidgetItem *itemTel    = this->ui->tableWidget_e->item(row, 4);
    QTableWidgetItem *itemPoste  = this->ui->tableWidget_e->item(row, 5);

    // Remplir les QLineEdit (⚠️ adapte les noms à ton UI)
    if (itemId)
        this->ui->lineid_e->setText(itemId->text());
    if (itemNom)
        this->ui->linenom_e->setText(itemNom->text());      // ex: linenom_e
    if (itemPrenom)
        this->ui->lineprenon_e->setText(itemPrenom->text());
    if (itemEmail)
        this->ui->lineemail_e->setText(itemEmail->text());
    if (itemTel)
        this->ui->linetel_e->setText(itemTel->text());
    if (itemPoste)
        this->ui->lineposte_e->setText(itemPoste->text());
}


