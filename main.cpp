#include "MainWindow.h"
#include "CAppDriver.h"
#include <QApplication>
#include "CAppManagement.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_IUdp = new UdpReceiver();
    g_ISerial = new ISerial();
    g_Cmain_win = new MainWindow();
    g_IUsbHid = new IUsbHid();
    
    g_ISerial->config();
    g_ISerial->open_serial();
    //g_IUsbHid->usb_init();
    g_IUsbHid->start();

    CWAdminLogin g_CWAdminlogin;
    g_CWAdminlogin.show();
<<<<<<< HEAD
=======
    g_IUsbHid->usb_init();
    g_IUsbHid->start();
>>>>>>> master
    return a.exec();
}
