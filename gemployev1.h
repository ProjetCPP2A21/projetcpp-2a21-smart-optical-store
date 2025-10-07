#ifndef GEMPLOYEV1_H
#define GEMPLOYEV1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gemploye;
}
QT_END_NAMESPACE

class Gemploye : public QMainWindow
{
    Q_OBJECT

public:
    Gemploye(QWidget *parent = nullptr);
    ~Gemploye();

private:
    Ui::Gemploye *ui;
};
#endif // GEMPLOYEV1_H
