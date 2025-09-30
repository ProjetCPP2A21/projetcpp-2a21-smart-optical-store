#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::on_quitButton_clicked);

    // Set up table
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"CIN", "Prenom", "Nom", "Medecin", "Date"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    // Check if UI elements are valid
    if (!ui->cinEdit || !ui->prenomEdit || !ui->nomEdit || !ui->medecinEdit || !ui->dateEdit || !ui->tableWidget) {
        QMessageBox::critical(this, "Error", "UI elements not found!");
        return;
    }

    // Validate input
    if (ui->cinEdit->text().isEmpty() || ui->prenomEdit->text().isEmpty() || ui->nomEdit->text().isEmpty() ||
        ui->medecinEdit->text().isEmpty() || ui->dateEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis.");
        return;
    }

    // Add data to table
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ui->cinEdit->text()));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(ui->prenomEdit->text()));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(ui->nomEdit->text()));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(ui->medecinEdit->text()));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(ui->dateEdit->text()));

    // Clear input fields
    ui->cinEdit->clear();
    ui->prenomEdit->clear();
    ui->nomEdit->clear();
    ui->medecinEdit->clear();
    ui->dateEdit->clear();
}

void MainWindow::on_quitButton_clicked()
{
    close();
}
