#include "gfournisseur.h"
#include "ui_gfournisseur.h"

gfournisseur::gfournisseur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gfournisseur)
{
    ui->setupUi(this);
}

gfournisseur::~gfournisseur()
{
    delete ui;
}
