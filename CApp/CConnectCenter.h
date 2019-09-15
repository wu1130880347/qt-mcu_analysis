#ifndef CCONNECTCENTER_H
#define CCONNECTCENTER_H
#include <QByteArray>
#include <QMutex>
#include <QQueue>
#include <QThread>
#include <stdint.h>

#define QBYTEARRAY_SEND_MAX 512
#define QBYTEARRAY_RECE_MAX 512
#define MS_FRAME_NUMS_MAX 1024 //最多1024帧

//帧格式==>>  帧头  设备类型  上下行标志  随机数  数据长度   数据  校验CRC  (byte)
//             4      4        1       2       2      len    8
class CConnectCenter;
typedef enum
{
    CONNECT_OK = 0,
    CONNECT_FAIL,
    CONNECT_TIMEROUT,
    CONNECT_UNKNOWN,
} ConnectError_t;

typedef struct
{
    QByteArray data;      //保存数据
    CConnectCenter *idrv; //接收来自于
} Q_FramePara_t;

class CConnectCenter : public QThread
{
public:
    CConnectCenter() = default;
    explicit CConnectCenter(CConnectCenter *t_CConCenter);
    void protocol_shake_hands(Q_FramePara_t &t_frame);    //握手协议-提供界面更新显示
    void protocol_transfer_other(Q_FramePara_t &t_frame); //转发兼容其他协议
    void Agreement(Q_FramePara_t &t_frame);
    void connect_receALl(CConnectCenter *t_pthis);

protected:
    void run(); //多线程处理

    virtual ~CConnectCenter();
    virtual ConnectError_t config(void);                      //配置底层驱动
    virtual ConnectError_t connect_send(QByteArray &t_QByte); //底层驱动实现
    virtual ConnectError_t connect_rece(QByteArray &t_QByte); //底层驱动实现
private:
    static uint32_t ms_CConnectCenter_nums; //记录底层驱动数量
    uint32_t *ms_frame_nums;                //记录缓存帧数量
    CConnectCenter *m_CConnectCenter;
    QByteArray *m_byte_array_send;            //连接发送数据
    QByteArray *m_byte_array_rece;            //连接接受到数据
    QQueue<Q_FramePara_t> m_frame_queue_send; //接收队列
    QQueue<Q_FramePara_t> m_frame_queue_rece; //发送队列
};
#endif // CCONNECTCENTER_H
