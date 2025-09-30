#include "mainwindowclient.h"
#include "ui_mainwindowclient.h"

MainWindowclient::MainWindowclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowclient)
{
    ui->setupUi(this);
}

MainWindowclient::~MainWindowclient()
{
    delete ui;
}
