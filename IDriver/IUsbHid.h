#ifndef IUSBHID_H
#define IUSBHID_H
#include <QObject>
#include "CConnectCenter.h"
#include <QThread>

class IUsbHid:public QThread
{
    Q_OBJECT
public:
    IUsbHid();
    virtual ~IUsbHid();

    //virtual ConnectError_t config(void);
    void usbhid_read(void);
    void usbhid_write(QByteArray &dat);
    uint16_t usb_test(void);
public slots:

private:

};

#endif // IUSBHID_H
