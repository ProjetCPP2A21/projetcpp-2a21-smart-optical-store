#include "gfournisseur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gfournisseur w;
    w.show();
    return a.exec();
}
