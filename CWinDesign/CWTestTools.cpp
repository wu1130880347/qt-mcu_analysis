#include "CWTestTools.h"
#include "ui_CWTestTools.h"
#include "CAppManagement.h"
//#include <synchapi.h>
#include <QDebug>
#include <QByteArray>

void CWTestTools::update_status(bool connect_fg)
{
    if(connect_fg == true)
    {
        m_test_connect = true;
        ui->label_show_tools_status->setText(QApplication::translate("CWTestTools", \
        "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ffAA00;\">设备已连接</span></p></body></html>", nullptr));
        if(g_CCTest_status != nullptr)
        {
            g_CCTest_status->show_tools_status(true);
        }
    }
    else
    {
        m_test_connect = false;
        ui->label_show_tools_status->setText(QApplication::translate("CWTestTools", \
        "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">设备不可用</span></p></body></html>", nullptr));
        if(g_CCTest_status != nullptr)
        {
            g_CCTest_status->show_tools_status(false);
        }
    }
}
CWTestTools::CWTestTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTestTools)
{
    ui->setupUi(this);
    //g_IUsbHid->usb_init_test_tool();//开启自动检测设备
    mp_lineedit_std[0] = ui->lineEdit_ic1_ch1_std;
    mp_lineedit_std[1] = ui->lineEdit_ic1_ch2_std;
    mp_lineedit_std[2] = ui->lineEdit_ic1_ch3_std;
    mp_lineedit_std[3] = ui->lineEdit_ic1_ch4_std;

    mp_lineedit_std[4] = ui->lineEdit_ic2_ch1_std;
    mp_lineedit_std[5] = ui->lineEdit_ic2_ch2_std;
    mp_lineedit_std[6] = ui->lineEdit_ic2_ch3_std;
    mp_lineedit_std[7] = ui->lineEdit_ic2_ch4_std;

    mp_lineedit_std[8] = ui->lineEdit_ic3_ch1_std;
    mp_lineedit_std[9] = ui->lineEdit_ic3_ch2_std;
    mp_lineedit_std[10] = ui->lineEdit_ic3_ch3_std;
    mp_lineedit_std[11] = ui->lineEdit_ic3_ch4_std;

    mp_lineedit_std[12] = ui->lineEdit_ic4_ch1_std;
    mp_lineedit_std[13] = ui->lineEdit_ic4_ch2_std;
    mp_lineedit_std[14] = ui->lineEdit_ic4_ch3_std;
    mp_lineedit_std[15] = ui->lineEdit_ic4_ch4_std;

    mp_lineedit_std[16] = ui->lineEdit_ic5_ch1_std;
    mp_lineedit_std[17] = ui->lineEdit_ic5_ch2_std;
    mp_lineedit_std[18] = ui->lineEdit_ic5_ch3_std;
    mp_lineedit_std[19] = ui->lineEdit_ic5_ch4_std;

    mp_lineedit_tol[0] = ui->lineEdit_ic1_ch1_tol;
    mp_lineedit_tol[1] = ui->lineEdit_ic1_ch2_tol;
    mp_lineedit_tol[2] = ui->lineEdit_ic1_ch3_tol;
    mp_lineedit_tol[3] = ui->lineEdit_ic1_ch4_tol;

    mp_lineedit_tol[4] = ui->lineEdit_ic2_ch1_tol;
    mp_lineedit_tol[5] = ui->lineEdit_ic2_ch2_tol;
    mp_lineedit_tol[6] = ui->lineEdit_ic2_ch3_tol;
    mp_lineedit_tol[7] = ui->lineEdit_ic2_ch4_tol;

    mp_lineedit_tol[8] = ui->lineEdit_ic3_ch1_tol;
    mp_lineedit_tol[9] = ui->lineEdit_ic3_ch2_tol;
    mp_lineedit_tol[10] = ui->lineEdit_ic3_ch3_tol;
    mp_lineedit_tol[11] = ui->lineEdit_ic3_ch4_tol;

    mp_lineedit_tol[12] = ui->lineEdit_ic4_ch1_tol;
    mp_lineedit_tol[13] = ui->lineEdit_ic4_ch2_tol;
    mp_lineedit_tol[14] = ui->lineEdit_ic4_ch3_tol;
    mp_lineedit_tol[15] = ui->lineEdit_ic4_ch4_tol;

    mp_lineedit_tol[16] = ui->lineEdit_ic5_ch1_tol;
    mp_lineedit_tol[17] = ui->lineEdit_ic5_ch2_tol;
    mp_lineedit_tol[18] = ui->lineEdit_ic5_ch3_tol;
    mp_lineedit_tol[19] = ui->lineEdit_ic5_ch4_tol;
}

CWTestTools::~CWTestTools()
{
    delete ui;
    if(g_CCTest_status != nullptr)
        g_CCTest_status->close();
}

void CWTestTools::on_pushButton__test_show_status_clicked()
{
    if(g_CCTest_status == nullptr)
        g_CCTest_status = new CWTestToolsStatus();

    g_CCTest_status->show();
    g_CCTest_status->show_tools_status(m_test_connect);
    m_show_status = 1;
}

void CWTestTools::on_pushButton_get_test_para_clicked()
{

}

void CWTestTools::on_pushButton_set_test_para_clicked()
{
    QString str;
    float buf = 0;
    for(uint8_t i = 0;i<20;i++)
    {
        str = mp_lineedit_std[i]->text();
        buf = str.toFloat();
        m_ch_std[i] = (uint32_t)(buf*1000);
        str = mp_lineedit_tol[i]->text();
        buf = str.toFloat();
        m_ch_tol[i] = (uint32_t)(buf*1000);
    }
    //usb写入下位机
    uint8_t usb_write_buf[50];
    uint8_t len = 50;
    *(uint32_t*)usb_write_buf = 0xaabbccdd;
    *(uint16_t*)(usb_write_buf+4) = 0;//00-10
    *(uint16_t*)(usb_write_buf+6) = 10;//00-10
    memcpy(usb_write_buf+8,(uint8_t*)mp_lineedit_std,40);
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    // Sleep(100);
    // *(uint32_t*)(usb_write_buf+4) = 0x00100020;//00-10
    // memcpy(usb_write_buf+8,(uint8_t*)(mp_lineedit_std+10),40);
    // memcpy(send_dat.data(),usb_write_buf,sizeof(usb_write_buf));
    // g_IUsbHid->usbhid_write(send_dat);
    // Sleep(100);

    // *(uint32_t*)usb_write_buf = 0xaabbccdd;
    // *(uint32_t*)(usb_write_buf+4) = 0x00200030;//00-10
    // memcpy(usb_write_buf+8,(uint8_t*)mp_lineedit_tol,40);
    // memcpy(send_dat.data(),usb_write_buf,sizeof(usb_write_buf));
    // g_IUsbHid->usbhid_write(send_dat);
    // Sleep(100);
    // *(uint32_t*)(usb_write_buf+4) = 0x00300040;//00-10
    // memcpy(usb_write_buf+8,(uint8_t*)(mp_lineedit_tol+10),40);
    // memcpy(send_dat.data(),usb_write_buf,sizeof(usb_write_buf));
    // g_IUsbHid->usbhid_write(send_dat);
    // Sleep(100);

}
