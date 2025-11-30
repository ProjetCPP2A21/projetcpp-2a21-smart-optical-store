#include "employe.h"
#include "authentification.h"
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
#include <QRegularExpression>
#include <QCompleter>  // ⭐ AJOUT pour l'auto-complétion
#include <QStringListModel>  // ⭐ AJOUT pour l'auto-complétion

//client
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
//produit
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
#include <QTextDocument>
#include <QFileDialog>
#include <QDateTime>
#include <QPageSize>
#include <QPageLayout>

//produit
using qrcodegen::QrCode;

optismart::optismart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::optismart)
    , fourn()           // ⭐ PREMIER - même ordre que dans .h
    , Ptmp()            // ⭐ DEUXIÈME
    , selectedIdProduit(-1) // ⭐ TROISIÈME
    , cinSelectionne("") // ⭐ QUATRIÈME
    , ord()             // ⭐ CINQUIÈME
    , m_mapWidget(nullptr)  // ⭐ AJOUT - initialiser le pointeur
    , m_mapDialog(nullptr)
{
    ui->setupUi(this);

    // ⭐ AJOUT: Configuration fournisseur (DOIT ÊTRE AVANT chargerProduits())
  //  setupInterfaceFournisseur();
    setupCarteFournisseurs();
    actualiserAffichageFournisseur();

   // chargerProduits();

    //client
    connect(ui->tableWidget_c->horizontalHeader(), &QHeaderView::sectionClicked, this, &optismart::recolorerToutesLesLignes);
    connect(ui->tableWidget_c, &QTableWidget::cellChanged, this, &optismart::mettreAJourCategorie);

    // Configuration du tableWidget_c
    ui->tableWidget_c->setColumnCount(9);
    ui->tableWidget_c->setHorizontalHeaderLabels(QStringList()
                                                 << "ID Client" << "Nom" << "Prénom"
                                                 << "Date Naissance" << "Email" << "Téléphone"
                                                 << "Date Inscription" << "Points Fidélité" << "Catégorie");
    //chargerClients();

    //  ajuster la taille des colonnes automatiquement
    ui->tableWidget_c->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QRegularExpression regexCIN("[0-9]{1,8}");
    QRegularExpressionValidator *validatorCIN = new QRegularExpressionValidator(regexCIN, this);
    ui->linecin_o->setValidator(validatorCIN);
    ui->linecin_o->setPlaceholderText("8 chiffres maximum");

    // Validateur pour nom, prénom, médecin (lettres seulement)
    QRegularExpression regexLettres("^[a-zA-ZÀ-ÿ\\s\\-']*$");
    QRegularExpressionValidator *validatorLettres = new QRegularExpressionValidator(regexLettres, this);

    ui->linenom_o->setValidator(validatorLettres);
    ui->lineprenom_o->setValidator(validatorLettres);
    ui->linemedecin_o->setValidator(validatorLettres);

    // ====================== PARTIE PRODUIT ======================
    ui->typeEdit->setPlaceholderText("Ex: Lunettes Homme / Femme / Enfant / Lentilles");
    ui->tableWidget_p_2->setModel(Ptmp.afficher());

    // Configuration de la date pour ordonnance
    ui->linedate_o->setDate(QDate::currentDate());
    // ==================== CHARGEMENT DES DONNÉES ====================

    actualiserAffichageFournisseur();  // Fournisseur
    chargerProduits();                 // Produit
    afficher_client();                 // Client
    actualiserAffichageOrdonnance();   // Ordonnance


    //client
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index) {
        if (index == 1) {
            // Appel de ta fonction d'affichage automatique
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
}

optismart::~optismart()
{
    delete ui;
}

//------------------------------fournisseur-------------------------------

//------------------------------fournisseur-------------------------------

// ==================== CONFIGURATION FOURNISSEUR ====================

// Dans le constructeur optismart::optismart(), ajoutez après setupInterfaceFournisseur() :


// Ajoutez cette méthode pour configurer la carte :
void optismart::setupCarteFournisseurs()
{
    m_mapDialog = new QDialog(this);
    m_mapDialog->setWindowTitle("Carte des Fournisseurs - Tunisie");
    m_mapDialog->resize(1000, 700);

    m_mapWidget = new QQuickWidget(m_mapDialog);
    m_mapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    qDebug() << "=== DÉBUT CHARGEMENT CARTE QML ===";

    // Charger depuis les ressources
    QUrl qmlUrl("qrc:/CarteFournisseurs.qml");
    qDebug() << "Chargement QML depuis:" << qmlUrl;

    m_mapWidget->setSource(qmlUrl);

    // Vérifier le statut
    qDebug() << "Statut QML:" << m_mapWidget->status();

    if (m_mapWidget->status() == QQuickWidget::Error) {
        qDebug() << "❌ ERREURS QML DÉTECTÉES:";
        QList<QQmlError> errors = m_mapWidget->errors();
        for (const QQmlError &error : errors) {
            qDebug() << " - " << error.toString();
            qDebug() << "   Fichier:" << error.url();
            qDebug() << "   Ligne:" << error.line();
            qDebug() << "   Description:" << error.description();
        }

        // Message d'erreur détaillé
        QString messageErreur = "Erreur de chargement de la carte QML:\n";
        for (const QQmlError &error : errors) {
            messageErreur += error.description() + "\n";
        }
        QMessageBox::critical(this, "Erreur Carte", messageErreur);

    } else if (m_mapWidget->status() == QQuickWidget::Ready) {
        qDebug() << "✅ QML CHARGÉ AVEC SUCCÈS";
    } else if (m_mapWidget->status() == QQuickWidget::Loading) {
        qDebug() << "⏳ QML EN COURS DE CHARGEMENT";
    } else if (m_mapWidget->status() == QQuickWidget::Null) {
        qDebug() << "❌ QML NON CHARGÉ";
        QMessageBox::warning(this, "Erreur", "Fichier QML non chargé - Vérifiez ressources.qrc");
    }

    QVBoxLayout *layout = new QVBoxLayout(m_mapDialog);
    layout->addWidget(m_mapWidget);
    m_mapDialog->setLayout(layout);

    qDebug() << "=== FIN CHARGEMENT CARTE QML ===";
}

// Ajoutez le slot pour le bouton carte :
void optismart::on_bcarte_f_clicked()
{
    Fournisseur fourn;
    QList<QVariantMap> fournisseursData = fourn.getAllFournisseursForMap();

    if (fournisseursData.isEmpty()) {
        QMessageBox::information(this, "Carte", "Aucun fournisseur à afficher sur la carte!");
        return;
    }

    QQuickItem *rootObject = m_mapWidget->rootObject();
    if (rootObject) {
        QMetaObject::invokeMethod(rootObject, "updateFournisseurs",
                                  Q_ARG(QVariant, QVariant::fromValue(fournisseursData)));
        m_mapDialog->show();
        m_mapDialog->raise();
        m_mapDialog->activateWindow();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger la carte QML");
    }
}
void optismart::actualiserAffichageFournisseur()
{
    if (ui->tableWidget_4) {
        fourn.afficher(ui->tableWidget_4);
    }
}

void optismart::clearFieldsFournisseur()
{
    ui->id_le->clear();
    ui->nom_le->clear();
    ui->adresse_le->clear();
    ui->email_le->clear();
    ui->telephone_le->clear();
    ui->cp_le->clear();

    // Réinitialiser les styles
    ui->nom_le->setStyleSheet("");
    ui->email_le->setStyleSheet("");
    ui->telephone_le->setStyleSheet("");
    ui->adresse_le->setStyleSheet("");
    ui->cp_le->setStyleSheet("");

    // Réinitialiser les tooltips
    ui->nom_le->setToolTip("");
    ui->email_le->setToolTip("");
    ui->telephone_le->setToolTip("");
    ui->adresse_le->setToolTip("");
    ui->cp_le->setToolTip("");

    // Remettre le focus sur le premier champ
    ui->id_le->setFocus();
}

// ==================== CRUD FOURNISSEUR ====================

void optismart::on_bajouter_f_clicked()
{
    qDebug() << "=== CLICK SUR BAJOUTER_F ===";

    // Récupération des valeurs depuis les line edits
    QString ID_FOURNISSEUR = ui->id_le->text();
    QString NOM = ui->nom_le->text();
    QString ADRESSE = ui->adresse_le->text();
    QString EMAIL = ui->email_le->text();
    QString NUMERO_TELEPHONE = ui->telephone_le->text();
    QString CONDITION_PAIEMENT = ui->cp_le->text();

    // Validation des champs obligatoires
    if (ID_FOURNISSEUR.isEmpty() || NOM.isEmpty() || NUMERO_TELEPHONE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir les champs ID_FOURNISSEUR, NOM et NUMERO_TELEPHONE!");
        return;
    }

    // Validation des données
    if (!Fournisseur::validerNom(NOM)) {
        QMessageBox::warning(this, "Nom invalide",
                             "Le nom ne doit contenir que des lettres et espaces (accents autorisés)\n"
                             "Longueur: 2 à 50 caractères");
        ui->nom_le->setFocus();
        return;
    }

    if (!ADRESSE.isEmpty() && !Fournisseur::validerAdresse(ADRESSE)) {
        QMessageBox::warning(this, "Adresse invalide",
                             "L'adresse doit contenir entre 5 et 100 caractères");
        ui->adresse_le->setFocus();
        return;
    }

    if (!EMAIL.isEmpty() && !Fournisseur::validerEmail(EMAIL)) {
        QMessageBox::warning(this, "Email invalide",
                             "Format d'email invalide\n"
                             "Exemple: exemple@domaine.fr");
        ui->email_le->setFocus();
        return;
    }

    if (!Fournisseur::validerTelephone(NUMERO_TELEPHONE)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir exactement 8 chiffres");
        ui->telephone_le->setFocus();
        return;
    }

    if (!CONDITION_PAIEMENT.isEmpty() && !Fournisseur::validerConditionPaiement(CONDITION_PAIEMENT)) {
        QMessageBox::warning(this, "Condition de paiement invalide",
                             "Condition de paiement non valide!\n\n"
                             "Valeurs acceptées:\n"
                             "• payé\n• 30 jours\n• 60 jours\n• comptant\n• avance\n• autre");
        ui->cp_le->setFocus();
        return;
    }

    if (ID_FOURNISSEUR.length() > 50) {
        QMessageBox::warning(this, "ID_FOURNISSEUR trop long", "L'ID_FOURNISSEUR ne doit pas dépasser 50 caractères!");
        return;
    }

    // Création et ajout du fournisseur
    Fournisseur nouveauFournisseur(ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT);

    if (nouveauFournisseur.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès!");
        actualiserAffichageFournisseur();
        clearFieldsFournisseur();
        qDebug() << "✅ Fournisseur ajouté et affichage actualisé";
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout du fournisseur!\n"
                              "Vérifiez que:\n"
                              "- L'ID_FOURNISSEUR n'existe pas déjà\n"
                              "- Tous les champs sont valides");
        qDebug() << "❌ Erreur lors de l'ajout";
    }
}

