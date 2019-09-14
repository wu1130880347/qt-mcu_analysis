#ifndef IUDPSERVER_H
#define IUDPSERVER_H
#include <QObject>
#include <QUdpSocket>
#include "IUart.h"


class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    UdpReceiver(QObject *p = 0);
    ~UdpReceiver();
    void udp_send(QByteArray &dat);

public slots:
    void receive();

private:
    QUdpSocket *uSocket;
    QHostAddress des_ip;//目标IP
    quint16 des_port;//目标端口号
    QSerialPort *m_serial;

};
#endif // IUDPSERVER_H
