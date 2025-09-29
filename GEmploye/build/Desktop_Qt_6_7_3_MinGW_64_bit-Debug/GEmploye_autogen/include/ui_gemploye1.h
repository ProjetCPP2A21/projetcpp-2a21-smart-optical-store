/********************************************************************************
** Form generated from reading UI file 'gemploye1.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEMPLOYE1_H
#define UI_GEMPLOYE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GEmploye
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QCheckBox *checkBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QFrame *frame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GEmploye)
    {
        if (GEmploye->objectName().isEmpty())
            GEmploye->setObjectName("GEmploye");
        GEmploye->resize(743, 661);
        QFont font;
        font.setPointSize(14);
        GEmploye->setFont(font);
        centralwidget = new QWidget(GEmploye);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 170, 141, 31));
        label->setFont(font);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(270, 270, 261, 28));
        QFont font1;
        font1.setPointSize(10);
        lineEdit_2->setFont(font1);
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 270, 151, 31));
        label_2->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 420, 148, 41));
        QFont font2;
        font2.setWeight(QFont::Medium);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: #4CAF50;\n"
"        border: none;\n"
"        color: white;\n"
"        padding: 12px 24px;\n"
"        border-radius: 8px;\n"
"        font-weight: 500;\n"
"        font-size: 11px;\n"
"        min-width: 100px;\n"
""));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(270, 170, 261, 28));
        lineEdit->setFont(font1);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 40, 481, 51));
        label_3->setStyleSheet(QString::fromUtf8("font: 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(280, 340, 231, 25));
        checkBox->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(390, 420, 148, 41));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(90, 90, 90);\n"
"        border: none;\n"
"        color: white;\n"
"        padding: 12px 24px;\n"
"        border-radius: 8px;\n"
"        font-weight: 500;\n"
"        font-size: 11px;\n"
"        min-width: 100px;\n"
""));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(430, 540, 271, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 20, 120, 80));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        GEmploye->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GEmploye);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 743, 36));
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
        label->setText(QCoreApplication::translate("GEmploye", "Identifiant :", nullptr));
        label_2->setText(QCoreApplication::translate("GEmploye", "Mot de passe :", nullptr));
        pushButton->setText(QCoreApplication::translate("GEmploye", "Valider", nullptr));
        label_3->setText(QCoreApplication::translate("GEmploye", "Connexion Employ\303\251e", nullptr));
        checkBox->setText(QCoreApplication::translate("GEmploye", "Se souvenir de moi ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GEmploye", "annuler", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GEmploye", "mot de passe oubli\303\251 ? ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GEmploye: public Ui_GEmploye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMPLOYE1_H
