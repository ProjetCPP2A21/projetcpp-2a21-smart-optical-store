#include "gordonnance.h"
#include "ui_gordonnance.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QDate>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QScrollBar>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QMap>
#include <QFrame>
#include <QVariant>
#include <QPair>
#include <QDebug>
#include <cmath>
#include <algorithm>

namespace {

QDate normaliserDateDepuisVariant(const QVariant &value)
{
    if (!value.isValid()) {
        return QDate();
    }

    if (value.canConvert<QDate>()) {
        QDate date = value.toDate();
        if (date.isValid()) {
            return date;
        }
    }

    const QString dateStr = value.toString();
    if (dateStr.isEmpty()) {
        return QDate();
    }

    QDate date = QDate::fromString(dateStr.left(10), Qt::ISODate);
    if (date.isValid()) {
        return date;
    }

    date = QDate::fromString(dateStr, "dd/MM/yyyy");
    if (date.isValid()) {
        return date;
    }

    date = QDate::fromString(dateStr, "yyyy-MM-dd");
    if (date.isValid()) {
        return date;
    }

    return QDate();
}

QString nomJourFrancais(int dayOfWeek)
{
    switch (dayOfWeek) {
    case 1: return "lundi";
    case 2: return "mardi";
    case 3: return "mercredi";
    case 4: return "jeudi";
    case 5: return "vendredi";
    case 6: return "samedi";
    case 7: return "dimanche";
    default: return "jour";
    }
}

QFrame *creerCartePrevision(const QString &titre,
                            QLabel *&labelValeur,
                            QLabel *&labelDetail,
                            QWidget *parent)
{
    QFrame *carte = new QFrame(parent);
    carte->setFrameShape(QFrame::StyledPanel);
    carte->setStyleSheet("QFrame { background-color: white; border: 2px solid #a8d9d0; border-radius: 12px; }");

    QVBoxLayout *layout = new QVBoxLayout(carte);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);

    QLabel *labelTitre = new QLabel(titre, carte);
    labelTitre->setStyleSheet("font: bold 14pt 'Segoe UI'; color: #2c5f2d;");
    layout->addWidget(labelTitre);

    labelValeur = new QLabel("—", carte);
    labelValeur->setStyleSheet("font: 24pt 'Segoe UI'; color: #1a5a1a;");
    layout->addWidget(labelValeur);

    labelDetail = new QLabel("En attente de données...", carte);
    labelDetail->setWordWrap(true);
    labelDetail->setStyleSheet("font: 10pt 'Segoe UI'; color: #2c5f2d;");
    layout->addWidget(labelDetail);

    layout->addStretch();
    return carte;
}

}

