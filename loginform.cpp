#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}


void LoginForm::on_buttonBox_accepted()
{
    emit accepted();
}


void LoginForm::on_buttonBox_rejected()
{
    emit rejected();
}


void LoginForm::on_RegistrationPushButton_clicked()
{
    emit registrationFormRequested();
}

