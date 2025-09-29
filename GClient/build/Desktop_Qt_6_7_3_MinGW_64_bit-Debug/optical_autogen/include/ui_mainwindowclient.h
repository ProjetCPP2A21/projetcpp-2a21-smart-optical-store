/********************************************************************************
** Form generated from reading UI file 'mainwindowclient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWCLIENT_H
#define UI_MAINWINDOWCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *titgr;
    QGroupBox *groupBox1;
    QPushButton *bc;
    QPushButton *bp;
    QPushButton *bf;
    QPushButton *ba;
    QPushButton *bem;
    QGroupBox *groupBox2;
    QLabel *Titre2;
    QTableWidget *tabc;
    QPushButton *brecherche;
    QPushButton *bhistorique;
    QPushButton *bexporter;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *bsupprimer;
    QLabel *label_2;
    QGroupBox *groupBox;
    QPushButton *bajouter;
    QPushButton *bmodifier;
    QLabel *non;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineid;
    QLineEdit *linenom;
    QLineEdit *lineprenon;
    QLineEdit *linetel;
    QLineEdit *lineemail;
    QLineEdit *linepoints;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1500, 850);
        QFont font;
        font.setBold(true);
        font.setKerning(false);
        MainWindow->setFont(font);
        MainWindow->setMouseTracking(true);
        MainWindow->setTabletTracking(true);
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("back.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/back 1.png);"));
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(true);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        titgr = new QLabel(centralwidget);
        titgr->setObjectName("titgr");
        titgr->setGeometry(QRect(600, 40, 351, 51));
        titgr->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName("groupBox1");
        groupBox1->setGeometry(QRect(20, 170, 211, 571));
        groupBox1->setStyleSheet(QString::fromUtf8(""));
        bc = new QPushButton(groupBox1);
        bc->setObjectName("bc");
        bc->setGeometry(QRect(10, 120, 191, 101));
        bc->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bp = new QPushButton(groupBox1);
        bp->setObjectName("bp");
        bp->setGeometry(QRect(10, 230, 191, 101));
        bp->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"color: rgb(51, 51, 51);\n"
"font: 18pt \"Segoe UI\";"));
        bf = new QPushButton(groupBox1);
        bf->setObjectName("bf");
        bf->setGeometry(QRect(10, 340, 191, 101));
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
        groupBox2 = new QGroupBox(centralwidget);
        groupBox2->setObjectName("groupBox2");
        groupBox2->setGeometry(QRect(240, 160, 891, 571));
        Titre2 = new QLabel(groupBox2);
        Titre2->setObjectName("Titre2");
        Titre2->setGeometry(QRect(270, 150, 231, 41));
        Titre2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"text-decoration: underline;\n"
"font: 9pt \"Segoe UI\";\n"
"font: 16pt \"Segoe UI\";"));
        tabc = new QTableWidget(groupBox2);
        if (tabc->columnCount() < 6)
            tabc->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tabc->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tabc->rowCount() < 3)
            tabc->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tabc->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tabc->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tabc->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tabc->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tabc->setItem(0, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tabc->setItem(0, 3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tabc->setItem(0, 4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tabc->setItem(0, 5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tabc->setItem(1, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tabc->setItem(1, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tabc->setItem(1, 3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tabc->setItem(1, 4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tabc->setItem(1, 5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tabc->setItem(2, 3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tabc->setItem(2, 4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tabc->setItem(2, 5, __qtablewidgetitem21);
        tabc->setObjectName("tabc");
        tabc->setGeometry(QRect(10, 220, 871, 192));
        tabc->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 220);\n"
"font: 10pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        brecherche = new QPushButton(groupBox2);
        brecherche->setObjectName("brecherche");
        brecherche->setGeometry(QRect(580, 30, 161, 41));
        brecherche->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        bhistorique = new QPushButton(groupBox2);
        bhistorique->setObjectName("bhistorique");
        bhistorique->setGeometry(QRect(350, 470, 161, 41));
        bhistorique->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        bexporter = new QPushButton(groupBox2);
        bexporter->setObjectName("bexporter");
        bexporter->setGeometry(QRect(610, 470, 231, 41));
        bexporter->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        lineEdit = new QLineEdit(groupBox2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(310, 30, 211, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";\n"
""));
        label = new QLabel(groupBox2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 251, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 16pt \"Segoe UI\";"));
        pushButton = new QPushButton(groupBox2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(179, 100, 151, 29));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));
        pushButton_2 = new QPushButton(groupBox2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(450, 100, 151, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));
        bsupprimer = new QPushButton(groupBox2);
        bsupprimer->setObjectName("bsupprimer");
        bsupprimer->setGeometry(QRect(40, 470, 161, 41));
        bsupprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 10, 150, 150));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/logo1.png);"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(1140, 150, 351, 581));
        bajouter = new QPushButton(groupBox);
        bajouter->setObjectName("bajouter");
        bajouter->setGeometry(QRect(90, 20, 161, 41));
        bajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        bmodifier = new QPushButton(groupBox);
        bmodifier->setObjectName("bmodifier");
        bmodifier->setGeometry(QRect(90, 70, 161, 41));
        bmodifier->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        non = new QLabel(groupBox);
        non->setObjectName("non");
        non->setGeometry(QRect(20, 140, 41, 51));
        non->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 220, 63, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 280, 63, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 340, 63, 20));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 390, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 440, 63, 20));
        label_7->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        lineid = new QLineEdit(groupBox);
        lineid->setObjectName("lineid");
        lineid->setGeometry(QRect(100, 150, 221, 41));
        lineid->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        linenom = new QLineEdit(groupBox);
        linenom->setObjectName("linenom");
        linenom->setGeometry(QRect(100, 210, 221, 41));
        linenom->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        lineprenon = new QLineEdit(groupBox);
        lineprenon->setObjectName("lineprenon");
        lineprenon->setGeometry(QRect(100, 280, 221, 41));
        lineprenon->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        linetel = new QLineEdit(groupBox);
        linetel->setObjectName("linetel");
        linetel->setGeometry(QRect(100, 337, 221, 31));
        linetel->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        lineemail = new QLineEdit(groupBox);
        lineemail->setObjectName("lineemail");
        lineemail->setGeometry(QRect(100, 387, 221, 31));
        lineemail->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        linepoints = new QLineEdit(groupBox);
        linepoints->setObjectName("linepoints");
        linepoints->setGeometry(QRect(100, 427, 221, 41));
        linepoints->setStyleSheet(QString::fromUtf8("color: rgb(102, 102, 102);\n"
"font: 11pt \"Segoe UI\";"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 510, 161, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(180, 510, 161, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 213, 186);\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(51, 51, 51);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1500, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        titgr->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        titgr->setText(QCoreApplication::translate("MainWindow", "GESTIOIN DE CLIENTS", nullptr));
        groupBox1->setTitle(QString());
        bc->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\274Clients", nullptr));
        bp->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246Produits", nullptr));
        bf->setText(QCoreApplication::translate("MainWindow", "\360\237\232\232Fournisseur", nullptr));
        ba->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204Ordonnance", nullptr));
        bem->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244Employee", nullptr));
        groupBox2->setTitle(QString());
        Titre2->setText(QCoreApplication::translate("MainWindow", "LISTE DES CLIENTS ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabc->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabc->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Points", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabc->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tabc->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Prenon", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tabc->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tabc->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tabc->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tabc->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tabc->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Nouvelle ligne", nullptr));

        const bool __sortingEnabled = tabc->isSortingEnabled();
        tabc->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tabc->item(0, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "01", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tabc->item(0, 2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "ali", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tabc->item(0, 3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "mahjoub", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tabc->item(0, 4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "+216-----", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tabc->item(0, 5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "alimahjoub@gmail.com", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tabc->item(1, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "02", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tabc->item(1, 2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tabc->item(1, 3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tabc->item(1, 4);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tabc->item(1, 5);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "----", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tabc->item(2, 3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tabc->item(2, 4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tabc->item(2, 5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        tabc->setSortingEnabled(__sortingEnabled);

        brecherche->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215Recherche", nullptr));
        bhistorique->setText(QCoreApplication::translate("MainWindow", "\360\237\223\234 Historique", nullptr));
        bexporter->setText(QCoreApplication::translate("MainWindow", "\342\254\207 Exporter en pdf", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "recherche...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Recherche un CLIENT", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Tirer par Nom", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Tirer par points", nullptr));
        bsupprimer->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221Supprimer", nullptr));
        label_2->setText(QString());
        groupBox->setTitle(QString());
        bajouter->setText(QCoreApplication::translate("MainWindow", "\342\236\225Ajouter", nullptr));
        bmodifier->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217Modifier", nullptr));
        non->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Pr\303\251non:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Tel:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Points:", nullptr));
        lineid->setText(QCoreApplication::translate("MainWindow", "Saisir l'identifiant...", nullptr));
        linenom->setText(QCoreApplication::translate("MainWindow", "Saisir le nom...", nullptr));
        lineprenon->setText(QCoreApplication::translate("MainWindow", "Saisir le prenon...", nullptr));
        linetel->setText(QCoreApplication::translate("MainWindow", "Saisir le numero de tel...", nullptr));
        lineemail->setText(QCoreApplication::translate("MainWindow", "Saisir le email...", nullptr));
        linepoints->setText(QCoreApplication::translate("MainWindow", "Saisir Points de fid\303\251lit\303\251....", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276Enregistrer", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\342\234\226Annuler ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWCLIENT_H
