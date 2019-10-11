#include "MainWindow.h"
#include "CAppDriver.h"
#include <QApplication>
#include "CAppManagement.h"

void app_init(void)
{
    g_IUdp = new UdpReceiver();
    g_ISerial = new ISerial();
    g_IUsbHid = new IUsbHid();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWAdminLogin g_CWAdminlogin;
    g_CWAdminlogin.show();

    app_init();
    return a.exec();
}
