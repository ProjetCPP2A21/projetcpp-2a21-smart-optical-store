/********************************************************************************
** Form generated from reading UI file 'gemploye2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEMPLOYE2_H
#define UI_GEMPLOYE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_GEmploye
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GEmploye)
    {
        if (GEmploye->objectName().isEmpty())
            GEmploye->setObjectName("GEmploye");
        GEmploye->resize(1105, 600);
        centralwidget = new QWidget(GEmploye);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 161, 511));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 50, 90, 29));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 130, 90, 29));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 200, 90, 29));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(40, 360, 90, 29));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(40, 270, 90, 29));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(40, 450, 90, 29));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(190, 120, 871, 411));
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(30, 60, 811, 331));
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(430, 30, 301, 51));
        label->setStyleSheet(QString::fromUtf8("font: 700 italic 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        GEmploye->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GEmploye);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1105, 25));
        GEmploye->setMenuBar(menubar);
        statusbar = new QStatusBar(GEmploye);
        statusbar->setObjectName("statusbar");
        GEmploye->setStatusBar(statusbar);

        retranslateUi(GEmploye);

        QMetaObject::connectSlotsByName(GEmploye);
    } // setupUi

    void retranslateUi(QMainWindow *GEmploye)
    {
        GEmploye->setWindowTitle(QCoreApplication::translate("GEmploye", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GEmploye", "GroupBox", nullptr));
        pushButton->setText(QCoreApplication::translate("GEmploye", "employe", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GEmploye", "produit", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GEmploye", "client", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GEmploye", "statistique", nullptr));
        pushButton_5->setText(QCoreApplication::translate("GEmploye", "assurance", nullptr));
        pushButton_6->setText(QCoreApplication::translate("GEmploye", "quitter", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GEmploye", "GroupBox", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GEmploye", "ID_Employ\303\251 ", nullptr));
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
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GEmploye", "Mot de passe", nullptr));
        label->setText(QCoreApplication::translate("GEmploye", "Genstion des employ\303\251s", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GEmploye: public Ui_GEmploye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMPLOYE2_H
