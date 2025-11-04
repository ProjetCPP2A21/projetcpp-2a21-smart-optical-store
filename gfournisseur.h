#ifndef GFOURNISSEUR_H
#define GFOURNISSEUR_H

#include <QMainWindow>
#include "fournisseur.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class gfournisseur;
}
QT_END_NAMESPACE

class gfournisseur : public QMainWindow
{
    Q_OBJECT

public:
    gfournisseur(QWidget *parent = nullptr);
    ~gfournisseur();

private slots:
    void on_bajouter_f_clicked();
    void on_bsupprimer_f_clicked();
    void on_bmodifier_f_clicked();  // ⭐ NOUVEAU SLOT

private:
    Ui::gfournisseur *ui;
    fournisseur fourn;
    void actualiserAffichage();
    void clearFields();
};
#endif // GFOURNISSEUR_H
