#include "CWTestTools.h"
#include "ui_CWTestTools.h"
#include "CAppManagement.h"
#include <synchapi.h>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>

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
            //QMessageBox::question(NULL, "question", "please input data!!!");
        }
    }
}
CWTestTools::CWTestTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTestTools)
{
    ui->setupUi(this);
    g_IUsbHid->usb_init_test_tool();//开启自动检测
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
    //usb读入下位机
    uint8_t usb_write_buf[10] = {0};
    uint8_t len = 10;
    *(uint32_t*)usb_write_buf = 0xaabbccee;
    *(uint32_t*)(usb_write_buf+4) = 1;//00-10
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
    *(uint32_t*)usb_write_buf = 0xaabbccee;
    *(uint32_t*)(usb_write_buf+4) = 2;//00-10
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
    *(uint32_t*)usb_write_buf = 0xaabbccee;
    *(uint32_t*)(usb_write_buf+4) = 3;//00-10
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
    *(uint32_t*)usb_write_buf = 0xaabbccee;
    *(uint32_t*)(usb_write_buf+4) = 4;//00-10
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
}
void CWTestTools::get_ret_status(uint8_t * dat,uint8_t len)
{
    static uint8_t get_fg = 0;
    if(*(uint32_t*)(dat+4) == 1)
    {
        get_fg = 0;
        memcpy((uint8_t *)m_ch_std,dat+8,40);
    }
    else if(*(uint32_t*)(dat+4) == 2)
    {
        get_fg++;
        memcpy((uint8_t *)(m_ch_std+10),dat+8,40);
    }
    else if(*(uint32_t*)(dat+4) == 3)
    {
        get_fg++;
        memcpy((uint8_t *)m_ch_tol,dat+8,40);
    }
    else if(*(uint32_t*)(dat+4) == 4)
    {
        if(get_fg == 2)
        {
            memcpy((uint8_t *)(m_ch_tol+10),dat+8,40);
            get_fg = 0;
            char temp_buf[20];
            QPalette palette_blue;
            QPalette palette_red;
            palette_blue.setColor(QPalette::Text,Qt::blue);
            palette_red.setColor(QPalette::Text,Qt::red);
            for (int i = 0; i < 20; i++)
            {
                mp_lineedit_std[i]->clear();
                sprintf(temp_buf, "%.2f", m_ch_std[i] * 1.0 / 1000);
                mp_lineedit_std[i]->setText(temp_buf);
                mp_lineedit_std[i]->setPalette(palette_blue);

                mp_lineedit_tol[i]->clear();
                sprintf(temp_buf, "%.2f", m_ch_tol[i] * 1.0 / 1000);
                mp_lineedit_tol[i]->setText(temp_buf);
                mp_lineedit_tol[i]->setPalette(palette_red);
            }
            QMessageBox::question(NULL, "question", "参数获取成功");
        }
    }
    
}
void CWTestTools::put_ret_status(bool ret_status)
{
    if(ret_status == true)
    {
        m_send_dat_count++;
    }
    if(m_send_dat_count == m_send_suc_count)
    {
        m_send_suc_count = 0;
        m_send_dat_count = 0;
        QMessageBox::question(NULL, "question", "参数设置成功");
    }
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
    uint8_t usb_write_buf[50] = {0};
    uint8_t len = 50;
    m_send_suc_count = 4;
    m_send_dat_count = 0;
    *(uint32_t*)usb_write_buf = 0xaabbccdd;
    *(uint16_t*)(usb_write_buf+4) = 0;//00-10
    *(uint16_t*)(usb_write_buf+6) = 10;//00-10
    memcpy(usb_write_buf+8,(uint8_t*)m_ch_std,40);
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
    *(uint16_t*)(usb_write_buf+4) = 10;//00-10
    *(uint16_t*)(usb_write_buf+6) = 20;//00-10
    memcpy(usb_write_buf+8,(uint8_t*)(m_ch_std+10),40);
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);

    *(uint16_t*)(usb_write_buf+4) = 20;//00-10
    *(uint16_t*)(usb_write_buf+6) = 30;//00-10
    memcpy(usb_write_buf+8,(uint8_t*)m_ch_tol,40);
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);

    *(uint16_t*)(usb_write_buf+4) = 30;//00-10
    *(uint16_t*)(usb_write_buf+6) = 40;//00-10
    memcpy(usb_write_buf+8,(uint8_t*)(m_ch_tol+10),40);
     g_IUsbHid->usbhid_write_byte(usb_write_buf,len);
    Sleep(500);
}
