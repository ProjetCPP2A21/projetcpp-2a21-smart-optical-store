#ifndef GEMPLOYE_H
#define GEMPLOYE_H

#include <QMainWindow>
#include <QGroupBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class GEmploye;
}
QT_END_NAMESPACE

class GEmploye : public QMainWindow
{
    Q_OBJECT

public:
    explicit GEmploye(QWidget *parent = nullptr);
    ~GEmploye();  // Declaration
private:
    Ui::GEmploye *ui;
    QGroupBox *groupBox;
};
// gemploye.h


#endif // GEMPLOYE2_H
