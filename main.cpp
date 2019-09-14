#include "MainWindow.h"
#include "CAppDriver.h"
#include <QApplication>
#include "CAppManagement.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    g_IUdp = new UdpReceiver();
    g_ISerial = new ISerial();
    g_Cmain_win = new MainWindow();
    g_ISerial->config();
    g_ISerial->open_serial();
    CWAdminLogin g_CWAdminlogin;
    g_CWAdminlogin.show();

    return a.exec();
}

//#include <QByteArray>
//#include <QCoreApplication>
//#include <QHostAddress>
//#include <QUdpSocket>
//#include <iostream>
//using namespace std;
//const quint16 PORT = 2333;

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    QUdpSocket qus;
//  qus.bind(QHostAddress("127.0.0.1"), PORT+1);
//    QByteArray msg = "Hello world!";
//    cout << "--- Sender ---" << std::endl;
//    for(int i=0; i<100; ++i)
//        qus.writeDatagram(msg, QHostAddress("192.168.1.101"), PORT);

//    return a.exec();
//}
