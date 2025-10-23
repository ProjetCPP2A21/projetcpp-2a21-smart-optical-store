#include "ordonnance.h"


ordonnance::ordonnance(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->addButton, &QPushButton::clicked, this, &ordonnance::ajouterOrdonnance);
    connect(ui->quitButton, &QPushButton::clicked, this, &ordonnance::modifierOrdonnance);
}

ordonnance::~ordonnance() {}

void ordonnance::chargerDonnees() {}
void ordonnance::ajouterOrdonnance() {}
void ordonnance::modifierOrdonnance() {}
void ordonnance::supprimerOrdonnance() {}
void ordonnance::rechercherOrdonnance(const QString &) {}
void ordonnance::exporterPdf() {}
