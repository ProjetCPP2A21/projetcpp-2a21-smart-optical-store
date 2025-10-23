    #include "client.h"

client::client(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->bajouter_c, &QPushButton::clicked, this, &client::ajouterClient);
    connect(ui->bmodifier_c, &QPushButton::clicked, this, &client::modifierClient);
    connect(ui->bsupprimer_c, &QPushButton::clicked, this, &client::supprimerClient);
    connect(ui->bexporter_c, &QPushButton::clicked, this, &client::exporterPdf);
    connect(ui->bstatistique_c, &QPushButton::clicked, this, &client::afficherStatistiques);
}

client::~client() {}

void client::chargerDonnees() {}
void client::ajouterClient() {}
void client::modifierClient() {}
void client::supprimerClient() {}
void client::rechercherClient(const QString &) {}
void client::exporterPdf() {}
void client::afficherStatistiques() {}
