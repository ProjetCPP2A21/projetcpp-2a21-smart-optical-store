#include "produit.h"


produit::produit(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->bajouter_p, &QPushButton::clicked, this, &produit::ajouterProduit);
    connect(ui->bmodifier_p, &QPushButton::clicked, this, &produit::modifierProduit);
    connect(ui->bsupprimer_p, &QPushButton::clicked, this, &produit::supprimerProduit);
    connect(ui->bexporter_p, &QPushButton::clicked, this, &produit::exporterPdf);
}

produit::~produit() {}

void produit::chargerDonnees() {}
void produit::ajouterProduit() {}
void produit::modifierProduit() {}
void produit::supprimerProduit() {}
void produit::rechercherProduit(const QString &) {}
void produit::exporterPdf() {}

