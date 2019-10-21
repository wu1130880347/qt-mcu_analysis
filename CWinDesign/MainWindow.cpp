#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CAppManagement.h"
#include <iostream>
#include <QDebug>
#include <QUdpSocket>
#include <QMessageBox>
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
void MainWindow::usb_log_process(QByteArray &dat)
{
    ui->textBrowser_usb_log->append(dat.data());
}
void MainWindow::usb_usb_rece_process_show_va(uint32_t *dat,uint8_t len)
{
    char buf[512] = {0};
    for(uint8_t i = 0;i<len;i++)
    {
        sprintf(buf,"ch = %d,value = %.2f\r\n",i,dat[i]*1.0/1000);
        ui->textBrowser_usb_rece->append(buf);
    }
}
void MainWindow::usb_usb_rece_process(QByteArray &dat)
{
    ui->textBrowser_usb_rece->append(dat.data());
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
void MainWindow::on_pushButton_usb_getdev_clicked()
{
    if (g_IUsbHid->usb_get_pc_dev() != true)
    {
        QMessageBox::question(NULL, "question", "usb init fail", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    cout<<"on_pushButton_usb_getdev_clicked"<<endl;
}

void MainWindow::on_pushButton_usb_open_clicked()
{
    int vid,pid;
    QString s_vid = ui->lineEdit_usb_vid->text();
    QString s_pid = ui->lineEdit_usb_pid->text();
    s_vid[1] = '0';
    s_pid[1] = '0';
    vid = s_vid.toInt(nullptr,16);
    pid = s_pid.toInt(nullptr,16);;

    if (g_IUsbHid->usb_open_dev((uint16_t)vid,(uint16_t)pid) != true)
    {
        QMessageBox::question(NULL, "question", "usb open fail");
    }
    else
    {
       ui->label_usb_connect->setText(QApplication::translate("MainWindow", "状态：连接成功", nullptr));
    }
    cout<<"on_pushButton_usb_open_clicked"<<endl;
}

void MainWindow::on_pushButton_usb_clear_clicked()
{
    ui->textBrowser_usb_log->clear();
    ui->textBrowser_usb_rece->clear();
    ui->textBrowser_usb_send->clear();
    cout<<"on_pushButton_usb_clear_clicked"<<endl;
}

void MainWindow::on_pushButton_usb_close_clicked()
{
    if (g_IUsbHid->usb_close_dev()==true)
        ui->label_usb_connect->setText(QApplication::translate("MainWindow", "状态：连接断开", nullptr));
    else
        QMessageBox::question(NULL, "question", "usb is close");
    cout<<"on_pushButton_usb_close_clicked"<<endl;
}

void MainWindow::on_pushButton_usb_send_clicked()
{
    QByteArray usb_send_str =  ui->textBrowser_usb_send->toPlainText().toUtf8();
    ui->textBrowser_usb_log->append(usb_send_str.data());
    if(usb_send_str.length() == 0)
    {
        QMessageBox::question(NULL, "question", "please input data!!!");
        return ;
    }
    if(g_IUsbHid->usbhid_write(usb_send_str) == false)
    {
        QMessageBox::question(NULL, "question", "usb is send fail");
    }
    cout<<"on_pushButton_usb_send_clicked"<<endl;
}

