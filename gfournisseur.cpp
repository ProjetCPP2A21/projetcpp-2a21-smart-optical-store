#include "gfournisseur.h"
#include "ui_gfournisseur.h"
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlQuery>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTextCharFormat>
#include <QDateTime>
#include <QPrinter>
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QGraphicsScene>
#include <QPainter>
#include <QPieSlice>
#include <QDir>
#include <QCompleter>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>

gfournisseur::gfournisseur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gfournisseur)
    , m_mapWidget(nullptr)
    , m_mapDialog(nullptr)
{
    ui->setupUi(this);

    // Validateur pour NUMERO_TELEPHONE (8 chiffres exactement)
    ui->telephone_le->setValidator(new QIntValidator(0, 99999999, this));

    // Configuration de la condition de paiement
    setupConditionPaiement();

    // Connexions pour la validation en temps réel
    connect(ui->nom_le, &QLineEdit::textChanged, this, &gfournisseur::on_nom_le_textChanged);
    connect(ui->email_le, &QLineEdit::textChanged, this, &gfournisseur::on_email_le_textChanged);
    connect(ui->telephone_le, &QLineEdit::textChanged, this, &gfournisseur::on_telephone_le_textChanged);
    connect(ui->cp_le, &QLineEdit::textChanged, this, &gfournisseur::on_cp_le_textChanged);

    // Connexion pour la sélection dans le tableau
    connect(ui->tableWidget_4, &QTableWidget::itemClicked, this, &gfournisseur::on_tableWidget_4_itemClicked);

    // Setup de la carte
    setupCarte();

    // Afficher les données au démarrage
    actualiserAffichage();
}

gfournisseur::~gfournisseur()
{
    delete ui;
}

// ==================== CONFIGURATION CONDITION PAIEMENT ====================

void gfournisseur::setupConditionPaiement()
{
    QCompleter *completer = new QCompleter(this);
    QStringList conditions;
    conditions << "payé" << "30 jours" << "60 jours" << "comptant" << "avance" << "autre";

    completer->setModel(new QStringListModel(conditions, this));
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    ui->cp_le->setCompleter(completer);
    ui->cp_le->setPlaceholderText("payé, 30 jours, 60 jours, comptant, avance, autre");
}

// ==================== MÉTHODES DE VALIDATION ====================

bool gfournisseur::validerNom(const QString &nom)
{
    if (nom.isEmpty()) return true;

    QRegularExpression regex("^[a-zA-ZÀ-ÿœŒ\\s\\-\\&]{2,50}$");
    return regex.match(nom).hasMatch();
}

