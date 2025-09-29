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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QLabel *label;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QTableWidget *tableWidget;
    QSpinBox *spinBox;
    QGroupBox *groupBox_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_11;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1346, 850);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 255, 246);\n"
"background-image: url(:/back.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 90, 221, 551));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 201, 101));
        pushButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"\n"
"color: rgb(51, 51, 51);"));
        pushButton->setIconSize(QSize(150, 150));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 220, 201, 101));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 330, 201, 101));
        pushButton_4->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 440, 201, 101));
        pushButton_5->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 110, 201, 101));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_2->setIconSize(QSize(191, 101));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, -30, 131, 131));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/logo.png);"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(240, 150, 1041, 421));
        groupBox_2->setStyleSheet(QString::fromUtf8("border-top-color: rgb(255, 227, 181);"));
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(150, 30, 90, 29));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"\n"
""));
        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(320, 30, 90, 29));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(450, 30, 90, 29));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(610, 30, 90, 29));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
""));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(0, 7, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(1, 6, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(1, 7, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(2, 4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(2, 5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(2, 6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(2, 7, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(3, 3, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(3, 4, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setItem(3, 5, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(3, 6, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(3, 7, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setItem(4, 3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(4, 4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(4, 5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(4, 6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(4, 7, __qtablewidgetitem43);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 80, 1101, 271));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(960, 310, 44, 29));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(1300, 160, 181, 421));
        groupBox_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 161, 20));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 63, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 120, 63, 20));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 190, 63, 20));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 240, 63, 20));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 290, 63, 20));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 340, 63, 20));
        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(70, 380, 90, 29));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 90, 82, 28));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(30, 150, 82, 28));
        comboBox_3 = new QComboBox(groupBox_3);
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(30, 210, 82, 28));
        comboBox_4 = new QComboBox(groupBox_3);
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(30, 260, 82, 28));
        comboBox_5 = new QComboBox(groupBox_3);
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(30, 310, 82, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1346, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\274Employee", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\360\237\232\232Fournisseur", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246Produits", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\360\237\247\276Ordonnance", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\274Clients", nullptr));
        label->setText(QString());
        groupBox_2->setTitle(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\342\236\225Ajouter", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217Modifier", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217Supprimer", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244Exporter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Couleur ", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Epaisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Diametre", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Taille", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Lunettes", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "150.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(0, 4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Noir", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(0, 5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "0.5cm", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(0, 6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "52mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(0, 7);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(1, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Lentilles", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(1, 2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(1, 3);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "30.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(1, 4);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Blanc", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(1, 5);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "0.2cm", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(1, 6);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "14.0mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(1, 7);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(2, 1);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Accessoirs", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(2, 2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(2, 3);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "20.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(2, 4);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Noir", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(2, 5);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "0.3cm", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(2, 7);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(3, 1);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Lunettes", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->item(3, 2);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "25", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->item(3, 3);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "180.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->item(3, 4);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Torro\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->item(3, 5);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "0.5cm", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->item(3, 6);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "54mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->item(3, 7);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(4, 1);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "Lunettes", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(4, 2);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->item(4, 3);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "200.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->item(4, 4);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("MainWindow", "Gris", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->item(4, 5);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("MainWindow", "0.4cm", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->item(4, 6);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("MainWindow", "50mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->item(4, 7);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        groupBox_3->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Ajouter un produit ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Epaisseur", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Domare", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\342\236\225Ajouter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
