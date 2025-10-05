/********************************************************************************
** Form generated from reading UI file 'gfournisseur.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GFOURNISSEUR_H
#define UI_GFOURNISSEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gfournisseur
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gfournisseur)
    {
        if (gfournisseur->objectName().isEmpty())
            gfournisseur->setObjectName("gfournisseur");
        gfournisseur->resize(1500, 850);
        centralwidget = new QWidget(gfournisseur);
        centralwidget->setObjectName("centralwidget");
        gfournisseur->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gfournisseur);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1500, 21));
        gfournisseur->setMenuBar(menubar);
        statusbar = new QStatusBar(gfournisseur);
        statusbar->setObjectName("statusbar");
        gfournisseur->setStatusBar(statusbar);

        retranslateUi(gfournisseur);

        QMetaObject::connectSlotsByName(gfournisseur);
    } // setupUi

    void retranslateUi(QMainWindow *gfournisseur)
    {
        gfournisseur->setWindowTitle(QCoreApplication::translate("gfournisseur", "gfournisseur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gfournisseur: public Ui_gfournisseur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GFOURNISSEUR_H