Gordonnance::Gordonnance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gordonnance),
    tabWidgetPrincipal(nullptr),
    cinSelectionne(""),
    textEditChat(nullptr),
    lineEditChatbot(nullptr),
    labelVolumeValeur(nullptr),
    labelVolumeDetail(nullptr),
    labelMedecinValeur(nullptr),
    labelMedecinDetail(nullptr),
    labelJourValeur(nullptr),
    labelJourDetail(nullptr),
    indexTabPrevision(-1)
{
    ui->setupUi(this);

    // Création du QTabWidget principal
    tabWidgetPrincipal = new QTabWidget(this);
    tabWidgetPrincipal->setStyleSheet("QTabWidget::pane { border: 1px solid #2c5f2d; } "
                                      "QTabBar::tab { background: #a8d9d0; color: #2c5f2d; padding: 10px; border-top-left-radius: 4px; border-top-right-radius: 4px; } "
                                      "QTabBar::tab:selected { background: #d3e9d4; font-weight: bold; }");

    // Onglet 1: Gestion Ordonnance (Interface existante)
    QWidget *tabOrdonnance = new QWidget();
    
    // Reparenter les widgets existants vers tabOrdonnance
    ui->groupBox->setParent(tabOrdonnance);
    ui->tableWidget->setParent(tabOrdonnance);
    ui->label->setParent(tabOrdonnance);
    ui->label_9->setParent(tabOrdonnance);
    ui->lineEditCIN_2->setParent(tabOrdonnance);
    ui->pushButton_2->setParent(tabOrdonnance);
    ui->pushButton_3->setParent(tabOrdonnance);
    ui->pushButton_5->setParent(tabOrdonnance);
    ui->pushButton_10->setParent(tabOrdonnance);
    ui->btnModifier->setParent(tabOrdonnance);
    ui->btnAjouter->setParent(tabOrdonnance);
    ui->btnSupprimer->setParent(tabOrdonnance);
    ui->label_2->setParent(tabOrdonnance);
    ui->label_3->setParent(tabOrdonnance);
    ui->label_4->setParent(tabOrdonnance);
    ui->label_5->setParent(tabOrdonnance);
    ui->label_6->setParent(tabOrdonnance);
    ui->label_7->setParent(tabOrdonnance);
    ui->lineEditCIN->setParent(tabOrdonnance);
    ui->lineEditNom->setParent(tabOrdonnance);
    ui->lineEditPrenom->setParent(tabOrdonnance);
    ui->lineEditMedecin->setParent(tabOrdonnance);
    ui->dateEdit->setParent(tabOrdonnance);

    // Onglet 2: Chatbot
    QWidget *tabChatbot = new QWidget();

    // Onglet 3: Prévision du futur
    QWidget *tabPrevision = new QWidget();
    
    // Ajouter les onglets
    tabWidgetPrincipal->addTab(tabOrdonnance, "Gestion Ordonnance");
    tabWidgetPrincipal->addTab(tabChatbot, "Assistant Chatbot");
    indexTabPrevision = tabWidgetPrincipal->addTab(tabPrevision, "Prévision du futur");
    
    // Mettre le TabWidget dans le centralWidget
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(tabWidgetPrincipal);
    ui->centralwidget->setLayout(layout);

    // Configurer le dateEdit avec la date actuelle
    ui->dateEdit->setDate(QDate::currentDate());
    
    // Configurer la couleur du texte pour tous les QLineEdit
    QString styleLineEdit = "QLineEdit { color: rgb(44, 95, 45); }"; // Vert foncé
    ui->lineEditCIN->setStyleSheet(styleLineEdit);
    ui->lineEditCIN_2->setStyleSheet(styleLineEdit);
    ui->lineEditNom->setStyleSheet(styleLineEdit);
    ui->lineEditPrenom->setStyleSheet(styleLineEdit);
    ui->lineEditMedecin->setStyleSheet(styleLineEdit);

    // Configurer le style du tableau pour une sélection plus claire
    ui->tableWidget->setStyleSheet("QTableView { selection-background-color: #87CEEB; selection-color: black; }"); // Bleu ciel clair

    // Afficher les données au lancement
    actualiserAffichage();
    
    // Initialiser le chatbot dans son onglet
    initialiserChatbot(tabChatbot);

    // Initialiser l'onglet de prévisions
    initialiserPrevisions(tabPrevision);

    // Mettre à jour les prévisions dès que l'onglet est ouvert
    connect(tabWidgetPrincipal, &QTabWidget::currentChanged, this, [this](int index) {
        if (index == indexTabPrevision) {
            mettreAJourPrevisions();
        }
    });
    mettreAJourPrevisions();
    
    // Vérifier les alertes toutes les 30 secondes
    QTimer *timerAlertes = new QTimer(this);
    connect(timerAlertes, &QTimer::timeout, this, &Gordonnance::verifierAlertes);
    timerAlertes->start(30000); // 30 secondes
}

Gordonnance::~Gordonnance()
{
    delete ui;
}

void Gordonnance::actualiserAffichage()
{
    ord.afficher(ui->tableWidget);
    if (labelVolumeValeur) {
        mettreAJourPrevisions();
    }
}

void Gordonnance::on_btnActualiser_clicked()
{
    actualiserAffichage();
    QMessageBox::information(this, "Actualisation", "Liste des ordonnances actualisée!");
}

void Gordonnance::on_btnAjouter_clicked()
{
    // Récupération des informations saisies dans les champs
    QString cin = ui->lineEditCIN->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString medecin = ui->lineEditMedecin->text();
    QDate date = ui->dateEdit->date();

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
        actualiserAffichage();

        // Vider les champs de saisie
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());

        QMessageBox::information(this, "Succès",
                                 "Ordonnance ajoutée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout de l'ordonnance!");
    }
}

