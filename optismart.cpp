#include "employe.h"
#include "authentification.h"
#include "client.h"
#include "produit.h"
#include "fournisseur.h"
#include "ordonnance.h"
#include "optismart.h"
#include "ui_optismart.h"

optismart::optismart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::optismart)
{
    ui->setupUi(this);

    // ---- Initialiser la classe employe ----
    // On relie l'interface à la logique du modèle employe
    employe *employePage = new employe(ui, this);
    employePage->afficherDansTable(); // charge les données existantes au démarrage

    // ---- Appliquer un fond dégradé à la fenêtre principale ----
    QLinearGradient gradient(0, 0, 0, this->height());
    gradient.setColorAt(0.0, QColor(168, 230, 207));  // Mint
    gradient.setColorAt(1.0, QColor(255, 211, 182));  // Peach

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window, QBrush(gradient));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // ---- Navigation entre les pages du stackedWidget ----
    auto setPage = [=](int index) {
        ui->stackedWidget->setCurrentIndex(index);
    };

    // Page Employé (menu 1)
    connect(ui->bem_1, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_1, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_1, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_1, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_1, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Client (menu 2)
    connect(ui->bem_3, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_3, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_3, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_3, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_3, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Produit (menu 3)
    connect(ui->bem_4, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_4, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_4, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_4, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_4, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Fournisseur (menu 4)
    connect(ui->bem_5, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_5, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_5, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_5, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_5, &QPushButton::clicked, this, [=]() { setPage(4); });

    // Page Ordonnance (menu 5)
    connect(ui->bem_6, &QPushButton::clicked, this, [=]() { setPage(0); });
    connect(ui->bc_6, &QPushButton::clicked, this, [=]() { setPage(1); });
    connect(ui->bp_6, &QPushButton::clicked, this, [=]() { setPage(2); });
    connect(ui->bf_6, &QPushButton::clicked, this, [=]() { setPage(3); });
    connect(ui->bo_6, &QPushButton::clicked, this, [=]() { setPage(4); });


    /*ui->stackedWidget->setCurrentIndex(5);*/
}

optismart::~optismart()
{
    delete ui;
}
