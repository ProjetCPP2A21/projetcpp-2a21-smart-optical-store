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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
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
    QLabel *label;
    QGroupBox *groupBox1;
    QPushButton *bc;
    QPushButton *bp;
    QPushButton *bf;
    QPushButton *ba;
    QPushButton *bem;
    QGroupBox *groupBox;
    QTableWidget *tableWidget;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1539, 850);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/back.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(1310, 90, 221, 561));
        groupBox_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 161, 20));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 50, 63, 20));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 110, 63, 20));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 180, 63, 20));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 250, 63, 20));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 330, 63, 20));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 410, 63, 20));
        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(100, 448, 90, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 70, 82, 31));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(30, 130, 82, 31));
        comboBox_3 = new QComboBox(groupBox_3);
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(30, 210, 82, 31));
        comboBox_4 = new QComboBox(groupBox_3);
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(30, 280, 82, 31));
        comboBox_5 = new QComboBox(groupBox_3);
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(30, 357, 82, 31));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 141, 121));
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName("groupBox1");
        groupBox1->setGeometry(QRect(10, 160, 211, 571));
        groupBox1->setStyleSheet(QString::fromUtf8(""));
        bc = new QPushButton(groupBox1);
        bc->setObjectName("bc");
        bc->setGeometry(QRect(10, 120, 191, 101));
        bc->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bp = new QPushButton(groupBox1);
        bp->setObjectName("bp");
        bp->setGeometry(QRect(10, 350, 191, 101));
        bp->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bf = new QPushButton(groupBox1);
        bf->setObjectName("bf");
        bf->setGeometry(QRect(10, 230, 191, 101));
        bf->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        ba = new QPushButton(groupBox1);
        ba->setObjectName("ba");
        ba->setGeometry(QRect(10, 460, 191, 101));
        ba->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 16pt \"Segoe UI\";"));
        bem = new QPushButton(groupBox1);
        bem->setObjectName("bem");
        bem->setGeometry(QRect(10, 10, 191, 101));
        bem->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(229, 210, 1051, 351));
        groupBox->setStyleSheet(QString::fromUtf8("gridline-color: rgb(0, 0, 0);"));
        tableWidget = new QTableWidget(groupBox);
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 90, 1011, 211));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(175, 220, 209);\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(130, 30, 90, 29));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"\n"
""));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(320, 30, 90, 29));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(510, 30, 90, 29));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(750, 30, 90, 29));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
""));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(480, 90, 421, 51));
        label_9->setStyleSheet(QString::fromUtf8("font: 28pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1539, 25));
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
        groupBox_3->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Ajouter un produit ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Epaisseur", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Diametree", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\342\236\225Ajouter", nullptr));
        label->setText(QString());
        groupBox1->setTitle(QString());
        bc->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\274Clients", nullptr));
        bp->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246Produits", nullptr));
        bf->setText(QCoreApplication::translate("MainWindow", "\360\237\232\232Fournisseur", nullptr));
        ba->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204Ordonnance", nullptr));
        bem->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244Employee", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Epaisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Diametre", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Taille", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\342\236\225Ajouter", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217Modifier", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217Supprimer", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244Exporter", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Gestion  de produit ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