void Gordonnance::on_btnSupprimer_clicked()
{
    // Récupération du CIN depuis le MÊME CHAMP
    QString cin = ui->lineEditCIN->text();

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
        actualiserAffichage();

        // Vider tous les champs après suppression
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());

        QMessageBox::information(this, "Succès",
                                 "Ordonnance supprimée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la suppression de l'ordonnance!\n"
                              "Vérifiez que le CIN existe dans la base de données.");
    }
}

void Gordonnance::on_tableWidget_clicked(const QModelIndex &index)
{
    // Récupérer la ligne sélectionnée
    int row = index.row();

    // Remplir les champs avec les données de la ligne sélectionnée
    ui->lineEditCIN->setText(ui->tableWidget->item(row, 0)->text());
    ui->lineEditNom->setText(ui->tableWidget->item(row, 1)->text());
    ui->lineEditPrenom->setText(ui->tableWidget->item(row, 2)->text());
    ui->lineEditMedecin->setText(ui->tableWidget->item(row, 3)->text());

    // Convertir la date du tableau vers QDate
    QString dateStr = ui->tableWidget->item(row, 4)->text();
    QDate date = QDate::fromString(dateStr, "dd-MM-yy");
    ui->dateEdit->setDate(date);

    // Stocker le CIN sélectionné pour la modification
    cinSelectionne = ui->tableWidget->item(row, 0)->text();
}

void Gordonnance::on_btnModifier_clicked()
{
    // Vérifier qu'une ordonnance est sélectionnée
    if (cinSelectionne.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une ordonnance dans le tableau!");
        return;
    }

    // Récupération des nouvelles informations saisies
    QString nouveauCIN = ui->lineEditCIN->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString medecin = ui->lineEditMedecin->text();
    QDate date = ui->dateEdit->date();

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
        actualiserAffichage();

        // Vider les champs et réinitialiser la sélection
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        cinSelectionne = "";

        QMessageBox::information(this, "Succès",
                                 "Ordonnance modifiée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la modification de l'ordonnance!");
    }
}

void Gordonnance::on_pushButton_2_clicked()
{
    // Récupération du CIN saisi dans le champ de recherche
    QString cinRecherche = ui->lineEditCIN_2->text().trimmed();

    // Si le champ est vide, afficher toutes les ordonnances
    if (cinRecherche.isEmpty()) {
        actualiserAffichage();
        QMessageBox::information(this, "Recherche",
                                 "Champ de recherche vide. Affichage de toutes les ordonnances.");
        return;
    }

    // Effectuer la recherche par CIN
    ord.rechercherParCIN(cinRecherche, ui->tableWidget);

    // Vérifier si des résultats ont été trouvés
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "Recherche",
                                 "Aucune ordonnance trouvée pour le CIN: " + cinRecherche);
    } else {
        QMessageBox::information(this, "Recherche",
                                QString::number(ui->tableWidget->rowCount()) +
                                " ordonnance(s) trouvée(s) pour le CIN: " + cinRecherche);
    }
}

void Gordonnance::on_pushButton_5_clicked()
{
    // Exporter le contenu du tableau en PDF
    ord.exporterEnPDF(ui->tableWidget);
}

void Gordonnance::on_pushButton_3_clicked()
{
    // Trier le tableau selon la première lettre du nom
    ord.trierParNom(ui->tableWidget);
}

void Gordonnance::on_pushButton_10_clicked()
{
    // Afficher les statistiques des ordonnances
    ord.afficherStatistiques(this);
}

