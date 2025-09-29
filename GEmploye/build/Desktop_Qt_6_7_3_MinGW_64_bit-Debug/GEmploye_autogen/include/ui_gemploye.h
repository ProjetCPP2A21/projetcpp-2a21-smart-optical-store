/********************************************************************************
** Form generated from reading UI file 'gemploye.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEMPLOYE_H
#define UI_GEMPLOYE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GEmploye
{
public:
    QWidget *centralwidget;
    QGroupBox *menu;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_13;
    QGroupBox *tab;
    QTableWidget *tableWidget;
    QPushButton *pushButton_15;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QLabel *label;
    QGroupBox *groupBox;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QLineEdit *linetel;
    QLineEdit *lineid;
    QLabel *non;
    QLabel *label_6;
    QLineEdit *linenom;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *lineprenon;
    QLineEdit *lineemail;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GEmploye)
    {
        if (GEmploye->objectName().isEmpty())
            GEmploye->setObjectName("GEmploye");
        GEmploye->resize(1500, 925);
        GEmploye->setBaseSize(QSize(851, 1500));
        QFont font;
        font.setPointSize(14);
        GEmploye->setFont(font);
        centralwidget = new QWidget(GEmploye);
        centralwidget->setObjectName("centralwidget");
        menu = new QGroupBox(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(0, -20, 211, 851));
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
        tab = new QGroupBox(centralwidget);
        tab->setObjectName("tab");
        tab->setGeometry(QRect(250, 200, 891, 581));
        tableWidget = new QTableWidget(tab);
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 60, 871, 431));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 220);\n"
"font: 10pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        tableWidget->horizontalHeader()->setDefaultSectionSize(113);
        pushButton_15 = new QPushButton(tab);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(140, 520, 161, 41));
        pushButton_15->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(370, 520, 161, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);\n"
""));
        pushButton_6 = new QPushButton(tab);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(580, 520, 211, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(570, 20, 421, 51));
        label->setStyleSheet(QString::fromUtf8("font: 700 italic 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(1150, 200, 351, 571));
        pushButton_14 = new QPushButton(groupBox);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(80, 40, 161, 41));
        pushButton_14->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_16 = new QPushButton(groupBox);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(80, 100, 161, 41));
        pushButton_16->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);\n"
""));
        linetel = new QLineEdit(groupBox);
        linetel->setObjectName("linetel");
        linetel->setGeometry(QRect(100, 370, 221, 41));
        linetel->setStyleSheet(QString::fromUtf8("\n"
"font: 11pt \"Segoe UI\";"));
        lineid = new QLineEdit(groupBox);
        lineid->setObjectName("lineid");
        lineid->setGeometry(QRect(100, 183, 221, 41));
        lineid->setStyleSheet(QString::fromUtf8("\n"
"font: 11pt \"Segoe UI\";"));
        non = new QLabel(groupBox);
        non->setObjectName("non");
        non->setGeometry(QRect(20, 173, 41, 51));
        non->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
""));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 430, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        linenom = new QLineEdit(groupBox);
        linenom->setObjectName("linenom");
        linenom->setGeometry(QRect(100, 243, 221, 41));
        linenom->setStyleSheet(QString::fromUtf8("\n"
"font: 11pt \"Segoe UI\";"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 330, 63, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 253, 63, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 390, 63, 20));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        lineprenon = new QLineEdit(groupBox);
        lineprenon->setObjectName("lineprenon");
        lineprenon->setGeometry(QRect(100, 313, 221, 41));
        lineprenon->setStyleSheet(QString::fromUtf8("\n"
"font: 11pt \"Segoe UI\";"));
        lineemail = new QLineEdit(groupBox);
        lineemail->setObjectName("lineemail");
        lineemail->setGeometry(QRect(100, 420, 221, 41));
        lineemail->setStyleSheet(QString::fromUtf8("\n"
"font: 11pt \"Segoe UI\";"));
        pushButton_17 = new QPushButton(groupBox);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(10, 520, 161, 41));
        pushButton_17->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_18 = new QPushButton(groupBox);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(180, 520, 161, 41));
        pushButton_18->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        GEmploye->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GEmploye);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1500, 36));
        GEmploye->setMenuBar(menubar);
        statusbar = new QStatusBar(GEmploye);
        statusbar->setObjectName("statusbar");
        GEmploye->setStatusBar(statusbar);

        retranslateUi(GEmploye);

        QMetaObject::connectSlotsByName(GEmploye);
    } // setupUi

    void retranslateUi(QMainWindow *GEmploye)
    {
        GEmploye->setWindowTitle(QCoreApplication::translate("GEmploye", "GEmploye", nullptr));
        menu->setTitle(QCoreApplication::translate("GEmploye", "menu", nullptr));
        pushButton->setText(QCoreApplication::translate("GEmploye", "employe", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GEmploye", "produit", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GEmploye", "client", nullptr));
        pushButton_5->setText(QCoreApplication::translate("GEmploye", "ordonnance", nullptr));
        pushButton_13->setText(QCoreApplication::translate("GEmploye", "fournisseur", nullptr));
        tab->setTitle(QCoreApplication::translate("GEmploye", "tableaux des employ\303\251s", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GEmploye", "ID_Emp", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GEmploye", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GEmploye", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GEmploye", "e-mail ", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GEmploye", "Num tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GEmploye", "Poste ", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GEmploye", "Login  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GEmploye", "MDP", nullptr));
        pushButton_15->setText(QCoreApplication::translate("GEmploye", "supprimer", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GEmploye", "statistique", nullptr));
        pushButton_6->setText(QCoreApplication::translate("GEmploye", "Exporter en pdf", nullptr));
        label->setText(QCoreApplication::translate("GEmploye", "Genstion des employ\303\251s", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GEmploye", "Gestion", nullptr));
        pushButton_14->setText(QCoreApplication::translate("GEmploye", "ajouter", nullptr));
        pushButton_16->setText(QCoreApplication::translate("GEmploye", "modifier", nullptr));
        linetel->setText(QString());
        linetel->setPlaceholderText(QCoreApplication::translate("GEmploye", "Saisir le numero de tel...", nullptr));
        lineid->setText(QString());
        lineid->setPlaceholderText(QCoreApplication::translate("GEmploye", "Saisir l'identifiant...", nullptr));
        non->setText(QCoreApplication::translate("GEmploye", "ID:", nullptr));
        label_6->setText(QCoreApplication::translate("GEmploye", "Email:", nullptr));
        linenom->setText(QString());
        linenom->setPlaceholderText(QCoreApplication::translate("GEmploye", "Saisir le nom...", nullptr));
        label_4->setText(QCoreApplication::translate("GEmploye", "Pr\303\251non:", nullptr));
        label_3->setText(QCoreApplication::translate("GEmploye", "Nom:", nullptr));
        label_5->setText(QCoreApplication::translate("GEmploye", "Tel:", nullptr));
        lineprenon->setText(QString());
        lineprenon->setPlaceholderText(QCoreApplication::translate("GEmploye", "Saisir le prenon...", nullptr));
        lineemail->setText(QString());
        lineemail->setPlaceholderText(QCoreApplication::translate("GEmploye", "Saisir le email...", nullptr));
        pushButton_17->setText(QCoreApplication::translate("GEmploye", "enregistrer", nullptr));
        pushButton_18->setText(QCoreApplication::translate("GEmploye", "annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GEmploye: public Ui_GEmploye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMPLOYE_H
