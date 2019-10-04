#ifndef CAPPDRIVER_H
#define CAPPDRIVER_H
#include <QSerialPort>
#include "IUdpServer.h"
#include "IUart.h"
#include "IUsbHid.h"
extern ISerial *g_ISerial;
extern UdpReceiver *g_IUdp;
extern IUsbHid *g_IUsbHid;
#endif // CAPPDRIVER_H
