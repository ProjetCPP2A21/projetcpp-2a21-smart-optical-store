#ifndef OPTISMART_H
#define OPTISMART_H
#include <QSoundEffect>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include "ui_optismart.h"
#include "produit.h"
#include "fournisseur.h"
#include"ordonnance.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSerialPort>



QT_BEGIN_NAMESPACE
namespace Ui {
class optismart;
}
QT_END_NAMESPACE

class optismart : public QMainWindow
{
    Q_OBJECT

private slots:
    void onSerialDataReceived();
private:
    QSerialPort *serial;
public:
    optismart(QWidget *parent = nullptr);
    ~optismart();
    //ordonnance
private slots:
    void on_btnActualiser_clicked();
    void on_bajouter_o_clicked();
    void on_bsupprimer_o_clicked();
    void on_bmodifier_o_clicked();  // NOUVEAU SLOT
    void on_tableWidget_5_clicked(const QModelIndex &index);  // Pour sélectionner une ligne

private:
    Ordonnance ord;
    QString cinSelectionne;  // Pour stocker le CIN sélectionné
    void actualiserAffichageo();
    //fournisseur
private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();  // ⭐ NOUVEAU SLOT

private:
    fournisseur fourn;
    void actualiserAffichagef();
    void clearFields();

    //client
private slots:
    void on_bajouter_c_clicked();
private slots:
    void on_bsupprimer_c_clicked();
    /*void afficher_client();*/
    void afficher_client(int id_selectionne = -1);
private slots:
    void on_tableWidget_c_cellClicked(int row, int column);
    void on_bmodifier_c_clicked();
    // produit
private:
    void actualiserAffichagep();
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_modifierButton_clicked();
    void on_tableWidget_p_2_doubleClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_exportPdfButton_clicked();
    void on_statsButton_clicked();
    void on_trierButton_clicked();
private:
    Ui::optismart *ui;
    produit Ptmp;
    int selectedIdProduit;
};

#endif // OPTISMART_H
