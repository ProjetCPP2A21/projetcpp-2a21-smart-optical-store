#include "gordonnance.h"
#include "ui_gordonnance.h"

Gordonnance::Gordonnance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gordonnance)
{
    ui->setupUi(this);
}

Gordonnance::~Gordonnance()
{
    delete ui;
}
