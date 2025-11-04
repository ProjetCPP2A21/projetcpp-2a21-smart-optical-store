#include "gfournisseur.h"
#include "ui_gfournisseur.h"
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>

gfournisseur::gfournisseur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gfournisseur)
{
    ui->setupUi(this);

    // Validateur pour téléphone seulement
    ui->telephone_le->setValidator(new QIntValidator(0, 99999999, this));

    // Afficher les données au démarrage
    actualiserAffichage();
}

gfournisseur::~gfournisseur()
{
    delete ui;
}

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
}

void gfournisseur::on_bajouter_f_clicked()
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
        actualiserAffichage();

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

void gfournisseur::on_bsupprimer_f_clicked()
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
            actualiserAffichage();

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
void gfournisseur::on_bmodifier_f_clicked()
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
            actualiserAffichage();

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