void optismart::on_bmodifier_f_clicked()
{
    qDebug() << "=== CLICK SUR BMODIFIER_F ===";

    // Récupération des valeurs depuis les line edits
    QString ID_FOURNISSEUR = ui->id_le->text();
    QString NOM = ui->nom_le->text();
    QString ADRESSE = ui->adresse_le->text();
    QString EMAIL = ui->email_le->text();
    QString NUMERO_TELEPHONE = ui->telephone_le->text();
    QString CONDITION_PAIEMENT = ui->cp_le->text();

    // Validation de l'ID (obligatoire)
    if (ID_FOURNISSEUR.isEmpty()) {
        QMessageBox::warning(this, "ID manquant",
                             "Veuillez sélectionner un fournisseur dans le tableau!");
        return;
    }

    // Validation NOM (obligatoire)
    if (NOM.isEmpty()) {
        QMessageBox::warning(this, "Nom manquant", "Le nom est obligatoire!");
        ui->nom_le->setFocus();
        return;
    }

    if (!Fournisseur::validerNom(NOM)) {
        QMessageBox::warning(this, "Nom invalide",
                             "Le nom ne doit contenir que des lettres et espaces (accents autorisés)\n"
                             "Longueur: 2 à 50 caractères");
        ui->nom_le->setFocus();
        return;
    }

    // Validation ADRESSE
    if (!ADRESSE.isEmpty() && !Fournisseur::validerAdresse(ADRESSE)) {
        QMessageBox::warning(this, "Adresse invalide",
                             "L'adresse doit contenir entre 5 et 100 caractères");
        ui->adresse_le->setFocus();
        return;
    }

    // Validation EMAIL
    if (!EMAIL.isEmpty() && !Fournisseur::validerEmail(EMAIL)) {
        QMessageBox::warning(this, "Email invalide",
                             "Format d'email invalide\n"
                             "Exemple: exemple@domaine.fr");
        ui->email_le->setFocus();
        return;
    }

    // Validation NUMERO_TELEPHONE (obligatoire)
    if (NUMERO_TELEPHONE.isEmpty()) {
        QMessageBox::warning(this, "Téléphone manquant", "Le numéro de téléphone est obligatoire!");
        ui->telephone_le->setFocus();
        return;
    }

    if (!Fournisseur::validerTelephone(NUMERO_TELEPHONE)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir exactement 8 chiffres");
        ui->telephone_le->setFocus();
        return;
    }

    // Validation CONDITION_PAIEMENT
    if (!CONDITION_PAIEMENT.isEmpty() && !Fournisseur::validerConditionPaiement(CONDITION_PAIEMENT)) {
        QMessageBox::warning(this, "Condition de paiement invalide",
                             "Condition de paiement non valide!\n\n"
                             "Valeurs acceptées:\n"
                             "• payé\n• 30 jours\n• 60 jours\n• comptant\n• avance\n• autre");
        ui->cp_le->setFocus();
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir modifier le fournisseur:\n"
                                  "ID: " + ID_FOURNISSEUR + "\n"
                                                         "Nom: " + NOM + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Modification du fournisseur
        if (fourn.modifier(ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT)) {
            QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès!");
            actualiserAffichageFournisseur();
            clearFieldsFournisseur();
            qDebug() << "✅ Fournisseur modifié et affichage actualisé";
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la modification!\n"
                                  "Vérifiez que le fournisseur existe toujours dans la base de données.");
            qDebug() << "❌ Erreur lors de la modification";
        }
    } else {
        qDebug() << "❌ Modification annulée par l'utilisateur";
    }
}

