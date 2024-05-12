#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <QDialog>
#include "myClasses.h"

namespace Ui {
class MemoryView;
}

class MemoryView : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryView(QWidget *parent = nullptr,SocialNetworkApp*app=nullptr,User*owner=nullptr);
    ~MemoryView();

private:
    Ui::MemoryView *ui;
    SocialNetworkApp*app;
    User*owner;
};

#endif // MEMORYVIEW_H
