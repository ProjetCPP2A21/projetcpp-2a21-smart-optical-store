#ifndef GORDONNANCE_H
#define GORDONNANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gordonnance;
}
QT_END_NAMESPACE

class Gordonnance : public QMainWindow
{
    Q_OBJECT

public:
    Gordonnance(QWidget *parent = nullptr);
    ~Gordonnance();

private:
    Ui::Gordonnance *ui;
};
#endif // GORDONNANCE_H
