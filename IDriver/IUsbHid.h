#ifndef IUSBHID_H
#define IUSBHID_H
#include <QObject>
#include "CConnectCenter.h"
#include <QThread>
#include <QByteArray>
#include <QTimer> 

class IUsbHid:public QThread
{
    Q_OBJECT
protected:
    void run(); //多线程处理
public:
    IUsbHid();
    virtual ~IUsbHid();

    //virtual ConnectError_t config(void);
    void usbhid_read(void);
    void usbhid_write(QByteArray &dat);
    uint16_t usb_init(void);
public slots:
    void handleTimeout();  //超时处理函数  
private:
    uint8_t m_usb_rece_dat[64];//hid最多支持64Byte
    uint8_t m_usb_send_dat[64];
    QTimer *m_pTimer;  
};

#endif // IUSBHID_H
