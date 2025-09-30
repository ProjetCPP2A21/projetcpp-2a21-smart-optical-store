#include "gproduit.h"
#include "ui_gproduit.h"

gproduit::gproduit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gproduit)
{
    ui->setupUi(this);
}

gproduit::~gproduit()
{
    delete ui;
}
