#include "gordonnance.h"
#include "ui_gordonnance.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QDate>

Gordonnance::Gordonnance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gordonnance),
    cinSelectionne("")
{
    ui->setupUi(this);

    // Configurer le dateEdit avec la date actuelle
    ui->dateEdit->setDate(QDate::currentDate());

    // Afficher les données au lancement
    actualiserAffichage();
}

Gordonnance::~Gordonnance()
{
    delete ui;
}

void Gordonnance::actualiserAffichage()
{
    ord.afficher(ui->tableWidget);
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
