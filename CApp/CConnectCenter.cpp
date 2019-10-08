#include "CConnectCenter.h"
#include <QDebug>
#include <QSemaphore>

static QMutex mutex_rece;
static QMutex mutex_send;
static QSemaphore rece_sem;
void CConnectCenter::run()
{
    while (1)
    {
        rece_sem.acquire();
        while (!m_frame_queue_rece.empty())
        {
            mutex_rece.lock();
            Q_FramePara_t &t_frame = m_frame_queue_rece.back();
            m_frame_queue_rece.pop_back();
            mutex_rece.unlock();
            Agreement(t_frame);
        }
    }
}

void CConnectCenter::Agreement(Q_FramePara_t &t_frame)
{
    uint16_t t_fun_code = uint16_t(t_frame.data.at(13) | t_frame.data.at(14) << 8);
    switch (t_fun_code)
    {
        //qDebug() << "t_fun_code = 0x" << hex << t_fun_code << endl;
    case 0x0501:
        //protocol_shake_hands(t_frame);
        break;
    default:
        break;
    }
    return;
}

ConnectError_t CConnectCenter::config(void)
{
    return m_CConnectCenter->config();
}
ConnectError_t CConnectCenter::connect_send(QByteArray &t_QByte)
{
    return m_CConnectCenter->connect_send(t_QByte);
}

//驱动获取数据包，封装后交给后台进程
ConnectError_t CConnectCenter::connect_rece(QByteArray &t_QByte)
{
    if (m_CConnectCenter->connect_rece(t_QByte) == CONNECT_OK)
    {
        Q_FramePara_t t_qframe = {t_QByte, m_CConnectCenter};
        mutex_rece.lock();
        m_frame_queue_rece.push_back(t_qframe);
        rece_sem.release();
        mutex_rece.unlock();
    }
    else
    {
        return CONNECT_FAIL;
    }
    return CONNECT_OK;
}

void CConnectCenter::connect_receALl(CConnectCenter *t_pthis)
{
    m_CConnectCenter = t_pthis;
    QByteArray t_QByte;
    connect_rece(t_QByte);
    qDebug() << "len = " << t_QByte.size() << endl;
    qDebug() << "server rece data : " << t_QByte.data() << endl;
}
