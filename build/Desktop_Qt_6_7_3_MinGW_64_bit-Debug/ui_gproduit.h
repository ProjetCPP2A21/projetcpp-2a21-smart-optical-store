/********************************************************************************
** Form generated from reading UI file 'gproduit.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPRODUIT_H
#define UI_GPRODUIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gproduit
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_9;
    QGroupBox *groupBox;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label;
    QGroupBox *groupBox1;
    QPushButton *bc_2;
    QPushButton *bp_2;
    QPushButton *bf_2;
    QPushButton *ba_2;
    QPushButton *bem_2;
    QGroupBox *groupBox_3;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *pushButton_15;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QComboBox *comboBox_8;
    QComboBox *comboBox_9;
    QComboBox *comboBox_10;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gproduit)
    {
        if (gproduit->objectName().isEmpty())
            gproduit->setObjectName("gproduit");
        gproduit->resize(1558, 810);
        centralwidget = new QWidget(gproduit);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1551, 771));
        page = new QWidget();
        page->setObjectName("page");
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(480, 80, 421, 51));
        label_9->setStyleSheet(QString::fromUtf8("font: 28pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(229, 200, 1051, 351));
        groupBox->setStyleSheet(QString::fromUtf8("gridline-color: rgb(0, 0, 0);"));
        tableWidget_2 = new QTableWidget(groupBox);
        if (tableWidget_2->columnCount() < 8)
            tableWidget_2->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget_2->rowCount() < 5)
            tableWidget_2->setRowCount(5);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(10, 90, 1011, 211));
        tableWidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(175, 220, 209);\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_10 = new QPushButton(groupBox);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(130, 30, 90, 29));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"\n"
""));
        pushButton_12 = new QPushButton(groupBox);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(320, 30, 90, 29));
        pushButton_12->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_13 = new QPushButton(groupBox);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(510, 30, 90, 29));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        pushButton_14 = new QPushButton(groupBox);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(750, 30, 90, 29));
        pushButton_14->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
""));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 141, 121));
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        groupBox1 = new QGroupBox(page);
        groupBox1->setObjectName("groupBox1");
        groupBox1->setGeometry(QRect(10, 150, 211, 571));
        groupBox1->setStyleSheet(QString::fromUtf8(""));
        bc_2 = new QPushButton(groupBox1);
        bc_2->setObjectName("bc_2");
        bc_2->setGeometry(QRect(10, 120, 191, 101));
        bc_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bp_2 = new QPushButton(groupBox1);
        bp_2->setObjectName("bp_2");
        bp_2->setGeometry(QRect(10, 350, 191, 101));
        bp_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bf_2 = new QPushButton(groupBox1);
        bf_2->setObjectName("bf_2");
        bf_2->setGeometry(QRect(10, 230, 191, 101));
        bf_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        ba_2 = new QPushButton(groupBox1);
        ba_2->setObjectName("ba_2");
        ba_2->setGeometry(QRect(10, 460, 191, 101));
        ba_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 16pt \"Segoe UI\";"));
        bem_2 = new QPushButton(groupBox1);
        bem_2->setObjectName("bem_2");
        bem_2->setGeometry(QRect(10, 10, 191, 101));
        bem_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(1310, 80, 221, 561));
        groupBox_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 20, 161, 20));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 50, 63, 20));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 110, 63, 20));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 180, 63, 20));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 250, 63, 20));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 330, 63, 20));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 410, 63, 20));
        pushButton_15 = new QPushButton(groupBox_3);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(100, 448, 90, 51));
        pushButton_15->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);"));
        comboBox_6 = new QComboBox(groupBox_3);
        comboBox_6->setObjectName("comboBox_6");
        comboBox_6->setGeometry(QRect(30, 70, 82, 31));
        comboBox_7 = new QComboBox(groupBox_3);
        comboBox_7->setObjectName("comboBox_7");
        comboBox_7->setGeometry(QRect(30, 130, 82, 31));
        comboBox_8 = new QComboBox(groupBox_3);
        comboBox_8->setObjectName("comboBox_8");
        comboBox_8->setGeometry(QRect(30, 210, 82, 31));
        comboBox_9 = new QComboBox(groupBox_3);
        comboBox_9->setObjectName("comboBox_9");
        comboBox_9->setGeometry(QRect(30, 280, 82, 31));
        comboBox_10 = new QComboBox(groupBox_3);
        comboBox_10->setObjectName("comboBox_10");
        comboBox_10->setGeometry(QRect(30, 357, 82, 31));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        gproduit->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gproduit);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1558, 25));
        gproduit->setMenuBar(menubar);
        statusbar = new QStatusBar(gproduit);
        statusbar->setObjectName("statusbar");
        gproduit->setStatusBar(statusbar);

        retranslateUi(gproduit);

        QMetaObject::connectSlotsByName(gproduit);
    } // setupUi

    void retranslateUi(QMainWindow *gproduit)
    {
        gproduit->setWindowTitle(QCoreApplication::translate("gproduit", "gproduit", nullptr));
        label_9->setText(QCoreApplication::translate("gproduit", "Gestion  de produit ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("gproduit", "GroupBox", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("gproduit", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("gproduit", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("gproduit", "Stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("gproduit", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("gproduit", "Couleur", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("gproduit", "Epaisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("gproduit", "Diametre", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("gproduit", "Taille", nullptr));
        pushButton_10->setText(QCoreApplication::translate("gproduit", "\342\236\225Ajouter", nullptr));
        pushButton_12->setText(QCoreApplication::translate("gproduit", "\342\234\217\357\270\217Modifier", nullptr));
        pushButton_13->setText(QCoreApplication::translate("gproduit", "\360\237\227\221\357\270\217Supprimer", nullptr));
        pushButton_14->setText(QCoreApplication::translate("gproduit", "\360\237\223\244Exporter", nullptr));
        label->setText(QString());
        groupBox1->setTitle(QString());
        bc_2->setText(QCoreApplication::translate("gproduit", "\360\237\247\221\342\200\215\360\237\222\274Clients", nullptr));
        bp_2->setText(QCoreApplication::translate("gproduit", "\360\237\223\246Produits", nullptr));
        bf_2->setText(QCoreApplication::translate("gproduit", "\360\237\232\232Fournisseur", nullptr));
        ba_2->setText(QCoreApplication::translate("gproduit", "\360\237\223\204Ordonnance", nullptr));
        bem_2->setText(QCoreApplication::translate("gproduit", "\360\237\221\244Employee", nullptr));
        groupBox_3->setTitle(QString());
        label_10->setText(QCoreApplication::translate("gproduit", "Ajouter un produit ", nullptr));
        label_11->setText(QCoreApplication::translate("gproduit", "Type", nullptr));
        label_12->setText(QCoreApplication::translate("gproduit", "Stock", nullptr));
        label_13->setText(QCoreApplication::translate("gproduit", "Prix", nullptr));
        label_14->setText(QCoreApplication::translate("gproduit", "Couleur", nullptr));
        label_15->setText(QCoreApplication::translate("gproduit", "Epaisseur", nullptr));
        label_16->setText(QCoreApplication::translate("gproduit", "Diametree", nullptr));
        pushButton_15->setText(QCoreApplication::translate("gproduit", "\342\236\225Ajouter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gproduit: public Ui_gproduit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPRODUIT_H
