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
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QMap>
#include <QFrame>
#include <QVariant>
#include <QPair>
#include <QDebug>
#include <QStatusBar>
#include <QRegularExpression>
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
    labelResultatRecherche(nullptr),
    timerArduino(nullptr),
    timeoutBuffer(nullptr),
    bufferArduino(""),
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
    QString styleLineEdit = "QLineEdit { color: rgb(44, 95, 45); }";
    ui->lineEditCIN->setStyleSheet(styleLineEdit);
    ui->lineEditCIN_2->setStyleSheet(styleLineEdit);
    ui->lineEditNom->setStyleSheet(styleLineEdit);
    ui->lineEditPrenom->setStyleSheet(styleLineEdit);
    ui->lineEditMedecin->setStyleSheet(styleLineEdit);

    // Configurer le style du tableau
    ui->tableWidget->setStyleSheet("QTableView { selection-background-color: #87CEEB; selection-color: black; }");

    // Afficher les données au lancement
    actualiserAffichage();

    // Initialiser le chatbot dans son onglet
    initialiserChatbot(tabChatbot);

    // Initialiser l'onglet de prévisions
    initialiserPrevisions(tabPrevision);

    // Initialiser Arduino
    initialiserArduino();

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
    timerAlertes->start(30000);
}

Gordonnance::~Gordonnance()
{
    if (timerArduino) {
        timerArduino->stop();
        delete timerArduino;
    }
    if (timeoutBuffer) {
        timeoutBuffer->stop();
        delete timeoutBuffer;
    }
    delete ui;
}

// ==================== METHODES ARDUINO ====================

void Gordonnance::initialiserArduino()
{
    // Connexion Arduino
    int ret = arduino_o.connect_arduino();
    switch(ret) {
    case 0:
        qDebug() << "Arduino connecté sur" << arduino_o.getarduino_port_name();
        // Connecter le signal readyRead pour lire les données
        connect(arduino_o.getserial(), &QSerialPort::readyRead, this, &Gordonnance::lireDonneesArduino);

        // Timer pour vérifier périodiquement
        timerArduino = new QTimer(this);
        connect(timerArduino, &QTimer::timeout, this, [this]() {
            if (arduino_o.getserial()->isReadable()) {
                lireDonneesArduino();
            }
        });
        timerArduino->start(100); // Vérifier toutes les 100ms

        // Timer pour le buffer (attente de saisie complète)
        timeoutBuffer = new QTimer(this);
        timeoutBuffer->setSingleShot(true);
        connect(timeoutBuffer, &QTimer::timeout, this, &Gordonnance::traiterBufferArduino);
        break;
    case 1:
        qDebug() << "Arduino disponible mais non connecté";
        break;
    case -1:
        qDebug() << "Arduino non disponible";
        break;
    }

    // Créer un label pour afficher le résultat dans la barre d'état
    labelResultatRecherche = new QLabel("🔍 Attente de saisie d'ID employé...", this);
    labelResultatRecherche->setStyleSheet("font: bold 10pt 'Segoe UI'; padding: 5px; border: 1px solid #2c5f2d; border-radius: 3px;");
    ui->statusbar->addPermanentWidget(labelResultatRecherche);
}

void Gordonnance::lireDonneesArduino()
{
    QByteArray data = arduino_o.read_from_arduino();
    if (data.isEmpty()) return;

    // Ajouter au buffer
    bufferArduino += QString::fromUtf8(data);
    qDebug() << "Données reçues:" << QString::fromUtf8(data).toUtf8().toHex()
             << "Texte:" << QString::fromUtf8(data)
             << "Buffer total:" << bufferArduino;

    // Vérifier si on a un délimiteur de fin (# ou \n)
    if (bufferArduino.contains('#') || bufferArduino.contains('\n')) {
        traiterBufferArduino();
    } else {
        // Redémarrer le timeout (attendre 300ms pour un ID complet)
        timeoutBuffer->start(300);
    }
}

void Gordonnance::traiterBufferArduino()
{
    if (bufferArduino.isEmpty()) {
        return;
    }

    qDebug() << "=== TRAITEMENT DU BUFFER ===";
    qDebug() << "Buffer complet:" << bufferArduino;

    // Extraire et traiter tous les IDs
    extraireEtTraiterIDs(bufferArduino);

    // Vider le buffer après traitement
    bufferArduino.clear();
}

