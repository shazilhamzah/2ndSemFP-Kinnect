#ifndef PAGEVIEW_H
#define PAGEVIEW_H

#include <QDialog>
#include "myClasses.h"
#include "availableusers.h"
#include "pagepostslist.h"

namespace Ui {
class PageView;
}

class PageView : public QDialog
{
    Q_OBJECT

public:
    explicit PageView(QWidget *parent = nullptr,SocialNetworkApp* = nullptr);
    ~PageView();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::PageView *ui;
    SocialNetworkApp* app;
    PagePostsList* listPage;
};

#endif // PAGEVIEW_H
