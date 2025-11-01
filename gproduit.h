#ifndef GPRODUIT_H
#define GPRODUIT_H

#include <QMainWindow>
#include "produit.h" //


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

private slots:
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_modifierButton_clicked();
    void on_tableWidget_p_2_doubleClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_exportPdfButton_clicked();
    void on_statsButton_clicked();
    void on_trierButton_clicked();    // ← ICI

private:
    Ui::gproduit *ui;
    produit Ptmp;
    int selectedIdProduit;

};

#endif // GPRODUIT_H