void optismart::on_bsupprimer_f_clicked()
{
    qDebug() << "=== CLICK SUR BSUPPRIMER_F ===";

    // Récupérer l'ID_FOURNISSEUR à supprimer
    QString ID_FOURNISSEUR = ui->id_le->text();

    // Validation
    if (ID_FOURNISSEUR.isEmpty()) {
        QMessageBox::warning(this, "ID_FOURNISSEUR manquant",
                             "Veuillez sélectionner un fournisseur dans le tableau!");
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer le fournisseur avec ID_FOURNISSEUR: " + ID_FOURNISSEUR + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Suppression du fournisseur
        if (fourn.supprimer(ID_FOURNISSEUR)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès!");
            actualiserAffichageFournisseur();
            clearFieldsFournisseur();
            qDebug() << "✅ Fournisseur supprimé et affichage actualisé";
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la suppression!\n"
                                  "Vérifiez que l'ID_FOURNISSEUR existe dans la base de données.");
            qDebug() << "❌ Erreur lors de la suppression";
        }
    } else {
        qDebug() << "❌ Suppression annulée par l'utilisateur";
    }
}

// ==================== FONCTIONNALITÉS AVANCÉES FOURNISSEUR ====================

void optismart::on_bnouveau_f_clicked()
{
    clearFieldsFournisseur();
    ui->tableWidget_4->clearSelection();
    QMessageBox::information(this, "Nouveau", "Formulaire prêt pour un nouveau fournisseur!");
}

