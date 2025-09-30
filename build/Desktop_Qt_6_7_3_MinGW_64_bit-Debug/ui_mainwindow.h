/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *cinEdit;
    QLineEdit *prenomEdit;
    QLineEdit *nomEdit;
    QLineEdit *medecinEdit;
    QPushButton *addButton;
    QPushButton *quitButton;
    QDateEdit *dateEdit;
    QGroupBox *menu;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_13;
    QLabel *label_8;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1049, 745);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #a8d9d0,\n"
"        stop:0.5 #d3e9d4,\n"
"        stop:1 #f2e1c9\n"
"    );\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 80, 311, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 700 italic 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(250, 190, 511, 201));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(850, 110, 361, 101));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 italic 10pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(810, 190, 49, 16));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(810, 230, 49, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(810, 280, 49, 16));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(810, 320, 49, 16));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(810, 360, 49, 16));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        cinEdit = new QLineEdit(centralwidget);
        cinEdit->setObjectName("cinEdit");
        cinEdit->setGeometry(QRect(850, 190, 141, 24));
        prenomEdit = new QLineEdit(centralwidget);
        prenomEdit->setObjectName("prenomEdit");
        prenomEdit->setGeometry(QRect(860, 230, 141, 24));
        nomEdit = new QLineEdit(centralwidget);
        nomEdit->setObjectName("nomEdit");
        nomEdit->setGeometry(QRect(850, 280, 171, 24));
        medecinEdit = new QLineEdit(centralwidget);
        medecinEdit->setObjectName("medecinEdit");
        medecinEdit->setGeometry(QRect(870, 320, 151, 24));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(810, 410, 81, 31));
        addButton->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(920, 410, 81, 31));
        quitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(850, 360, 110, 25));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        menu = new QGroupBox(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(10, 0, 211, 731));
        menu->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);"));
        pushButton = new QPushButton(menu);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 180, 191, 101));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_2 = new QPushButton(menu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(11, 290, 191, 101));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";\n"
""));
        pushButton_3 = new QPushButton(menu);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(11, 400, 191, 101));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";\n"
""));
        pushButton_5 = new QPushButton(menu);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(11, 510, 191, 101));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_13 = new QPushButton(menu);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(11, 620, 191, 101));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";\n"
""));
        label_8 = new QLabel(menu);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 50, 151, 111));
        label_8->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/552966492_691544266651586_7706130658263486080_n.png")));
        label_8->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Gestion des ordonnance", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Medecin", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ajouter une ordonnance", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "CIN:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Prenom:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Medecin:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "menu", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "employe", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "produit", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "client", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "ordonnance", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "fournisseur", nullptr));
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
