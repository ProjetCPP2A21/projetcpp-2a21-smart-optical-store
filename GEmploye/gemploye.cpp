#include "gemploye.h"
#include "./ui_gemploye.h"
#include <QLinearGradient>
#include <QPalette>

GEmploye::GEmploye(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GEmploye)
{
    ui->setupUi(this);


    // Apply gradient to central widget
    QLinearGradient gradient(0, 0, 0, this->height());
    gradient.setColorAt(0.0, QColor(168, 230, 207));  // mint
    gradient.setColorAt(1.0, QColor(255, 211, 182));  // peach

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window, QBrush(gradient));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

GEmploye::~GEmploye()
{
    delete ui;
}