void Gordonnance::extraireEtTraiterIDs(const QString &buffer)
{
    // Méthode 1: Recherche avec expression régulière
    QRegularExpression regex("ID_(\\d+)[#\\n\\r]");
    QRegularExpressionMatchIterator i = regex.globalMatch(buffer);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString id = match.captured(1);
        qDebug() << "ID trouvé via regex:" << id;
        rechercherEmployeParID(id);
    }

    // Méthode 2: Recherche manuelle (fallback)
    if (!i.hasNext()) {
        int startPos = 0;
        while ((startPos = buffer.indexOf("ID_", startPos)) != -1) {
            startPos += 3; // Passer "ID_"

            // Extraire tous les chiffres qui suivent
            QString id;
            for (int i = startPos; i < buffer.length(); i++) {
                if (buffer[i].isDigit()) {
                    id += buffer[i];
                } else {
                    break; // Arrêter au premier caractère non numérique
                }
            }

            if (!id.isEmpty()) {
                qDebug() << "ID trouvé manuellement:" << id;
                rechercherEmployeParID(id);
            }

            startPos += id.length();
        }
    }
}

void Gordonnance::rechercherEmployeParID(const QString &id)
{
    if (id.isEmpty()) {
        qDebug() << "ID vide, recherche ignorée";
        return;
    }

    qDebug() << "Recherche de l'employé ID:" << id;

    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, POSTE FROM EMPLOYE WHERE ID_EMPLOYE = ?");
    query.bindValue(0, id.toInt());

    if (query.exec() && query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString poste = query.value(2).toString();

        QString resultat = QString("✅ Employé trouvé: %1 %2 (%3) - ID: %4")
                               .arg(prenom, nom, poste, id);
        afficherResultatRecherche(resultat, true);

        // Envoyer une confirmation à Arduino (optionnel)
        arduino_o.write_to_arduino("1"); // 1 = trouvé
    } else {
        QString resultat = QString("❌ ID %1 non trouvé dans la base de données").arg(id);
        afficherResultatRecherche(resultat, false);

        // Envoyer un signal à Arduino (optionnel)
        arduino_o.write_to_arduino("0"); // 0 = non trouvé
    }
}

void Gordonnance::afficherResultatRecherche(const QString &message, bool trouve)
{
    if (!labelResultatRecherche) return;

    labelResultatRecherche->setText(message);

    if (trouve) {
        labelResultatRecherche->setStyleSheet(
            "font: bold 10pt 'Segoe UI'; padding: 5px; "
            "border: 2px solid #4CAF50; border-radius: 3px; "
            "background-color: #E8F5E9; color: #2E7D32;"
            );
    } else {
        labelResultatRecherche->setStyleSheet(
            "font: bold 10pt 'Segoe UI'; padding: 5px; "
            "border: 2px solid #F44336; border-radius: 3px; "
            "background-color: #FFEBEE; color: #C62828;"
            );
    }

    // Effacer le message après 5 secondes
    QTimer::singleShot(5000, this, [this]() {
        if (labelResultatRecherche) {
            labelResultatRecherche->setText("🔍 Attente de saisie d'ID employé...");
            labelResultatRecherche->setStyleSheet(
                "font: bold 10pt 'Segoe UI'; padding: 5px; "
                "border: 1px solid #2c5f2d; border-radius: 3px;"
                );
        }
    });
}

// ==================== METHODES EXISTANTES ====================

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
    QString cin = ui->lineEditCIN->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString medecin = ui->lineEditMedecin->text();
    QDate date = ui->dateEdit->date();

    if (cin.isEmpty() || nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    Ordonnance nouvelleOrdonnance(cin, nom, prenom, medecin, date);
    bool test = nouvelleOrdonnance.ajouter();

    if (test) {
        actualiserAffichage();
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        QMessageBox::information(this, "Succès", "Ordonnance ajoutée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de l'ordonnance!");
    }
}

void Gordonnance::on_btnSupprimer_clicked()
{
    QString cin = ui->lineEditCIN->text();

    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant",
                             "Veuillez saisir le CIN de l'ordonnance à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de suppression",
                                  "Êtes-vous sûr de vouloir supprimer l'ordonnance avec CIN: " + cin + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    bool test = ord.supprimer(cin);

    if (test) {
        actualiserAffichage();
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        QMessageBox::information(this, "Succès", "Ordonnance supprimée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la suppression de l'ordonnance!\n"
                              "Vérifiez que le CIN existe dans la base de données.");
    }
}

