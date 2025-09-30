#include "gproduit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gproduit w;
    w.show();
    return a.exec();
}
