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

private slots:
    void on_pushButton_udp_start_clicked();

    void on_pushButton_udp_stop_clicked();

    void on_pushButton_udp_send_clicked();

    void on_pushButton_udp_send_clear_clicked();

    void on_pushButton_udp_rece_clear_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
};

#endif // MAINWINDOW_H
