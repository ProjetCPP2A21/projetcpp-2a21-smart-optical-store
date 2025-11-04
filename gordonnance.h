#ifndef GORDONNANCE_H
#define GORDONNANCE_H

#include <QMainWindow>
#include "ordonnance.h"

namespace Ui {
class Gordonnance;
}

class Gordonnance : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gordonnance(QWidget *parent = nullptr);
    ~Gordonnance();

private slots:
    void on_btnActualiser_clicked();
    void on_btnAjouter_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();  // NOUVEAU SLOT
    void on_tableWidget_clicked(const QModelIndex &index);  // Pour sélectionner une ligne

private:
    Ui::Gordonnance *ui;
    Ordonnance ord;
    QString cinSelectionne;  // Pour stocker le CIN sélectionné
    void actualiserAffichage();
};

#endif // GORDONNANCE_H
