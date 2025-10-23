#include "fournisseur.h"


fournisseur::fournisseur(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->bajouter_f, &QPushButton::clicked, this, &fournisseur::ajouterFournisseur);
    connect(ui->bmodifier_f, &QPushButton::clicked, this, &fournisseur::modifierFournisseur);
    connect(ui->bsupprimer_f, &QPushButton::clicked, this, &fournisseur::supprimerFournisseur);
    connect(ui->bexporter_f, &QPushButton::clicked, this, &fournisseur::exporterPdf);
}

fournisseur::~fournisseur() {}

void fournisseur::chargerDonnees() {}
void fournisseur::ajouterFournisseur() {}
void fournisseur::modifierFournisseur() {}
void fournisseur::supprimerFournisseur() {}
void fournisseur::rechercherFournisseur(const QString &) {}
void fournisseur::exporterPdf() {}