void optismart::on_brechercher_f_clicked()
{
    QString idRecherche = ui->recherche_le->text().trimmed();

    // Si le champ recherche est vide, afficher TOUS les fournisseurs
    if (idRecherche.isEmpty()) {
        actualiserAffichageFournisseur();
        QMessageBox::information(this, "Recherche", "Affichage de tous les fournisseurs");
        return;
    }

    bool trouve = fourn.rechercherParId(idRecherche, ui->tableWidget_4);

    if (trouve) {
        // Sélectionner la ligne trouvée
        ui->tableWidget_4->selectRow(0);
        ui->tableWidget_4->scrollToItem(ui->tableWidget_4->item(0, 0), QAbstractItemView::PositionAtCenter);

        // Remplir automatiquement les champs avec les données trouvées
        QTableWidget *table = ui->tableWidget_4;
        QString id = table->item(0, 0)->text();
        QString nom = table->item(0, 1)->text();
        QString adresse = table->item(0, 2)->text();
        QString email = table->item(0, 3)->text();
        QString telephone = table->item(0, 4)->text();
        QString conditionPaiement = table->item(0, 5)->text();

        ui->id_le->setText(id);
        ui->nom_le->setText(nom);
        ui->adresse_le->setText(adresse);
        ui->email_le->setText(email);
        ui->telephone_le->setText(telephone);
        ui->cp_le->setText(conditionPaiement);

        // Appliquer la validation pour mettre à jour les styles
        on_nom_le_textChanged(nom);
        on_email_le_textChanged(email);
        on_telephone_le_textChanged(telephone);
        on_cp_le_textChanged(conditionPaiement);

        QMessageBox::information(this, "Recherche",
                                 "Fournisseur trouvé avec l'ID: " + idRecherche);
    } else {
        QMessageBox::information(this, "Recherche",
                                 "Aucun fournisseur trouvé avec l'ID: " + idRecherche);
        // Réafficher tous les fournisseurs après une recherche infructueuse
        actualiserAffichageFournisseur();
    }
}