void Gordonnance::initialiserChatbot(QWidget *parentWidget)
{
    // Utiliser le widget parent (l'onglet) pour le layout
    QVBoxLayout *mainLayout = new QVBoxLayout(parentWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10);
    
    // En-tête avec titre
    QLabel *labelTitre = new QLabel("🤖 Assistant Chatbot", parentWidget);
    labelTitre->setStyleSheet("font: bold 16pt 'Segoe UI'; color: #2c5f2d; margin-bottom: 10px;");
    labelTitre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelTitre);
    
    // Zone d'affichage des messages (Grande zone maintenant)
    textEditChat = new QTextEdit(parentWidget);
    textEditChat->setReadOnly(true);
    textEditChat->setStyleSheet("QTextEdit { background-color: white; border: 2px solid #2c5f2d; border-radius: 10px; padding: 10px; font: 11pt 'Segoe UI'; }");
    textEditChat->setObjectName("textEditChat");
    mainLayout->addWidget(textEditChat);
    
    // Zone de saisie
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->setSpacing(10);
    
    lineEditChatbot = new QLineEdit(parentWidget);
    lineEditChatbot->setPlaceholderText("Tapez votre question... (ex: 'Montre-moi les patients du Dr. X')");
    lineEditChatbot->setStyleSheet("QLineEdit { background-color: white; border: 2px solid #2c5f2d; border-radius: 5px; padding: 10px; font: 11pt 'Segoe UI'; color: rgb(44, 95, 45); }");
    lineEditChatbot->setObjectName("lineEditChatbot");
    inputLayout->addWidget(lineEditChatbot, 1);
    
    QPushButton *btnEnvoyer = new QPushButton("Envoyer", parentWidget);
    btnEnvoyer->setStyleSheet("QPushButton { background-color: rgb(168, 213, 186); font: bold 11pt 'Segoe UI'; color: rgb(51, 51, 51); padding: 10px 20px; border-radius: 5px; } "
                              "QPushButton:hover { background-color: rgb(148, 193, 166); }");
    btnEnvoyer->setObjectName("btnChatbotEnvoyer");
    inputLayout->addWidget(btnEnvoyer);
    
    mainLayout->addLayout(inputLayout);
    
    // Connecter les signaux
    connect(btnEnvoyer, &QPushButton::clicked, this, &Gordonnance::on_btnChatbotEnvoyer_clicked);
    connect(lineEditChatbot, &QLineEdit::returnPressed, this, &Gordonnance::on_lineEditChatbot_returnPressed);
    
    // Message de bienvenue
    ajouterMessageChat("🤖 Bonjour! Je suis votre assistant virtuel.\n\n"
                       "Je peux vous aider à :\n"
                       "- Rechercher des ordonnances\n"
                       "- Analyser les données\n"
                       "- Détecter des anomalies\n\n"
                       "Tapez 'aide' pour voir la liste des commandes.", false);
}

