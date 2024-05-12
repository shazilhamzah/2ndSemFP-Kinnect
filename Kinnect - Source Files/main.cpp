#include "mainwindow.h"
#include"myClasses.h"
#include <QApplication>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SocialNetworkApp app;
    app.getTotalUsers();
    app.addUsers();
    app.setDateObject();
    MainWindow w(nullptr,&app);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#131B26"));
    w.setPalette(palette);
    w.show();
    return a.exec();
}