void optismart::on_btrier_f_clicked()
{
    QTableWidget *table = ui->tableWidget_4;
    if (!table || table->rowCount() == 0) {
        QMessageBox::information(this, "Tri", "Aucune donnée à trier!");
        return;
    }

    // Tri numérique croissant direct
    fourn.trierParIdNumerique(table, true);
    QMessageBox::information(this, "Tri", "Liste triée par ID numérique (ordre croissant)");
}

void optismart::afficherGraphiqueStatistiques()
{
    QMap<QString, int> stats = fourn.getStatistiquesParConditionPaiement();
    int total = 0;

    for (int count : stats) {
        total += count;
    }

    // Vérifier si le graphicsView existe
    if (!ui->graphicsView_statistiques) {
        QMessageBox::warning(this, "Erreur", "Graphics View non trouvé!");
        return;
    }

    // Créer un QChartView (qui est un QGraphicsView)
    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    // Créer la série de données pour le camembert
    QPieSeries *series = new QPieSeries();

    // Couleurs pour les segments
    QList<QColor> colors = {
        QColor("#FF6384"), QColor("#36A2EB"), QColor("#FFCE56"),
        QColor("#4BC0C0"), QColor("#9966FF"), QColor("#FF9F40")
    };

    int colorIndex = 0;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString condition = it.key();
        int count = it.value();
        double pourcentage = total > 0 ? (count * 100.0 / total) : 0;

        QString label = QString("%1\n%2 (%3%)")
                            .arg(condition)
                            .arg(count)
                            .arg(QString::number(pourcentage, 'f', 1));

        QPieSlice *slice = series->append(label, count);
        slice->setColor(colors[colorIndex % colors.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);

        colorIndex++;
    }

    // Créer le chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par Condition de Paiement - Total: " + QString::number(total));
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Configurer le chartView
    chartView->setChart(chart);

    // Remplacer le contenu du graphicsView par le chartView
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(chartView);
    ui->graphicsView_statistiques->setScene(scene);
}

void optismart::on_bstatistique_f_clicked()
{
    // Afficher les statistiques dans le graphique
    afficherGraphiqueStatistiques();

    // Afficher aussi un résumé textuel
    QMap<QString, int> stats = fourn.getStatistiquesParConditionPaiement();
    int total = 0;

    for (int count : stats) {
        total += count;
    }

    QString message = "📊 STATISTIQUES FOURNISSEURS\n\n";
    message += QString("Total fournisseurs: %1\n\n").arg(total);
    message += "Répartition par condition de paiement:\n";

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString condition = it.key();
        int count = it.value();
        double pourcentage = total > 0 ? (count * 100.0 / total) : 0;

        message += QString("• %1: %2 fournisseurs (%3%)\n")
                       .arg(condition)
                       .arg(count)
                       .arg(QString::number(pourcentage, 'f', 1));
    }

    QMessageBox::information(this, "Détails Statistiques", message);
}

void optismart::on_bexporter_f_clicked()
{
    // Demander où sauvegarder le PDF
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/liste_fournisseurs.pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    // Créer le document PDF
    QTextDocument document;

    // Construire le contenu HTML simple
    QString htmlContent;
    htmlContent += "<html><body>";
    htmlContent += "<h1 align='center'>LISTE DES FOURNISSEURS</h1>";
    htmlContent += "<p align='center'><i>Exporté le: " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</i></p>";
    htmlContent += "<table border='1' cellpadding='5' width='100%'>";
    htmlContent += "<tr style='background-color: #f0f0f0; font-weight: bold;'>";
    htmlContent += "<th>ID</th><th>Nom</th><th>Adresse</th><th>Email</th><th>Téléphone</th><th>Condition Paiement</th>";
    htmlContent += "</tr>";

    // Remplir avec les données du tableau
    QTableWidget *table = ui->tableWidget_4;
    for (int row = 0; row < table->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            htmlContent += "<td>" + (item ? item->text() : "") + "</td>";
        }
        htmlContent += "</tr>";
    }

    htmlContent += "</table>";
    htmlContent += "<p><br>Total fournisseurs: " + QString::number(table->rowCount()) + "</p>";
    htmlContent += "</body></html>";

    // Définir le contenu HTML
    document.setHtml(htmlContent);

    // Générer le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));

    // Imprimer le document
    document.print(&printer);

    QMessageBox::information(this, "Export PDF",
                             "Liste exportée en PDF avec succès!\nFichier: " + fileName);
}

// ==================== VALIDATION TEMPS RÉEL FOURNISSEUR ====================

