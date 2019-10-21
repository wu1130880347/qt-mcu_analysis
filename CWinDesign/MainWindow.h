#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void udp_rece_process(QByteArray &dat);
    void usb_log_process(QByteArray &dat);
    void usb_usb_rece_process(QByteArray &dat);
    void usb_usb_rece_process_show_va(uint32_t *dat,uint8_t len);
private slots:
    void on_pushButton_udp_start_clicked();
    void on_pushButton_udp_stop_clicked();
    void on_pushButton_udp_send_clicked();
    void on_pushButton_udp_send_clear_clicked();
    void on_pushButton_udp_rece_clear_clicked();
    void on_pushButton_usb_getdev_clicked();
    void on_pushButton_usb_open_clicked();
    void on_pushButton_usb_clear_clicked();
    void on_pushButton_usb_close_clicked();
    void on_pushButton_usb_send_clicked();
    
private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
};

#endif // MAINWINDOW_H
