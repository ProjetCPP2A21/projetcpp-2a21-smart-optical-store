#ifndef GPRODUIT_H
#define GPRODUIT_H

#include <QMainWindow>

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

private:
    Ui::gproduit *ui;
};
#endif // GPRODUIT_H
