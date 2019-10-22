#ifndef IUSBHID_H
#define IUSBHID_H
#include <QObject>
#include "CConnectCenter.h"
#include <QThread>
#include <QByteArray>
#include <QTimer> 

#define TEST_USB_DEV_VID 0x0483
#define TEST_USB_DEV_PID 0x5750

class IUsbHid:public QThread
{
    Q_OBJECT
protected:
    void run(); //多线程处理
public:
    bool m_get_dev_fg;

    IUsbHid();
    virtual ~IUsbHid();

    //virtual ConnectError_t config(void);
    void usbhid_read(void);
    bool usbhid_write(QByteArray &dat);
    bool usbhid_write_byte(uint8_t *dat,uint8_t len);
    uint16_t usb_init(void);
    bool usb_get_pc_dev(void);
    bool usb_open_dev(uint16_t vid,uint16_t pid);
    bool usb_close_dev(void);
    bool usb_get_test_dev(uint16_t vid,uint16_t pid);
    void usb_init_test_tool(void);
signals:
    void sig_rece_usb_data();
public slots:
    void handleTimeout();  //超时处理函数
    void handle_test_tools();//检测下位机0x0483 0x5057
    void slot_rece_usb_data();
private:
    uint8_t m_usb_rece_dat[64];//hid最多支持数据包长
    uint8_t m_usb_send_dat[64];
    QTimer *m_pTimer;  
    QTimer *m_pTimer_tools;
};

#endif // IUSBHID_H
