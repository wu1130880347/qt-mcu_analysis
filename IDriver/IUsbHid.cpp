#include "IUsbHid.h"
#include "hidapi.h"
#include <QDebug>
#include <QSemaphore>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

IUsbHid *g_IUsbHid = nullptr;

static QMutex mutex_usb;
static QMutex mutex_send;
static QSemaphore rece_sem;
static hid_device *handle = nullptr;

// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#if defined(QT_DEBUG)
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
    while (1)
    {
        rece_sem.acquire();
        if(handle != nullptr)
        {
            hid_read(handle, m_usb_rece_dat, sizeof(m_usb_rece_dat));
            qDebug()<<"Enter hid_read successful\n";
        }
        else
        {
            qDebug()<<"Enter hid_read fail\n";
        }
    }
}
void IUsbHid::handleTimeout()
{
    qDebug()<<"Enter timeout processing function\n";  
    rece_sem.release();
    return ;
}
IUsbHid::IUsbHid()
{
    m_pTimer = new QTimer(this);  
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));  
    m_pTimer->start(1000); 
}
IUsbHid::~IUsbHid()
{
}
void IUsbHid::usbhid_read(void)
{
}
void IUsbHid::usbhid_write(QByteArray &dat)
{
    dat.toInt();
}
uint16_t IUsbHid::usb_init(void)
{
    int res;
    unsigned char buf[256];
#define MAX_STR 255
    wchar_t wstr[MAX_STR];

    int i;

    struct hid_device_info *devs, *cur_dev;

    if (hid_init())
        return -1;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        Dprintf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        Dprintf("\n");
        Dprintf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        Dprintf("  Product:      %ls\n", cur_dev->product_string);
        Dprintf("  Release:      %hx\n", cur_dev->release_number);
        Dprintf("  Interface:    %d\n", cur_dev->interface_number);
        Dprintf("\n");
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    // Set up the command buffer.
    memset(buf, 0x00, sizeof(buf));
    buf[0] = 0x01;
    buf[1] = 0x81;

    // Open the device using the VID, PID,
    // and optionally the Serial number.
    ////handle = hid_open(0x4d8, 0x3f, L"12345");
    handle = hid_open(0x483, 0x5750, NULL);
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
    res = hid_read(handle, buf, 17);

    // Send a Feature Report to the device
    // buf[0] = 0x02;
    // buf[1] = 0xa0;
    // buf[2] = 0x0a;
    // buf[3] = 0x00;
    // buf[4] = 0x00;
    // res = hid_send_feature_report(handle, buf, 17);
    // if (res < 0)
    // {
    //     Dprintf("Unable to send a feature report.\n");
    // }

    // memset(buf, 0, sizeof(buf));

    // // Read a Feature Report from the device
    // buf[0] = 0x2;
    // res = hid_get_feature_report(handle, buf, sizeof(buf));
    // if (res < 0)
    // {
    //     Dprintf("Unable to get a feature report.\n");
    //     Dprintf("%ls", hid_error(handle));
    // }
    // else
    // {
    //     // Print out the returned buffer.
    //     Dprintf("Feature Report\n   ");
    //     for (i = 0; i < res; i++)
    //         Dprintf("%02hhx ", buf[i]);
    //     Dprintf("\n");
    // }

    // memset(buf, 0, sizeof(buf));

    // Toggle LED (cmd 0x80). The first byte is the report number (0x1).
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

    // Request state (cmd 0x81). The first byte is the report number (0x1).
    // buf[0] = 0x2;
    // buf[1] = 0x81;
    // buf[2] = 0xa5;
    // hid_write(handle, buf, 17);
    // if (res < 0)
    //     Dprintf("Unable to write() (2)\n");

    // Read requested state. hid_read() has been set to be
    // non-blocking by the call to hid_set_nonblocking() above.
    // This loop demonstrates the non-blocking nature of hid_read().
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
