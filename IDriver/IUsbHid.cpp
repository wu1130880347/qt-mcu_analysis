#include "IUsbHid.h"
#include "hidapi.h"
#include <QDebug>
#include <QSemaphore>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "CAppManagement.h"
#include <stdint.h>

IUsbHid *g_IUsbHid = nullptr;

static QMutex mutex_usb;
static QMutex mutex_send;
static QSemaphore rece_sem;
static hid_device *handle = nullptr;
static QByteArray m_rece_usb_data;
// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#if defined(QT_DEBUG)
static int Dprintf(const char *format, ...)
{
    static QByteArray usb_log;
    char buf[500];
    int i;
    va_list vlist;
    va_start(vlist, format);
    i = vsprintf(buf, format, vlist);
    va_end(vlist);
    //qDebug() << buf;
    usb_log.append(buf);
    g_Cmain_win->usb_log_process(usb_log);
    usb_log.clear();
    return i;
}
#else
static int Dprintf(const char *format, ...)
{
    char buf[500];
    int i;
    va_list vlist;
    va_start(vlist, format);
    i = vsprintf(buf, format, vlist);
    va_end(vlist);
    qDebug() << buf;
    return i;
}
#endif

void IUsbHid::run()
{
    int ret = 0;
    while (1)
    {
        rece_sem.acquire();
        if(handle != nullptr)
        {
            ret = hid_read(handle, m_usb_rece_dat, sizeof(m_usb_rece_dat));
            //qDebug()<<"Enter hid_read successful rece: "<<ret<<endl;
            if(ret > 0)
            {
                m_rece_usb_data.clear();
                m_rece_usb_data = QByteArray((char*)m_usb_rece_dat, ret);

                char *temp_buf = m_rece_usb_data.data();
                uint32_t get_dat_ch[16] = {0};
                memcpy((uint8_t *)get_dat_ch, (uint8_t *)temp_buf, 64);
                if (get_dat_ch[0] == 0xabceabce && get_dat_ch[1] != 4)
                {  
                    if(g_CCTest_tools != nullptr)
                        g_CCTest_tools->get_ret_status((uint8_t *)temp_buf, 64);
                }
                
                emit sig_rece_usb_data();//发出显示输出数据信号
            }
        }
        else
        {
            qDebug()<<"Enter hid_read fail\n";
        }
    }
}