bool gfournisseur::validerEmail(const QString &email)
{
    if (email.isEmpty()) return true;

    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool gfournisseur::validerTelephone(const QString &telephone)
{
    if (telephone.isEmpty()) return true;

    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool gfournisseur::validerAdresse(const QString &adresse)
{
    if (adresse.isEmpty()) return true;

    return adresse.length() >= 5 && adresse.length() <= 100;
}

bool gfournisseur::validerConditionPaiement(const QString &condition)
{
    if (condition.isEmpty()) return true;

    QStringList conditionsValides = {"payé", "30 jours", "60 jours", "comptant", "avance", "autre"};
    return conditionsValides.contains(condition.toLower());
}

void gfournisseur::afficherErreurChamp(QLineEdit *champ, bool estValide, const QString &message)
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

// ==================== SLOTS DE VALIDATION TEMPS RÉEL ====================

void gfournisseur::on_nom_le_textChanged(const QString &text)
{
    bool estValide = validerNom(text);
    afficherErreurChamp(ui->nom_le, estValide,
                        "Le nom ne doit contenir que des lettres et espaces (accents autorisés)");
}

void gfournisseur::on_email_le_textChanged(const QString &text)
{
    bool estValide = validerEmail(text);
    afficherErreurChamp(ui->email_le, estValide,
                        "Format d'email invalide (ex: exemple@domaine.fr)");
}

void gfournisseur::on_telephone_le_textChanged(const QString &text)
{
    bool estValide = validerTelephone(text);
    afficherErreurChamp(ui->telephone_le, estValide,
                        "Le numéro doit être 8 chiffres");
}

void gfournisseur::on_cp_le_textChanged(const QString &text)
{
    bool estValide = validerConditionPaiement(text);
    afficherErreurChamp(ui->cp_le, estValide,
                        "Condition de paiement invalide!\n"
                        "Valeurs acceptées:\n"
                        "• payé\n• 30 jours\n• 60 jours\n• comptant\n• avance\n• autre");
}

// ==================== MÉTHODES PRINCIPALES ====================

void gfournisseur::actualiserAffichage()
{
    if (ui->tableWidget_4) {
        fourn.afficher(ui->tableWidget_4);
    }
}

void gfournisseur::clearFields()
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

// ==================== CARTE DES FOURNISSEURS ====================

void gfournisseur::setupCarte()
{
    m_mapDialog = new QDialog(this);
    m_mapDialog->setWindowTitle("Carte des Fournisseurs - Tunisie");
    m_mapDialog->resize(1000, 700);

    m_mapWidget = new QQuickWidget(m_mapDialog);
    m_mapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    qDebug() << "=== DÉBUT CHARGEMENT CARTE QML ===";

    // Vérifier l'existence des fichiers QML dans les ressources
    QFile qmlFile1(":/CarteFournisseurs.qml");
    QFile qmlFile2(":/FournisseurMarker.qml");

    qDebug() << "CarteFournisseurs.qml existe dans ressources:" << qmlFile1.exists();
    qDebug() << "FournisseurMarker.qml existe dans ressources:" << qmlFile2.exists();

    // Vérifier l'existence des fichiers locaux
    QFile localFile1("CarteFournisseurs.qml");
    QFile localFile2("FournisseurMarker.qml");

    qDebug() << "CarteFournisseurs.qml existe local:" << localFile1.exists();
    qDebug() << "FournisseurMarker.qml existe local:" << localFile2.exists();

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
        QMessageBox::warning(this, "Erreur", "Fichier QML non chargé - Vérifiez maps.qrc");
    }

    QVBoxLayout *layout = new QVBoxLayout(m_mapDialog);
    layout->addWidget(m_mapWidget);
    m_mapDialog->setLayout(layout);

    qDebug() << "=== FIN CHARGEMENT CARTE QML ===";
}

void gfournisseur::on_bcarte_f_clicked()
{
    QList<QVariantMap> fournisseursData;

    QSqlQuery query("SELECT NOM, EMAIL, NUMERO_TELEPHONE, ADRESSE FROM FOURNISSEUR");

    qDebug() << "=== DÉBUT GÉOCODAGE INTELLIGENT FOURNISSEURS ===";

    QMap<QString, QList<QPair<double, double>>> positionsVilles = {
        {"tunis", {{36.8008,10.1800},{36.8380,10.2400},{36.8065,10.1815},{36.7960,10.1760},{36.8500,10.2000},{36.8200,10.1500},{36.7800,10.2200},{36.8300,10.1650},{36.8100,10.0950}}},
        {"sfax",  {{34.7400,10.7600},{34.7500,10.7700},{34.7300,10.7500},{34.7200,10.7800},{34.7350,10.7550}}},
        {"sousse",{{35.8254,10.6360},{35.8300,10.6250},{35.8200,10.6400},{35.8150,10.6300},{35.8270,10.5920}}},
        {"nabeul",{{36.4561,10.7376},{36.4600,10.7300},{36.4500,10.7400},{36.4400,10.7500},{36.4550,10.7250}}},
        {"bizerte",{{37.2747,9.8739},{37.2800,9.8700},{37.2700,9.8800},{37.2650,9.8650}}},
        {"gabès", {{33.8815,10.0982},{33.8900,10.1000},{33.8700,10.1100},{33.8800,10.0850}}},
        {"kairouan",{{35.6781,10.0964},{35.6800,10.0900},{35.6700,10.1050},{35.6750,10.0850}}},
        {"gafsa", {{34.4250,8.7842},{34.4300,8.7800},{34.4200,8.7900},{34.4150,8.7750}}}
    };

    QMap<QString, int> compteurPositions;
    int count = 0;
    int countIgnored = 0;

    // Utility lambda to detect full words
    auto containsWord = [&](const QString &text, const QString &word) {
        QRegularExpression rx("\\b" + QRegularExpression::escape(word) + "\\b",
                              QRegularExpression::CaseInsensitiveOption);
        return text.contains(rx);
    };

    while (query.next()) {
        QVariantMap fournisseur;

        fournisseur["nom"] = query.value("NOM").toString();
        fournisseur["email"] = query.value("EMAIL").toString();
        fournisseur["telephone"] = query.value("NUMERO_TELEPHONE").toString();
        QString adresse = query.value("ADRESSE").toString();
        fournisseur["adresse"] = adresse;

        QString adresseLower = adresse.toLower();
        QString villeDetectee = "";

        // Correct full-word detection
        if (containsWord(adresseLower, "sfax")   || adresseLower.contains("صفاقس"))
            villeDetectee = "sfax";
        else if (containsWord(adresseLower, "sousse") || adresseLower.contains("سوسة"))
            villeDetectee = "sousse";
        else if (containsWord(adresseLower, "nabeul") || adresseLower.contains("نابل"))
            villeDetectee = "nabeul";
        else if (containsWord(adresseLower, "bizerte") || adresseLower.contains("بنزرت"))
            villeDetectee = "bizerte";
        else if (containsWord(adresseLower, "gabes") || containsWord(adresseLower, "gabès") || adresseLower.contains("قابس"))
            villeDetectee = "gabès";
        else if (containsWord(adresseLower, "kairouan") || adresseLower.contains("القيروان"))
            villeDetectee = "kairouan";
        else if (containsWord(adresseLower, "gafsa") || adresseLower.contains("قفصة"))
            villeDetectee = "gafsa";
        else if (containsWord(adresseLower, "tunis") || adresseLower.contains("تونس"))
            villeDetectee = "tunis";

        // ❌ If no valid city → ignore this supplier
        if (villeDetectee.isEmpty() || !positionsVilles.contains(villeDetectee)) {
            qDebug() << "⚠️ Fournisseur ignoré (ville inconnue) :" << fournisseur["nom"].toString()
                << "- Adresse:" << adresse;
            countIgnored++;
            continue;
        }

        count++;

        // Assign coordinates
        QList<QPair<double, double>> positions = positionsVilles[villeDetectee];
        int posIdx = compteurPositions[villeDetectee] % positions.size();

        fournisseur["latitude"] = positions[posIdx].first;
        fournisseur["longitude"] = positions[posIdx].second;
        fournisseur["ville"] = villeDetectee;

        compteurPositions[villeDetectee]++;

        qDebug() << "📍" << fournisseur["nom"].toString()
                 << "→" << villeDetectee << "(" << posIdx << ")";
        fournisseursData.append(fournisseur);
    }

    qDebug() << "=== FIN GÉOCODAGE ===";
    qDebug() << count << "fournisseurs valides";
    qDebug() << countIgnored << "adresses ignorées";

    if (count == 0) return;

    QQuickItem *rootObject = m_mapWidget->rootObject();
    if (rootObject) {
        QMetaObject::invokeMethod(rootObject, "updateFournisseurs",
                                  Q_ARG(QVariant, QVariant::fromValue(fournisseursData)));
        m_mapDialog->show();
        m_mapDialog->raise();
        m_mapDialog->activateWindow();
    }
}

// ==================== CLIC SUR UNE LIGNE DU TABLEAU ====================

void gfournisseur::on_tableWidget_4_itemClicked(QTableWidgetItem *item)
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

// ==================== BOUTON NOUVEAU ====================

void gfournisseur::on_bnouveau_f_clicked()
{
    clearFields();
    ui->tableWidget_4->clearSelection();
    QMessageBox::information(this, "Nouveau", "Formulaire prêt pour un nouveau fournisseur!");
}

// ==================== AJOUTER ====================

void gfournisseur::on_bajouter_f_clicked()
{
    qDebug() << "=== CLICK SUR BAJOUTER_F ===";

    // Récupération des valeurs depuis les line edits
    QString ID_FOURNISSEUR = ui->id_le->text();
    QString NOM = ui->nom_le->text();
    QString ADRESSE = ui->adresse_le->text();
    QString EMAIL = ui->email_le->text();
    QString NUMERO_TELEPHONE = ui->telephone_le->text();
    QString CONDITION_PAIEMENT = ui->cp_le->text();

    // ==================== VALIDATION DES CHAMPS ====================

    // Validation des champs obligatoires
    if (ID_FOURNISSEUR.isEmpty() || NOM.isEmpty() || NUMERO_TELEPHONE.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir les champs ID_FOURNISSEUR, NOM et NUMERO_TELEPHONE!");
        return;
    }

    // Validation NOM
    if (!validerNom(NOM)) {
        QMessageBox::warning(this, "Nom invalide",
                             "Le nom ne doit contenir que des lettres et espaces (accents autorisés)\n"
                             "Longueur: 2 à 50 caractères");
        ui->nom_le->setFocus();
        return;
    }

    // Validation ADRESSE
    if (!ADRESSE.isEmpty() && !validerAdresse(ADRESSE)) {
        QMessageBox::warning(this, "Adresse invalide",
                             "L'adresse doit contenir entre 5 et 100 caractères");
        ui->adresse_le->setFocus();
        return;
    }

    // Validation EMAIL
    if (!EMAIL.isEmpty() && !validerEmail(EMAIL)) {
        QMessageBox::warning(this, "Email invalide",
                             "Format d'email invalide\n"
                             "Exemple: exemple@domaine.fr");
        ui->email_le->setFocus();
        return;
    }

    // Validation NUMERO_TELEPHONE
    if (!validerTelephone(NUMERO_TELEPHONE)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir exactement 8 chiffres");
        ui->telephone_le->setFocus();
        return;
    }

    // Validation CONDITION_PAIEMENT
    if (!CONDITION_PAIEMENT.isEmpty() && !validerConditionPaiement(CONDITION_PAIEMENT)) {
        QMessageBox::warning(this, "Condition de paiement invalide",
                             "Condition de paiement non valide!\n\n"
                             "Valeurs acceptées:\n"
                             "• payé\n• 30 jours\n• 60 jours\n• comptant\n• avance\n• autre");
        ui->cp_le->setFocus();
        return;
    }

    // Validation de la longueur des champs
    if (ID_FOURNISSEUR.length() > 50) {
        QMessageBox::warning(this, "ID_FOURNISSEUR trop long", "L'ID_FOURNISSEUR ne doit pas dépasser 50 caractères!");
        return;
    }

    // Création d'un objet fournisseur
    fournisseur nouveauFournisseur(ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT);

    // Ajout dans la base de données
    if (nouveauFournisseur.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès!");

        // Actualiser l'affichage
        actualiserAffichage();

        // Vider les champs
        clearFields();

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

// ==================== SUPPRIMER ====================

void gfournisseur::on_bsupprimer_f_clicked()
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
        // Supprimer le fournisseur
        if (fourn.supprimer(ID_FOURNISSEUR)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès!");

            // Actualiser l'affichage
            actualiserAffichage();

            // Vider les champs
            clearFields();

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

// ==================== MODIFIER ====================

void gfournisseur::on_bmodifier_f_clicked()
{
    qDebug() << "=== CLICK SUR BMODIFIER_F ===";

    // Récupération des valeurs depuis les line edits
    QString ID_FOURNISSEUR = ui->id_le->text();
    QString NOM = ui->nom_le->text();
    QString ADRESSE = ui->adresse_le->text();
    QString EMAIL = ui->email_le->text();
    QString NUMERO_TELEPHONE = ui->telephone_le->text();
    QString CONDITION_PAIEMENT = ui->cp_le->text();

    // ==================== VALIDATION DES CHAMPS ====================

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

    if (!validerNom(NOM)) {
        QMessageBox::warning(this, "Nom invalide",
                             "Le nom ne doit contenir que des lettres et espaces (accents autorisés)\n"
                             "Longueur: 2 à 50 caractères");
        ui->nom_le->setFocus();
        return;
    }

    // Validation ADRESSE
    if (!ADRESSE.isEmpty() && !validerAdresse(ADRESSE)) {
        QMessageBox::warning(this, "Adresse invalide",
                             "L'adresse doit contenir entre 5 et 100 caractères");
        ui->adresse_le->setFocus();
        return;
    }

    // Validation EMAIL
    if (!EMAIL.isEmpty() && !validerEmail(EMAIL)) {
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

    if (!validerTelephone(NUMERO_TELEPHONE)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir exactement 8 chiffres");
        ui->telephone_le->setFocus();
        return;
    }

    // Validation CONDITION_PAIEMENT
    if (!CONDITION_PAIEMENT.isEmpty() && !validerConditionPaiement(CONDITION_PAIEMENT)) {
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
        // Modifier le fournisseur
        if (fourn.modifier(ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, NUMERO_TELEPHONE, CONDITION_PAIEMENT)) {
            QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès!");

            // Actualiser l'affichage
            actualiserAffichage();

            // Vider les champs
            clearFields();

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

// ==================== RECHERCHER PAR ID ====================

void gfournisseur::on_brechercher_f_clicked()
{
    QString idRecherche = ui->recherche_le->text().trimmed();

    // Si le champ recherche est vide, afficher TOUS les fournisseurs
    if (idRecherche.isEmpty()) {
        actualiserAffichage();
        QMessageBox::information(this, "Recherche", "Affichage de tous les fournisseurs");
        return;
    }

    QSqlQuery query;
    bool trouve = false;

    // Vider le tableau actuel
    ui->tableWidget_4->setRowCount(0);

    // Rechercher dans la base de données
    query.prepare("SELECT * FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", idRecherche);

    if (query.exec() && query.next()) {
        // Ajouter UNIQUEMENT la ligne trouvée au tableau
        int row = ui->tableWidget_4->rowCount();
        ui->tableWidget_4->insertRow(row);

        // Remplir chaque colonne
        for (int col = 0; col < 6; col++) {
            ui->tableWidget_4->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }

        // Sélectionner la ligne
        ui->tableWidget_4->selectRow(row);
        ui->tableWidget_4->scrollToItem(ui->tableWidget_4->item(row, 0), QAbstractItemView::PositionAtCenter);

        // Remplir automatiquement les champs avec les données trouvées
        QString id = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString adresse = query.value(2).toString();
        QString email = query.value(3).toString();
        QString telephone = query.value(4).toString();
        QString conditionPaiement = query.value(5).toString();

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

        trouve = true;
        QMessageBox::information(this, "Recherche",
                                 "Fournisseur trouvé avec l'ID: " + idRecherche);
    }

    if (!trouve) {
        QMessageBox::information(this, "Recherche",
                                 "Aucun fournisseur trouvé avec l'ID: " + idRecherche);

        // Réafficher tous les fournisseurs après une recherche infructueuse
        actualiserAffichage();
    }
}

// ==================== STATISTIQUES ====================

void gfournisseur::afficherGraphiqueStatistiques()
{
    QSqlQuery query;
    QMap<QString, int> stats;
    int total = 0;

    // Compter par condition de paiement
    if (query.exec("SELECT CONDITION_PAIEMENT, COUNT(*) FROM FOURNISSEUR GROUP BY CONDITION_PAIEMENT")) {
        while (query.next()) {
            QString condition = query.value(0).toString();
            int count = query.value(1).toInt();
            stats[condition.isEmpty() ? "Non spécifié" : condition] = count;
            total += count;
        }
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

void gfournisseur::on_bstatistique_f_clicked()
{
    // Afficher les statistiques dans le graphique
    afficherGraphiqueStatistiques();

    // Afficher aussi un résumé textuel
    QSqlQuery query;
    QMap<QString, int> stats;
    int total = 0;

    if (query.exec("SELECT CONDITION_PAIEMENT, COUNT(*) FROM FOURNISSEUR GROUP BY CONDITION_PAIEMENT")) {
        while (query.next()) {
            QString condition = query.value(0).toString();
            int count = query.value(1).toInt();
            stats[condition.isEmpty() ? "Non spécifié" : condition] = count;
            total += count;
        }
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

// ==================== TRI PAR ID ====================

void gfournisseur::on_btrier_f_clicked()
{
    QTableWidget *table = ui->tableWidget_4;
    if (!table || table->rowCount() == 0) {
        QMessageBox::information(this, "Tri", "Aucune donnée à trier!");
        return;
    }

    // Tri par ID (colonne 0) - Ordre croissant
    table->sortItems(0, Qt::AscendingOrder);
    QMessageBox::information(this, "Tri", "Liste triée par ID avec succès!");
}

// ==================== EXPORTATION PDF ====================

void gfournisseur::on_bexporter_f_clicked()
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
