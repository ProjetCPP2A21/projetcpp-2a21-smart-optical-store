#include "authentification.h"
#include "authentification.h"

authentification::authentification(Ui::optismart *ui, QWidget *parent)
    : QWidget(parent), ui(ui)
{
    connect(ui->benregistrer_e_2, &QPushButton::clicked, this, &authentification::seConnecter);
    connect(ui->bannuler_e_2, &QPushButton::clicked, this, &authentification::annuler);
}

authentification::~authentification() {}

void authentification::seConnecter() {}
void authentification::annuler() {}
