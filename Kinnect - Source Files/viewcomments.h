#ifndef VIEWCOMMENTS_H
#define VIEWCOMMENTS_H

#include <QDialog>
#include "myClasses.h"

namespace Ui {
class ViewComments;
}

class ViewComments : public QDialog
{
    Q_OBJECT

public:
    explicit ViewComments(QWidget *parent = nullptr,Post* post = nullptr);
    ~ViewComments();

private:
    Ui::ViewComments *ui;
};

#endif // VIEWCOMMENTS_H
