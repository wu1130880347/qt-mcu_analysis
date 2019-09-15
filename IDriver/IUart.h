#ifndef IUART_H
#define IUART_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include "CConnectCenter.h"

class ISerial:public QObject
{
    Q_OBJECT
public:
    ISerial();
    virtual ~ISerial();

    virtual ConnectError_t config(void);
    void open_serial(void);
    void serial_write(QByteArray &dat);

public slots:
    void serial_read();

private:
    QSerialPort *m_serial;
};

#endif // IUART_H
