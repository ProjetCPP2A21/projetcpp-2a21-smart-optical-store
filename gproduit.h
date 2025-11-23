#ifndef GPRODUIT_H
#define GPRODUIT_H

#include <QMainWindow>
#include "produit.h" //
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class gproduit;
}
QT_END_NAMESPACE

class gproduit : public QMainWindow
{
    Q_OBJECT

public:
    gproduit(QWidget *parent = nullptr);
    ~gproduit();
       void refreshTable();


private slots:
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_modifierButton_clicked();
    void on_tableWidget_p_2_doubleClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_exportPdfButton_clicked();
    void on_statsButton_clicked();
    void on_trierButton_clicked();

    void on_genererQrButton_clicked();

    void jouerAlerteVocale(int idProduit, const QString &nomProduit, int quantite);
    void envoyerSMS(const QString &numeroDestinataire, const QString &message);



    // gproduit.h
private:
    Ui::gproduit *ui;
    produit Ptmp;                    // D'ABORD Ptmp
    int selectedIdProduit = -1;


};


#endif // GPRODUIT_H