void optismart::on_nom_le_textChanged(const QString &text)
{
    bool estValide = Fournisseur::validerNom(text);
    afficherErreurChampFournisseur(ui->nom_le, estValide,
                                   "Le nom ne doit contenir que des lettres et espaces (accents autorisés)");
}

void optismart::on_email_le_textChanged(const QString &text)
{
    bool estValide = Fournisseur::validerEmail(text);
    afficherErreurChampFournisseur(ui->email_le, estValide,
                                   "Format d'email invalide (ex: exemple@domaine.fr)");
}

void optismart::on_telephone_le_textChanged(const QString &text)
{
    bool estValide = Fournisseur::validerTelephone(text);
    afficherErreurChampFournisseur(ui->telephone_le, estValide,
                                   "Le numéro doit être 8 chiffres");
}

void optismart::on_cp_le_textChanged(const QString &text)
{
    bool estValide = Fournisseur::validerConditionPaiement(text);
    afficherErreurChampFournisseur(ui->cp_le, estValide,
                                   "Condition de paiement invalide!\n"
                                   "Valeurs acceptées:\n"
                                   "• payé\n• 30 jours\n• 60 jours\n• comptant\n• avance\n• autre");
}

void optismart::on_tableWidget_4_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int row = item->row();
    QTableWidget *table = ui->tableWidget_4;

    // Récupérer toutes les données de la ligne
    QString id = table->item(row, 0)->text();
    QString nom = table->item(row, 1)->text();
    QString adresse = table->item(row, 2)->text();
    QString email = table->item(row, 3)->text();
    QString telephone = table->item(row, 4)->text();
    QString conditionPaiement = table->item(row, 5)->text();

    // Remplir les champs avec les données
    ui->id_le->setText(id);
    ui->nom_le->setText(nom);
    ui->adresse_le->setText(adresse);
    ui->email_le->setText(email);
    ui->telephone_le->setText(telephone);
    ui->cp_le->setText(conditionPaiement);

    // Appliquer la validation pour mettre à jour les styles
    on_nom_le_textChanged(nom);
    on_email_le_textChanged(email);
    on_telephone_le_textChanged(telephone);
    on_cp_le_textChanged(conditionPaiement);

    qDebug() << "✅ Données du fournisseur" << id << "chargées dans le formulaire";
}

void optismart::afficherErreurChampFournisseur(QLineEdit *champ, bool estValide, const QString &message)
{
    QString style = estValide ?
                        "border: 2px solid green; background-color: #f0fff0;" :
                        "border: 2px solid red; background-color: #fff0f0;";

    champ->setStyleSheet(style);

    if (!estValide && !message.isEmpty()) {
        champ->setToolTip(message);
    } else {
        champ->setToolTip("");
    }
}

//------------------------------client------------------------------------
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

/*void optismart::afficher_client(int id_selectionne)
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
}*/

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
void optismart::on_brechercher_c_clicked()
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

void optismart::on_btrier_c_clicked()
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

void optismart::on_bexporter_c_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (!fileName.isEmpty()) {
        client c;
        c.exporter_client_pdf(fileName);
    }
}


void optismart::afficherStatistiques_client()
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


void optismart::on_bstatistique_c_clicked()
{
    afficherStatistiques_client();
}
//categorie

QString optismart::calculerCategorie(int points)
{
    if (points > 500)
        return "VIP";
    else if (points >= 100)
        return "Régulier";
    else
        return "Nouveau";
}

void optismart::colorerCategorie(QTableWidgetItem *item)
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
void optismart::afficher_client(int id_selectionne)
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


void optismart::chargerClients()
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
void optismart::on_tableWidget_c_cellChanged(int row, int column)
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
void optismart::on_tableWidget_c_horizontalHeader_sectionClicked(int column)
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
void optismart::mettreAJourCategorie(int row, int col)
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

void optismart::recolorerToutesLesLignes()
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

