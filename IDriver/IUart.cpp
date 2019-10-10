#include "IUart.h"
#include "CAppManagement.h"
#include <QByteArray>
#include <QDebug>

ISerial *g_ISerial = nullptr;

ISerial::ISerial()
{
    m_serial = nullptr;
}
ISerial::~ISerial()
{

}
ConnectError_t ISerial::config(void)
{
    m_serial = new QSerialPort;
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
            QSerialPort serial;
            m_serial->setPort(info);
            if(m_serial->open(QIODevice::ReadWrite))
            {
                m_serial->close();
                qDebug()<<"find serial : "<<m_serial->portName();
                return CONNECT_OK;
            }
    }
    qDebug()<<"no find COMx"<<endl;
    return CONNECT_OK;
}

void ISerial::open_serial(void)
{
    m_serial->open(QIODevice::ReadWrite);
    m_serial->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
    m_serial->setDataBits(QSerialPort::Data8);//设置数据
    m_serial->setParity(QSerialPort::NoParity); //校验位
    m_serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控
    connect(m_serial,SIGNAL(readyRead()),this,SLOT(serial_read()));
}

void ISerial::serial_read()
{
    QByteArray buf;
    buf = m_serial->readAll();
    if (!buf.isEmpty())
    {
        qDebug()<<buf<<endl;
        g_Cmain_win->udp_rece_process(buf);
    }
    buf.clear();
}

void ISerial::serial_write(QByteArray &dat)
{
    m_serial->write(dat);
}

