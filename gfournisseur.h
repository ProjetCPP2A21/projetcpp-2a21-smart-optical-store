#ifndef GFOURNISSEUR_H
#define GFOURNISSEUR_H

#include <QMainWindow>

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

private:
    Ui::gfournisseur *ui;
};
#endif // GFOURNISSEUR_H
