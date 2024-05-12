#ifndef PAGEPOSTSLIST_H
#define PAGEPOSTSLIST_H

#include <QDialog>
#include "myClasses.h"
#include "postview.h"

namespace Ui {
class PagePostsList;
}

class PagePostsList : public QDialog
{
    Q_OBJECT

public:
    explicit PagePostsList(QWidget *parent = nullptr,Page*page=nullptr,SocialNetworkApp*app=nullptr);

    ~PagePostsList();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::PagePostsList *ui;
    SocialNetworkApp*app;
    PostView* postView;
};

#endif // PAGEPOSTSLIST_H
