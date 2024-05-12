#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginpage.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,SocialNetworkApp *app = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::MainWindow *ui;
    LoginPage* login;
    SocialNetworkApp*app;
};
#endif // MAINWINDOW_H
