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

gfournisseur::gfournisseur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gfournisseur)
{
    ui->setupUi(this);

    // Validateur pour NUMERO_TELEPHONE (8 chiffres exactement)
    ui->telephone_le->setValidator(new QIntValidator(0, 99999999, this));

    // Connexions pour la validation en temps réel
    connect(ui->nom_le, &QLineEdit::textChanged, this, &gfournisseur::on_nom_le_textChanged);
    connect(ui->email_le, &QLineEdit::textChanged, this, &gfournisseur::on_email_le_textChanged);
    connect(ui->telephone_le, &QLineEdit::textChanged, this, &gfournisseur::on_telephone_le_textChanged);

    // Connexion pour la sélection dans le tableau
    connect(ui->tableWidget_4, &QTableWidget::itemClicked, this, &gfournisseur::on_tableWidget_4_itemClicked);

    // Afficher les données au démarrage
    actualiserAffichage();
}

gfournisseur::~gfournisseur()
{
    delete ui;
}

// ==================== MÉTHODES DE VALIDATION ====================

bool gfournisseur::validerNom(const QString &nom)
{
    if (nom.isEmpty()) return true; // Laisser vide pour le moment

    // Expression régulière : lettres, espaces, accents français, &, -
    QRegularExpression regex("^[a-zA-ZÀ-ÿœŒ\\s\\-\\&]{2,50}$");
    return regex.match(nom).hasMatch();
}

bool gfournisseur::validerEmail(const QString &email)
{
    if (email.isEmpty()) return true; // Laisser vide pour le moment

    // Expression régulière pour email
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool gfournisseur::validerTelephone(const QString &telephone)
{
    if (telephone.isEmpty()) return true; // Laisser vide pour le moment

    // Exactement 8 chiffres
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool gfournisseur::validerAdresse(const QString &adresse)
{
    if (adresse.isEmpty()) return true; // Laisser vide pour le moment

    // Longueur entre 5 et 100 caractères
    return adresse.length() >= 5 && adresse.length() <= 100;
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

    // Réinitialiser les tooltips
    ui->nom_le->setToolTip("");
    ui->email_le->setToolTip("");
    ui->telephone_le->setToolTip("");
    ui->adresse_le->setToolTip("");

    // Remettre le focus sur le premier champ
    ui->id_le->setFocus();
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

    // Validation de la longueur des champs
    if (ID_FOURNISSEUR.length() > 50) {
        QMessageBox::warning(this, "ID_FOURNISSEUR trop long", "L'ID_FOURNISSEUR ne doit pas dépasser 50 caractères!");
        return;
    }
    if (CONDITION_PAIEMENT.length() > 50) {
        QMessageBox::warning(this, "CONDITION_PAIEMENT trop longue", "La CONDITION_PAIEMENT ne doit pas dépasser 50 caractères!");
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

// ==================== STATISTIQUES CONDITION PAIEMENT ====================


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

// ==================== RECHERCHER PAR ID ====================

void gfournisseur::on_brechercher_f_clicked()
{
    QString idRecherche = ui->recherche_le->text().trimmed();

    if (idRecherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID à rechercher!");
        ui->recherche_le->setFocus();
        return;
    }

    QTableWidget *table = ui->tableWidget_4;
    bool trouve = false;

    // Réinitialiser les couleurs de toutes les lignes
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *cell = table->item(row, col);
            if (cell) {
                cell->setBackground(QBrush(Qt::white));
            }
        }
    }

    // Parcourir toutes les lignes pour trouver l'ID
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem *item = table->item(row, 0); // Colonne 0 = ID_FOURNISSEUR

        if (item && item->text().compare(idRecherche, Qt::CaseInsensitive) == 0) {
            // Sélectionner la ligne trouvée
            table->selectRow(row);
            table->scrollToItem(item, QAbstractItemView::PositionAtCenter);

            // Surligner la ligne en jaune
            for (int col = 0; col < table->columnCount(); ++col) {
                QTableWidgetItem *cell = table->item(row, col);
                if (cell) {
                    cell->setBackground(QBrush(QColor(255, 255, 0))); // Jaune
                }
            }

            // Remplir automatiquement les champs avec les données trouvées
            on_tableWidget_4_itemClicked(item);

            trouve = true;
            QMessageBox::information(this, "Recherche",
                                     "Fournisseur trouvé avec l'ID: " + idRecherche);
            break;
        }
    }

    if (!trouve) {
        QMessageBox::information(this, "Recherche",
                                 "Aucun fournisseur trouvé avec l'ID: " + idRecherche);
    }
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