void IUsbHid::slot_rece_usb_data()
{
    Dprintf("slot_rece_usb_data\n");
    char *temp_buf = m_rece_usb_data.data();
    uint32_t get_dat_ch[16] = {0};
    memcpy((uint8_t *)get_dat_ch,(uint8_t *)temp_buf,64);
    if(g_CCTest_tools != nullptr)
    {
        if(get_dat_ch[0] == 0xabcdabcd)
        {
            g_CCTest_tools->put_ret_status(true);
        }
        else if (get_dat_ch[0] == 0xabceabce)
        {
            g_CCTest_tools->get_ret_status((uint8_t *)temp_buf, 64);
        }
        else if(g_CCTest_tools->m_show_status == 1)
        {
            g_CCTest_status->show_test_value(get_dat_ch,16);
        }
        else
        {
            g_Cmain_win->usb_usb_rece_process_show_va(get_dat_ch,16);
        }
    }
    else
    {
        g_Cmain_win->usb_usb_rece_process_show_va(get_dat_ch,16);
    }
    //qDebug()<<get_dat_ch[0];
    //g_Cmain_win->usb_usb_rece_process(m_rece_usb_data);
}
void IUsbHid::handleTimeout()
{
    //qDebug()<<"Enter timeout processing function\n";  
    rece_sem.release();
    return ;
}
void IUsbHid::handle_test_tools()
{
    static uint8_t once_fg = 0;
    m_get_dev_fg = g_IUsbHid->usb_get_test_dev(TEST_USB_DEV_VID,TEST_USB_DEV_PID);
    if(m_get_dev_fg == true && once_fg == 0)
    {
        once_fg = 1;
        g_IUsbHid->usb_open_dev(TEST_USB_DEV_VID,TEST_USB_DEV_PID);
        g_CCTest_tools->update_status(m_get_dev_fg);
        qDebug()<<"open usb dev successful\n";
    }
    else if(m_get_dev_fg == false && once_fg == 1)
    {
        once_fg = 0;
        g_IUsbHid->usb_close_dev();
        g_CCTest_tools->update_status(m_get_dev_fg);
        qDebug()<<"close usb dev successful\n";
    }
}
void IUsbHid::usb_init_test_tool(void)
{
    m_pTimer_tools = new QTimer(this);
    connect(m_pTimer_tools, SIGNAL(timeout()), this, SLOT(handle_test_tools()));
    m_pTimer_tools->start(1000);
}
IUsbHid::IUsbHid()
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(this, SIGNAL(sig_rece_usb_data()), this, SLOT(slot_rece_usb_data()));
}
IUsbHid::~IUsbHid()
{
    delete m_pTimer;
    delete m_pTimer_tools;
}
void IUsbHid::usbhid_read(void)
{
}
bool IUsbHid::usbhid_write_byte(uint8_t *dat,uint8_t len)
{
    char buf[65] = {0};
    if(handle == nullptr)
        return false;
    memcpy(buf+1,dat,len);
    int res = hid_write(handle, (unsigned char*)buf, 64 + 1);
    if (res < 0)
    {
        Dprintf("Unable to write()\n");
        Dprintf("Error: %ls\n", hid_error(handle));
        return false;
    }
    Dprintf("usb wirte suc %d \n",res);
    rece_sem.release();//准备读
    return true;
}
bool IUsbHid::usbhid_write(QByteArray &dat)
{
    char buf[65] = {0};
    if(handle == nullptr)
        return false;
    char *temp_buf = dat.data();
    int len = dat.length();
    memcpy(buf+1,temp_buf,len);
    int res = hid_write(handle, (unsigned char*)buf, 64 + 1);
    if (res < 0)
    {
        Dprintf("Unable to write()\n");
        Dprintf("Error: %ls\n", hid_error(handle));
        return false;
    }
    Dprintf("usb wirte suc %d \n",res);
    rece_sem.release();//准备读
    return true;
}
//滤重
static uint8_t check_usb_dev(uint16_t (*dev)[2], uint16_t vid, uint16_t pid)
{
    uint8_t i = 0;
    uint8_t ret = 0;
    for (i = 0; i < 20; i++)
    {
        if (dev[i][0] == vid && dev[i][1] == pid)
        {
            ret = 1;
            break;
        }
        if (dev[i][0] == 0)
        {
            ret = 2;
            dev[i][0] = vid;
            dev[i][1] = pid;
            break;
        }
    }
    return (ret == 2) ? 0 : 1;
}

