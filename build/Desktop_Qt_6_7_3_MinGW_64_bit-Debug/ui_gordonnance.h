/********************************************************************************
** Form generated from reading UI file 'gordonnance.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GORDONNANCE_H
#define UI_GORDONNANCE_H

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

class Ui_Gordonnance
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QTableWidget *tableWidget;
    QPushButton *btnModifier;
    QLabel *label_3;
    QLineEdit *lineEditMedecin;
    QLabel *label_5;
    QLabel *label_4;
    QLineEdit *lineEditNom;
    QDateEdit *dateEdit;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *lineEditPrenom;
    QLabel *label_2;
    QLineEdit *lineEditCIN;
    QPushButton *btnAjouter;
    QLabel *label;
    QLabel *label_9;
    QPushButton *pushButton;
    QPushButton *btnSupprimer;
    QLineEdit *lineEditCIN_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Gordonnance)
    {
        if (Gordonnance->objectName().isEmpty())
            Gordonnance->setObjectName("Gordonnance");
        Gordonnance->resize(1360, 692);
        Gordonnance->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #a8d9d0,\n"
"        stop:0.5 #d3e9d4,\n"
"        stop:1 #f2e1c9\n"
"    );\n"
"}"));
        centralwidget = new QWidget(Gordonnance);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 90, 231, 631));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 20, 201, 101));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_4->setIconSize(QSize(150, 150));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 240, 201, 101));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 350, 201, 101));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 460, 201, 101));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 130, 201, 101));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        pushButton_9->setIconSize(QSize(191, 101));
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
        tableWidget->setGeometry(QRect(410, 170, 511, 201));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnModifier = new QPushButton(centralwidget);
        btnModifier->setObjectName("btnModifier");
        btnModifier->setGeometry(QRect(1040, 430, 81, 31));
        btnModifier->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1000, 210, 49, 16));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditMedecin = new QLineEdit(centralwidget);
        lineEditMedecin->setObjectName("lineEditMedecin");
        lineEditMedecin->setGeometry(QRect(1060, 340, 151, 24));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1000, 300, 49, 16));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1000, 250, 49, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        lineEditNom = new QLineEdit(centralwidget);
        lineEditNom->setObjectName("lineEditNom");
        lineEditNom->setGeometry(QRect(1040, 300, 171, 24));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(1050, 390, 110, 25));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(1000, 390, 49, 16));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(1000, 340, 49, 16));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPrenom = new QLineEdit(centralwidget);
        lineEditPrenom->setObjectName("lineEditPrenom");
        lineEditPrenom->setGeometry(QRect(1050, 250, 141, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1030, 100, 361, 101));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 italic 10pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        lineEditCIN = new QLineEdit(centralwidget);
        lineEditCIN->setObjectName("lineEditCIN");
        lineEditCIN->setGeometry(QRect(1040, 210, 141, 24));
        btnAjouter = new QPushButton(centralwidget);
        btnAjouter->setObjectName("btnAjouter");
        btnAjouter->setGeometry(QRect(940, 430, 81, 31));
        btnAjouter->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(540, 20, 311, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 700 italic 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 0, 151, 111));
        label_9->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/552966492_691544266651586_7706130658263486080_n.png")));
        label_9->setScaledContents(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1140, 430, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        btnSupprimer = new QPushButton(centralwidget);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setGeometry(QRect(1039, 483, 101, 31));
        btnSupprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        lineEditCIN_2 = new QLineEdit(centralwidget);
        lineEditCIN_2->setObjectName("lineEditCIN_2");
        lineEditCIN_2->setGeometry(QRect(480, 120, 141, 24));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(670, 120, 101, 21));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(490, 410, 111, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(630, 410, 111, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        Gordonnance->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Gordonnance);
        statusbar->setObjectName("statusbar");
        Gordonnance->setStatusBar(statusbar);

        retranslateUi(Gordonnance);

        QMetaObject::connectSlotsByName(Gordonnance);
    } // setupUi

    void retranslateUi(QMainWindow *Gordonnance)
    {
        Gordonnance->setWindowTitle(QCoreApplication::translate("Gordonnance", "Gordonnance", nullptr));
        groupBox->setTitle(QString());
        pushButton_4->setText(QCoreApplication::translate("Gordonnance", "\360\237\221\244Employee", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Gordonnance", "\360\237\232\232Fournisseur", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Gordonnance", "\360\237\223\246Produits", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Gordonnance", "\360\237\247\276Ordonnance", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Gordonnance", "\360\237\247\221\342\200\215\360\237\222\274Clients", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Gordonnance", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Gordonnance", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Gordonnance", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Gordonnance", "Medecin", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Gordonnance", "Date", nullptr));
        btnModifier->setText(QCoreApplication::translate("Gordonnance", "Modifier", nullptr));
        label_3->setText(QCoreApplication::translate("Gordonnance", "CIN:", nullptr));
        label_5->setText(QCoreApplication::translate("Gordonnance", "Nom:", nullptr));
        label_4->setText(QCoreApplication::translate("Gordonnance", "Prenom:", nullptr));
        label_7->setText(QCoreApplication::translate("Gordonnance", "Date:", nullptr));
        label_6->setText(QCoreApplication::translate("Gordonnance", "Medecin:", nullptr));
        label_2->setText(QCoreApplication::translate("Gordonnance", "Ajouter une ordonnance", nullptr));
        btnAjouter->setText(QCoreApplication::translate("Gordonnance", "Ajouter", nullptr));
        label->setText(QCoreApplication::translate("Gordonnance", "Gestion des ordonnance", nullptr));
        label_9->setText(QString());
        pushButton->setText(QCoreApplication::translate("Gordonnance", "Recherche", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("Gordonnance", "Supprimer", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Gordonnance", "Recherche", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Gordonnance", "Trier", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Gordonnance", "Exporter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gordonnance: public Ui_Gordonnance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GORDONNANCE_H
