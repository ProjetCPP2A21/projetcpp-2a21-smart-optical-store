#ifndef MAINWINDOWCLIENT_H
#define MAINWINDOWCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowclient;
}
QT_END_NAMESPACE

class MainWindowclient : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowclient(QWidget *parent = nullptr);
    ~MainWindowclient();

private:
    Ui::MainWindowclient *ui;
};
#endif // MAINWINDOWCLIENT_H
