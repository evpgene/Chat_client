#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_buttonBox_accepted()
{
    emit accepted();
}


void RegistrationForm::on_buttonBox_rejected()
{
    emit rejected();
}


void RegistrationForm::on_loginButton_clicked()
{
    emit loginFormRequested();
}