//--------------produit----------
void optismart::chargerProduits()
{
    ui->tableWidget_p_2->setModel(Ptmp.afficher());
    ui->tableWidget_p_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

/* ==================== AJOUTER ==================== */
void optismart::on_ajouterButton_clicked()
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
       chargerProduits();
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
void optismart::on_supprimerButton_clicked()
{
    bool ok;
    int id = ui->idEdit->text().toInt(&ok);
    if (!ok || id <= 0) { QMessageBox::warning(this, "Erreur", "ID invalide"); return; }

    if (Ptmp.supprimer(id)) {
        chargerProduits();
        QMessageBox::information(this, "Succès", "Produit supprimé");
        ui->idEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression échouée");
    }
}

/* ==================== DOUBLE CLIC TABLEAU ==================== */
void optismart::on_tableWidget_p_2_doubleClicked(const QModelIndex &index)
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
void optismart::on_modifierButton_clicked()
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
        chargerProduits();
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
void optismart::on_searchButton_clicked()
{
    QString text = ui->searchIdEdit->text().trimmed();
    if (text.isEmpty()) {
        chargerProduits();
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
        chargerProduits();
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
void optismart::on_statsButton_clicked()
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
void optismart::on_trierButton_clicked()
{
    ui->tableWidget_p_2->setModel(Ptmp.trierParType());
    QMessageBox::information(this, "Tri", "Tableau trié par type (A → Z)");
}

/* ==================== EXPORT WORD ==================== */
/* ==================== EXPORT PDF ==================== */
void optismart::on_exportPdfButton_clicked()
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

    // Construire le contenu HTML simple
    QString htmlContent;
    htmlContent += "<html><body>";
    htmlContent += "<h1 align='center'>LISTE DES PRODUITS OPTISMART</h1>";
    htmlContent += "<p align='center'><i>Exporté le: " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</i></p>";
    htmlContent += "<table border='1' cellpadding='5' width='100%' style='border-collapse: collapse;'>";
    htmlContent += "<tr style='background-color: #1e4620; color: white; font-weight: bold;'>";
    htmlContent += "<th>ID Produit</th><th>Type</th><th>Quantité</th><th>Prix</th><th>Couleur</th>";
    htmlContent += "<th>Épaisseur</th><th>Diamètre</th><th>ID Client</th><th>ID Employé</th><th>ID Fournisseur</th>";
    htmlContent += "</tr>";

    // Remplir avec les données
    for (int row = 0; row < model->rowCount(); ++row) {
        // Alternance des couleurs de ligne
        QString bgColor = (row % 2 == 0) ? "#f8f8f8" : "#ffffff";
        htmlContent += "<tr style='background-color: " + bgColor + ";'>";

        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();
            htmlContent += "<td style='text-align: center; padding: 4px;'>" + text + "</td>";
        }
        htmlContent += "</tr>";
    }

    htmlContent += "</table>";
    htmlContent += "<p style='margin-top: 20px;'><strong>Total produits: " + QString::number(model->rowCount()) + "</strong></p>";
    htmlContent += "<p style='text-align: right; font-style: italic; color: #666;'>Généré par OptiSmart</p>";
    htmlContent += "</body></html>";

    // Définir le contenu HTML
    document.setHtml(htmlContent);

    // Générer le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait);

    // Imprimer le document
    document.print(&printer);

    // Nettoyer
    delete model;

    QMessageBox::information(this, "Export PDF",
                             "✅ Liste des produits exportée en PDF avec succès!\n\nFichier: " + fileName);
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

void optismart::on_genererQrButton_clicked()
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
void optismart::jouerAlerteVocale(int idProduit, const QString &nomProduit, int quantite)
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
void optismart::envoyerSMS(const QString &numeroDestinataire, const QString &message)
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

// ⭐ AJOUT: FONCTIONS POUR ORDONNANCE

void optismart::actualiserAffichageOrdonnance()
{
    if (ui->tableWidget_o) {
        ord.afficherOrdonnance(ui->tableWidget_o);
    }
}

// ⭐ AJOUT: Fonction de validation du CIN
// ⭐ AJOUT: Fonction de validation du CIN
bool optismart::validerCIN(const QString& cin)
{
    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Le CIN est obligatoire!");
        return false;
    }

    if (cin.length() > 8) {
        QMessageBox::warning(this, "CIN invalide", "Le CIN ne doit pas dépasser 8 chiffres!");
        return false;
    }

    // ⭐ CORRECTION: Utiliser QRegularExpression au lieu de QRegExp
    QRegularExpression digitRegex("^[0-9]+$");
    if (!digitRegex.match(cin).hasMatch()) {
        QMessageBox::warning(this, "CIN invalide", "Le CIN doit contenir uniquement des chiffres!");
        return false;
    }

    return true;
}
// ⭐ AJOUT: Fonction de validation pour nom, prénom et médecin
bool optismart::validerNomPrenom(const QString& texte, const QString& champ)
{
    if (texte.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Le " + champ + " est obligatoire!");
        return false;
    }

    // Vérification que ce ne sont que des lettres, espaces et traits d'union
    QRegularExpression lettreRegex("^[a-zA-ZÀ-ÿ\\s\\-']+$");
    if (!lettreRegex.match(texte).hasMatch()) {
        QMessageBox::warning(this, champ + " invalide",
                             "Le " + champ + " doit contenir uniquement des lettres, espaces, traits d'union et apostrophes!");
        return false;
    }

    // Vérification de la longueur raisonnable
    if (texte.length() > 50) {
        QMessageBox::warning(this, champ + " trop long",
                             "Le " + champ + " ne doit pas dépasser 50 caractères!");
        return false;
    }

    return true;
}

void optismart::on_bajouter_o_clicked()
{
    // Récupération des informations saisies
    QString cin = ui->linecin_o->text();
    QString nom = ui->linenom_o->text();
    QString prenom = ui->lineprenom_o->text();
    QString medecin = ui->linemedecin_o->text();
    QDate date = ui->linedate_o->date();

    // ⭐ AJOUT: Validation spécifique du CIN
    if (!validerCIN(cin)) {
        return;
    }

    // Validation des autres champs obligatoires
    if (nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    // Créer et ajouter l'ordonnance
    Ordonnance nouvelleOrdonnance(cin, nom, prenom, medecin, date);
    bool test = nouvelleOrdonnance.ajouterOrdonnance();

    if (test) {
        actualiserAffichageOrdonnance();
        // Vider les champs
        ui->linecin_o->clear();
        ui->linenom_o->clear();
        ui->lineprenom_o->clear();
        ui->linemedecin_o->clear();
        ui->linedate_o->setDate(QDate::currentDate());
        QMessageBox::information(this, "Succès", "Ordonnance ajoutée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de l'ordonnance!");
    }
}

void optismart::on_bsupprimer_o_clicked()
{
    QString cin = ui->linecin_o->text();

    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant",
                             "Veuillez saisir le CIN de l'ordonnance à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Supprimer l'ordonnance avec CIN: " + cin + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = ord.supprimerOrdonnance(cin);
        if (test) {
            actualiserAffichageOrdonnance();
            // Vider les champs
            ui->linecin_o->clear();
            ui->linenom_o->clear();
            ui->lineprenom_o->clear();
            ui->linemedecin_o->clear();
            ui->linedate_o->setDate(QDate::currentDate());
            QMessageBox::information(this, "Succès", "Ordonnance supprimée avec succès!");
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression!");
        }
    }
}

void optismart::on_bmodifier_o_clicked()
{
    if (cinSelectionne.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une ordonnance dans le tableau!");
        return;
    }

    QString nouveauCIN = ui->linecin_o->text();
    QString nom = ui->linenom_o->text();
    QString prenom = ui->lineprenom_o->text();
    QString medecin = ui->linemedecin_o->text();
    QDate date = ui->linedate_o->date();

    // ⭐ AJOUT: Validation spécifique du CIN pour la modification
    if (!validerCIN(nouveauCIN)) {
        return;
    }

    // Validation des autres champs obligatoires
    if (nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Modifier l'ordonnance avec CIN: " + cinSelectionne + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Ordonnance ordonnanceModifiee(nouveauCIN, nom, prenom, medecin, date);
        bool test = ordonnanceModifiee.modifierOrdonnance(cinSelectionne);

        if (test) {
            actualiserAffichageOrdonnance();
            // Vider les champs et réinitialiser
            ui->linecin_o->clear();
            ui->linenom_o->clear();
            ui->lineprenom_o->clear();
            ui->linemedecin_o->clear();
            ui->linedate_o->setDate(QDate::currentDate());
            cinSelectionne = "";
            QMessageBox::information(this, "Succès", "Ordonnance modifiée avec succès!");
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification!");
        }
    }
}

void optismart::on_bactualiser_o_clicked()
{
    actualiserAffichageOrdonnance();
    QMessageBox::information(this, "Actualisation", "Liste des ordonnances actualisée!");
}

void optismart::on_tableWidget_o_clicked(const QModelIndex &index)
{
    int row = index.row();

    // Remplir les champs avec les données sélectionnées
    ui->linecin_o->setText(ui->tableWidget_o->item(row, 0)->text());
    ui->linenom_o->setText(ui->tableWidget_o->item(row, 1)->text());
    ui->lineprenom_o->setText(ui->tableWidget_o->item(row, 2)->text());
    ui->linemedecin_o->setText(ui->tableWidget_o->item(row, 3)->text());

    // Convertir et afficher la date
    QString dateStr = ui->tableWidget_o->item(row, 4)->text();
    QDate date = QDate::fromString(dateStr, "dd-MM-yy");
    ui->linedate_o->setDate(date);

    // Stocker le CIN sélectionné
    cinSelectionne = ui->tableWidget_o->item(row, 0)->text();
}


