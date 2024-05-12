#include "usernameerror.h"
#include "ui_usernameerror.h"

UsernameError::UsernameError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UsernameError)
{
    ui->setupUi(this);
}

UsernameError::~UsernameError()
{
    delete ui;
}

void UsernameError::setErrorMessage(const QString& msgHead,const QString& msgPara){
    ui->labelheading->setText(msgHead);
    ui->labelpara->setText(msgPara);
}
