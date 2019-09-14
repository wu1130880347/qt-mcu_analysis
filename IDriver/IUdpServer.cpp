#include <QByteArray>
#include <QDebug>
#include "IUdpServer.h"
#include "CAppManagement.h"

UdpReceiver *g_IUdp = nullptr;
const quint16 PORT = 2333;

UdpReceiver::UdpReceiver(QObject *p) :
    QObject(p)
{
    uSocket = new QUdpSocket;
    uSocket->bind(QHostAddress("192.168.1.101"), PORT);
    connect(uSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

UdpReceiver::~UdpReceiver()
{
    delete uSocket;
}

void UdpReceiver::receive()
{
    QByteArray dat;
    while(uSocket->hasPendingDatagrams())
    {
        dat.resize((int)uSocket->pendingDatagramSize());
        uSocket->readDatagram(dat.data(), dat.size(),&des_ip,&des_port);
        qDebug()<<"addr_ip : "<<des_ip.toString()<<" port : "<<des_port;
        qDebug()<<"rece data : "<<dat.data();
        g_Cmain_win->udp_rece_process(dat);
    }
}
void UdpReceiver::udp_send(QByteArray &dat)
{
    uSocket->writeDatagram(dat,des_ip,des_port);
}
