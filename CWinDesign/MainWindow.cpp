#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CAppManagement.h"
#include <iostream>
#include <QDebug>
#include <QUdpSocket>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::udp_rece_process(QByteArray &dat)
{
    ui->textEdit_rece->append(dat.data());
    return;
}
void MainWindow::on_pushButton_udp_start_clicked()
{
    cout<<"on_pushButton_udp_start_clicked"<<endl;
}

void MainWindow::on_pushButton_udp_stop_clicked()
{
     cout<<"on_pushButton_udp_stop_clicked"<<endl;
}

void MainWindow::on_pushButton_udp_send_clicked()
{
     cout<<"on_pushButton_udp_send_clicked"<<endl;
     QByteArray temp_dat = ui->textEdit_send->toPlainText().toLocal8Bit();
     g_IUdp->udp_send(temp_dat);
}

void MainWindow::on_pushButton_udp_send_clear_clicked()
{
     cout<<"on_pushButton_udp_send_clear_clicked"<<endl;
}

void MainWindow::on_pushButton_udp_rece_clear_clicked()
{
     cout<<"on_pushButton_udp_rece_clear_clicked"<<endl;
}

