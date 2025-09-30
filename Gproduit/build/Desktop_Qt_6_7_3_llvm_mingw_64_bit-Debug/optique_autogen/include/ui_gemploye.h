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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gemploye
{
public:

    void setupUi(QWidget *gemploye)
    {
        if (gemploye->objectName().isEmpty())
            gemploye->setObjectName("gemploye");
        gemploye->resize(400, 300);

        retranslateUi(gemploye);

        QMetaObject::connectSlotsByName(gemploye);
    } // setupUi

    void retranslateUi(QWidget *gemploye)
    {
        gemploye->setWindowTitle(QCoreApplication::translate("gemploye", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gemploye: public Ui_gemploye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMPLOYE_H