void Gordonnance::initialiserPrevisions(QWidget *parentWidget)
{
    if (!parentWidget) {
        return;
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(parentWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    QLabel *titre = new QLabel("🔮 Mode Prévision du futur", parentWidget);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font: bold 18pt 'Segoe UI'; color: #2c5f2d;");
    mainLayout->addWidget(titre);

    QLabel *sousTitre = new QLabel("Projette automatiquement l'activité à partir des données déjà enregistrées (moyenne + tendance).", parentWidget);
    sousTitre->setWordWrap(true);
    sousTitre->setAlignment(Qt::AlignCenter);
    sousTitre->setStyleSheet("font: 11pt 'Segoe UI'; color: #1a5a1a;");
    mainLayout->addWidget(sousTitre);

    QHBoxLayout *cartesLayout = new QHBoxLayout();
    cartesLayout->setSpacing(16);

    cartesLayout->addWidget(creerCartePrevision("📈 Ordonnances attendues", labelVolumeValeur, labelVolumeDetail, parentWidget), 1);
    cartesLayout->addWidget(creerCartePrevision("👨‍⚕️ Médecin pressenti", labelMedecinValeur, labelMedecinDetail, parentWidget), 1);
    cartesLayout->addWidget(creerCartePrevision("📅 Jour le plus chargé", labelJourValeur, labelJourDetail, parentWidget), 1);

    mainLayout->addLayout(cartesLayout);

    QPushButton *btnRafraichir = new QPushButton("Rafraîchir les prévisions", parentWidget);
    btnRafraichir->setStyleSheet("QPushButton { background-color: rgb(168, 213, 186); font: bold 12pt 'Segoe UI'; color: rgb(51, 51, 51); padding: 12px 24px; border-radius: 8px; } "
                                 "QPushButton:hover { background-color: rgb(148, 193, 166); }");
    connect(btnRafraichir, &QPushButton::clicked, this, [this]() {
        mettreAJourPrevisions();
    });

    mainLayout->addWidget(btnRafraichir, 0, Qt::AlignCenter);
    mainLayout->addStretch();
}

void Gordonnance::mettreAJourPrevisions()
{
    if (!labelVolumeValeur || !labelMedecinValeur || !labelJourValeur) {
        return;
    }

    const PrevisionData data = calculerPrevisions();

    if (data.hasVolume) {
        labelVolumeValeur->setText(data.volumeTexte);
        labelVolumeDetail->setText(data.volumeDetail);
    } else {
        labelVolumeValeur->setText("Pas assez de données");
        labelVolumeDetail->setText("Ajoutez quelques ordonnances pour générer une tendance hebdomadaire.");
    }

    if (data.hasMedecin) {
        labelMedecinValeur->setText(data.medecinTexte);
        labelMedecinDetail->setText(data.medecinDetail);
    } else {
        labelMedecinValeur->setText("En attente de données");
        labelMedecinDetail->setText("Les médecins les plus actifs apparaîtront dès qu'un historique de 2 jours sera disponible.");
    }

    if (data.hasJour) {
        labelJourValeur->setText(data.jourTexte);
        labelJourDetail->setText(data.jourDetail);
    } else {
        labelJourValeur->setText("En attente");
        labelJourDetail->setText("Enregistrez plusieurs jours d'activité pour détecter les périodes chargées.");
    }
}

Gordonnance::PrevisionData Gordonnance::calculerPrevisions() const
{
    PrevisionData resultat;
    QSqlQuery query;

    if (!query.exec("SELECT MEDECIN, DATE_ORD FROM ordonnance ORDER BY DATE_ORD ASC")) {
        qWarning() << "Erreur lors du calcul des prévisions:" << query.lastError();
        return resultat;
    }

    QMap<QDate, int> ordonnancesParJour;
    QMap<QString, QMap<QDate, int>> activiteParMedecin;
    QMap<QPair<int, int>, int> ordonnancesParSemaine;

    QDate dateMax;
    bool dateMaxValide = false;

    while (query.next()) {
        const QString medecin = query.value("MEDECIN").toString();
        const QDate date = normaliserDateDepuisVariant(query.value("DATE_ORD"));
        if (!date.isValid()) {
            continue;
        }

        ordonnancesParJour[date]++;
        activiteParMedecin[medecin][date]++;

        int isoYear = 0;
        const int isoWeek = date.weekNumber(&isoYear);
        ordonnancesParSemaine[qMakePair(isoYear, isoWeek)]++;

        if (!dateMaxValide || date > dateMax) {
            dateMax = date;
            dateMaxValide = true;
        }
    }

    // Prévision du volume hebdomadaire
    if (!ordonnancesParSemaine.isEmpty()) {
        QVector<int> volumes;
        volumes.reserve(ordonnancesParSemaine.size());
        for (auto it = ordonnancesParSemaine.constBegin(); it != ordonnancesParSemaine.constEnd(); ++it) {
            volumes.append(it.value());
        }

        double total = 0.0;
        for (int valeur : volumes) {
            total += valeur;
        }

        const double moyenne = total / volumes.size();
        double tendance = 0.0;
        if (volumes.size() >= 2) {
            tendance = static_cast<double>(volumes.last() - volumes[volumes.size() - 2]);
        }

        const int prevision = std::max(0, static_cast<int>(std::round(moyenne + tendance)));
        resultat.hasVolume = true;
        resultat.volumeTexte = QString("≈ %1 ordonnances").arg(prevision);
        resultat.volumeDetail = QString("Moyenne %.1f/sem, tendance %+0.1f sur les deux dernières semaines.")
                                    .arg(moyenne, 0, 'f', 1)
                                    .arg(tendance, 0, 'f', 1);
    }

    // Médecin le plus actif prédit
    if (!activiteParMedecin.isEmpty()) {
        const QDate reference = dateMaxValide ? dateMax : QDate::currentDate();
        const QDate debutFenetre = reference.addDays(-6); // 7 jours glissants

        double meilleurScore = -1.0;
        QString medecinTop;
        int totalRecentTop = 0;

        for (auto itMed = activiteParMedecin.constBegin(); itMed != activiteParMedecin.constEnd(); ++itMed) {
            double score = 0.0;
            int totalRecent = 0;

            for (auto itJour = itMed.value().constBegin(); itJour != itMed.value().constEnd(); ++itJour) {
                if (itJour.key() < debutFenetre) {
                    continue;
                }
                int joursEcoules = itJour.key().daysTo(reference);
                if (joursEcoules < 0) {
                    joursEcoules = 0;
                } else if (joursEcoules > 6) {
                    joursEcoules = 6;
                }
                const double poids = 1.0 + (6 - joursEcoules) * 0.15; // Accent sur les jours récents
                score += itJour.value() * poids;
                totalRecent += itJour.value();
            }

            if (totalRecent > 0 && score > meilleurScore) {
                meilleurScore = score;
                medecinTop = itMed.key();
                totalRecentTop = totalRecent;
            }
        }

        if (meilleurScore > 0) {
            resultat.hasMedecin = true;
            resultat.medecinTexte = medecinTop;
            resultat.medecinDetail = QString("Basé sur %1 ordonnance(s) sur les 7 derniers jours, pondérées par la fraîcheur.")
                                         .arg(totalRecentTop);
        }
    }

    // Jour de la semaine le plus chargé
    if (!ordonnancesParJour.isEmpty()) {
        struct JourStats {
            int total = 0;
            int nbJours = 0;
        };

        QMap<int, JourStats> statsParJour;
        for (auto it = ordonnancesParJour.constBegin(); it != ordonnancesParJour.constEnd(); ++it) {
            JourStats &stats = statsParJour[it.key().dayOfWeek()];
            stats.total += it.value();
            stats.nbJours += 1;
        }

        int meilleurJour = -1;
        double meilleureMoyenne = -1.0;
        JourStats statsRetenus;

        for (auto it = statsParJour.constBegin(); it != statsParJour.constEnd(); ++it) {
            const JourStats stats = it.value();
            if (stats.nbJours == 0) {
                continue;
            }
            const double moyenneJour = static_cast<double>(stats.total) / stats.nbJours;
            if (moyenneJour > meilleureMoyenne) {
                meilleureMoyenne = moyenneJour;
                meilleurJour = it.key();
                statsRetenus = stats;
            }
        }

        if (meilleurJour != -1) {
            resultat.hasJour = true;
            resultat.jourTexte = QString("≈ %1").arg(nomJourFrancais(meilleurJour));
            resultat.jourDetail = QString("En moyenne %.1f ordonnance(s) chaque %2 (basé sur %3 occurrences).")
                                      .arg(meilleureMoyenne, 0, 'f', 1)
                                      .arg(nomJourFrancais(meilleurJour))
                                      .arg(statsRetenus.nbJours);
        }
    }

    return resultat;
}

void Gordonnance::ajouterMessageChat(const QString &message, bool estUtilisateur)
{
    if (!textEditChat) return;
    
    QString prefixe = estUtilisateur ? "👤 Vous: " : "🤖 Assistant: ";
    QString couleurFond = estUtilisateur ? "#a8d9d0" : "#d3e9d4"; // Fond vert clair
    QString couleurTexte = estUtilisateur ? "#2c5f2d" : "#1a5a1a"; // Texte vert foncé/noir
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm");
    
    textEditChat->append(QString("<div style='margin: 5px 0; padding: 8px; border-radius: 5px; background-color: %1; color: %2;'>"
                                "<b>%3</b> <span style='font-size: 9pt; opacity: 0.8;'>(%4)</span><br>%5</div>")
                         .arg(couleurFond)
                         .arg(couleurTexte)
                         .arg(prefixe)
                         .arg(timestamp)
                         .arg(message));
    
    // Défilement automatique vers le bas
    QScrollBar *scrollBar = textEditChat->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void Gordonnance::on_btnChatbotEnvoyer_clicked()
{
    if (!lineEditChatbot) return;
    
    QString message = lineEditChatbot->text().trimmed();
    if (!message.isEmpty()) {
        ajouterMessageChat(message, true);
        QString reponse = chatbot.traiterMessage(message, ui->tableWidget);
        ajouterMessageChat(reponse, false);
        lineEditChatbot->clear();
        actualiserAffichage();
    }
}

void Gordonnance::on_lineEditChatbot_returnPressed()
{
    on_btnChatbotEnvoyer_clicked();
}

void Gordonnance::verifierAlertes()
{
    // Vérifier les anomalies toutes les 30 secondes
    QStringList anomalies = chatbot.detecterAnomalies();
    
    if (!anomalies.isEmpty() && anomalies.size() <= 3) {
        // Afficher seulement les 3 premières anomalies pour ne pas surcharger
        QString messageAlerte = "⚠️ **Alertes détectées:**\n";
        for (int i = 0; i < qMin(3, anomalies.size()); ++i) {
            messageAlerte += anomalies[i] + "\n";
        }
        
        // Ajouter au chat
        ajouterMessageChat(messageAlerte, false);
    }
}