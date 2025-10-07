#include "gemployev1.h"
#include "ui_gemployev1.h"

Gemploye::Gemploye(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gemploye)
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
    //employe
    connect(ui->bem_1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Go to page index 1 (the second page)
    });
    connect(ui->bc_1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1); // Go to page index 1 (the second page)
    });
    connect(ui->bp_1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Go to page index 1 (the second page)
    });
    connect(ui->bf_1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3); // Go to page index 1 (the second page)
    });
    connect(ui->bo_1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(4); // Go to page index 1 (the second page)
    });
    //client---
    connect(ui->bem_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Go to page index 1 (the second page)
    });
    connect(ui->bc_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1); // Go to page index 1 (the second page)
    });
    connect(ui->bp_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Go to page index 1 (the second page)
    });
    connect(ui->bf_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3); // Go to page index 1 (the second page)
    });
    connect(ui->bo_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(4); // Go to page index 1 (the second page)
    });
    //produit

    connect(ui->bem_4, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Go to page index 1 (the second page)
    });
    connect(ui->bc_4, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1); // Go to page index 1 (the second page)
    });
    connect(ui->bp_4, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Go to page index 1 (the second page)
    });
    connect(ui->bf_4, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3); // Go to page index 1 (the second page)
    });
    connect(ui->bo_4, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(4); // Go to page index 1 (the second page)
    });

    //fournisseur

    connect(ui->bem_5, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Go to page index 1 (the second page)
    });
    connect(ui->bc_5, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1); // Go to page index 1 (the second page)
    });
    connect(ui->bp_5, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Go to page index 1 (the second page)
    });
    connect(ui->bf_5, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3); // Go to page index 1 (the second page)
    });





}


Gemploye::~Gemploye()
{
    delete ui;
}
