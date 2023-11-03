#include "mainwindow.h"
#include "startscreen.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::createClient()
{
    StartScreen s;
    s.exec();
    return nullptr;
}


void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendPushButton_clicked();
}


void MainWindow::on_sendPushButton_clicked()
{

}


void MainWindow::on_actionOpen_another_client_triggered()
{
    createClient();
}


void MainWindow::on_actionClose_client_triggered()
{

}