#define MAX_STR 255
bool IUsbHid::usb_open_dev(uint16_t vid,uint16_t pid)
{
    int res = 0;
    wchar_t wstr[MAX_STR];
    if(handle != nullptr)
        return false;
    handle = hid_open(vid, pid, nullptr);
    if (!handle)
    {
        Dprintf("unable to open 0x%04x pid: 0x%04x\n",vid,pid);
        return false;
    }
    Dprintf("open device vid：0x%04x pid: 0x%04x successful\n",vid,pid);

    // Read the Manufacturer String
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read manufacturer string\n");
    Dprintf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    wstr[0] = 0x0000;
    res = hid_get_product_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read product string\n");
    Dprintf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    wstr[0] = 0x0000;
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read serial number string\n");
    Dprintf("Serial Number String: (%d) %ls", wstr[0], wstr);
    Dprintf("\n");

    // Read Indexed String 1
    wstr[0] = 0x0000;
    res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read indexed string 1\n");
    Dprintf("Indexed String 1: %ls\n", wstr);

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);
    //开启接受线程
    g_IUsbHid->start();
    m_pTimer->start(100);
    return true;
}
bool IUsbHid::usb_get_pc_dev(void)
{
    struct hid_device_info *devs, *cur_dev;
    uint16_t usb_dev[20][2] = {0};
    if (hid_init())
        return false;
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        if (check_usb_dev(usb_dev, cur_dev->vendor_id, cur_dev->product_id))
        {
            cur_dev = cur_dev->next;
            continue;
        }

        Dprintf("Device Found\ntype: vid 0x%04hx pid 0x%04hx", cur_dev->vendor_id, cur_dev->product_id);
        Dprintf("Manufacturer: %ls", cur_dev->manufacturer_string);
        Dprintf("Product:      %ls", cur_dev->product_string);
        Dprintf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs); //释放内存
    cur_dev = nullptr;
    return true;
}
bool IUsbHid::usb_close_dev(void)
{
    if(handle == nullptr)
        return false;
    Dprintf("usb close successful\n");
    g_IUsbHid->quit();
    m_pTimer->stop();
    hid_close(handle);
    handle = nullptr;
    return true;
}
bool IUsbHid::usb_get_test_dev(uint16_t vid,uint16_t pid)
{
    struct hid_device_info *devs;
//    if (hid_init())
//        return false;
    devs = hid_enumerate(vid, pid);
    return (devs != nullptr)?true:false;
}
uint16_t IUsbHid::usb_init(void)
{
    int res;
    int i;
    unsigned char buf[MAX_STR];
    wchar_t wstr[MAX_STR];
    struct hid_device_info *devs, *cur_dev;
    uint16_t usb_dev[20][2] = {0};
    if (hid_init())
        return -1;
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        if(check_usb_dev(usb_dev,cur_dev->vendor_id,cur_dev->product_id))
        {
            cur_dev = cur_dev->next;
            continue;
        }

        Dprintf("Device Found\ntype: vid 0x%04hx pid 0x%04hx",cur_dev->vendor_id, cur_dev->product_id);
        Dprintf("Manufacturer: %ls", cur_dev->manufacturer_string);
        Dprintf("Product:      %ls", cur_dev->product_string);
        Dprintf("\n");
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);//释放内存
    cur_dev = nullptr;

    handle = hid_open(0x0483, 0x5750, NULL);
    if (!handle)
    {
        Dprintf("unable to open device\n");
        return 1;
    }

    // Read the Manufacturer String
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read manufacturer string\n");
    Dprintf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    wstr[0] = 0x0000;
    res = hid_get_product_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read product string\n");
    Dprintf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    wstr[0] = 0x0000;
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read serial number string\n");
    Dprintf("Serial Number String: (%d) %ls", wstr[0], wstr);
    Dprintf("\n");

    // Read Indexed String 1
    wstr[0] = 0x0000;
    res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
    if (res < 0)
        Dprintf("Unable to read indexed string 1\n");
    Dprintf("Indexed String 1: %ls\n", wstr);

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    // Try to read from the device. There shoud be no
    // data here, but execution should not block.
    res = hid_read(handle, buf, 64);
    buf[0] = 0x1;
    buf[1] = 0x80;
    for(uint8_t i = 0;i<64;i++)
        buf[i+1] = i;
    res = hid_write(handle, buf, 64 + 1);
    if (res < 0)
    {
        Dprintf("Unable to write()\n");
        Dprintf("Error: %ls\n", hid_error(handle));
    }
    res = 0;
    while (res == 0)
    {
        res = hid_read(handle, buf, 64+1);
        if (res == 0)
            Dprintf("waiting...\n");
        if (res < 0)
            Dprintf("Unable to read()\n");
#ifdef WIN32
        Sleep(500);
#else
        usleep(500 * 1000);
#endif
    }

    Dprintf("Data read:\n   ");
    // Print out the returned buffer.
    for (i = 0; i < res; i++)
        Dprintf("%02hhx ", buf[i]);
    Dprintf("\n");

    hid_close(handle);

    /* Free static HIDAPI objects. */
    hid_exit();
    return 0;
}