void Gordonnance::on_tableWidget_clicked(const QModelIndex &index)
{
    int row = index.row();
    ui->lineEditCIN->setText(ui->tableWidget->item(row, 0)->text());
    ui->lineEditNom->setText(ui->tableWidget->item(row, 1)->text());
    ui->lineEditPrenom->setText(ui->tableWidget->item(row, 2)->text());
    ui->lineEditMedecin->setText(ui->tableWidget->item(row, 3)->text());

    QString dateStr = ui->tableWidget->item(row, 4)->text();
    QDate date = QDate::fromString(dateStr, "dd-MM-yy");
    ui->dateEdit->setDate(date);

    cinSelectionne = ui->tableWidget->item(row, 0)->text();
}

void Gordonnance::on_btnModifier_clicked()
{
    if (cinSelectionne.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une ordonnance dans le tableau!");
        return;
    }

    QString nouveauCIN = ui->lineEditCIN->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString medecin = ui->lineEditMedecin->text();
    QDate date = ui->dateEdit->date();

    if (nouveauCIN.isEmpty() || nom.isEmpty() || prenom.isEmpty() || medecin.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir tous les champs obligatoires!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de modification",
                                  "Êtes-vous sûr de vouloir modifier l'ordonnance avec CIN: " + cinSelectionne + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    Ordonnance ordonnanceModifiee(nouveauCIN, nom, prenom, medecin, date);
    bool test = ordonnanceModifiee.modifier(cinSelectionne);

    if (test) {
        actualiserAffichage();
        ui->lineEditCIN->clear();
        ui->lineEditNom->clear();
        ui->lineEditPrenom->clear();
        ui->lineEditMedecin->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        cinSelectionne = "";
        QMessageBox::information(this, "Succès", "Ordonnance modifiée avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de l'ordonnance!");
    }
}

void Gordonnance::on_pushButton_2_clicked()
{
    QString cinRecherche = ui->lineEditCIN_2->text().trimmed();

    if (cinRecherche.isEmpty()) {
        actualiserAffichage();
        QMessageBox::information(this, "Recherche",
                                 "Champ de recherche vide. Affichage de toutes les ordonnances.");
        return;
    }

    ord.rechercherParCIN(cinRecherche, ui->tableWidget);

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
    ord.exporterEnPDF(ui->tableWidget);
}

void Gordonnance::on_pushButton_3_clicked()
{
    ord.trierParNom(ui->tableWidget);
}

void Gordonnance::on_pushButton_10_clicked()
{
    ord.afficherStatistiques(this);
}

void Gordonnance::initialiserChatbot(QWidget *parentWidget)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parentWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10);

    QLabel *labelTitre = new QLabel("🤖 Assistant Chatbot", parentWidget);
    labelTitre->setStyleSheet("font: bold 16pt 'Segoe UI'; color: #2c5f2d; margin-bottom: 10px;");
    labelTitre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelTitre);

    textEditChat = new QTextEdit(parentWidget);
    textEditChat->setReadOnly(true);
    textEditChat->setStyleSheet("QTextEdit { background-color: white; border: 2px solid #2c5f2d; border-radius: 10px; padding: 10px; font: 11pt 'Segoe UI'; }");
    textEditChat->setObjectName("textEditChat");
    mainLayout->addWidget(textEditChat);

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

    connect(btnEnvoyer, &QPushButton::clicked, this, &Gordonnance::on_btnChatbotEnvoyer_clicked);
    connect(lineEditChatbot, &QLineEdit::returnPressed, this, &Gordonnance::on_lineEditChatbot_returnPressed);

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
        const QDate debutFenetre = reference.addDays(-6);

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
                const double poids = 1.0 + (6 - joursEcoules) * 0.15;
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
    QString couleurFond = estUtilisateur ? "#a8d9d0" : "#d3e9d4";
    QString couleurTexte = estUtilisateur ? "#2c5f2d" : "#1a5a1a";
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm");

    textEditChat->append(QString("<div style='margin: 5px 0; padding: 8px; border-radius: 5px; background-color: %1; color: %2;'>"
                                 "<b>%3</b> <span style='font-size: 9pt; opacity: 0.8;'>(%4)</span><br>%5</div>")
                             .arg(couleurFond)
                             .arg(couleurTexte)
                             .arg(prefixe)
                             .arg(timestamp)
                             .arg(message));

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
    QStringList anomalies = chatbot.detecterAnomalies();

    if (!anomalies.isEmpty() && anomalies.size() <= 3) {
        QString messageAlerte = "⚠️ **Alertes détectées:**\n";
        for (int i = 0; i < qMin(3, anomalies.size()); ++i) {
            messageAlerte += anomalies[i] + "\n";
        }

        ajouterMessageChat(messageAlerte, false);
    }
}
