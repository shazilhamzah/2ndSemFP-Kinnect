#ifndef USERNAMEERROR_H
#define USERNAMEERROR_H

#include <QDialog>

namespace Ui {
class UsernameError;
}

class UsernameError : public QDialog
{
    Q_OBJECT

public:
    explicit UsernameError(QWidget *parent = nullptr);
    ~UsernameError();
    void setErrorMessage(const QString& message1,const QString& message2);

private:
    Ui::UsernameError *ui;
};

#endif // USERNAMEERROR_H
