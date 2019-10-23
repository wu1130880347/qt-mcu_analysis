#include "CWTestToolsStatus.h"
#include "ui_CWTestToolsStatus.h"
#include "CAppManagement.h"

CWTestToolsStatus::CWTestToolsStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTestToolsStatus)
{
    ui->setupUi(this);
    mp_lineedit[0] = ui->lineEdit_ch_1;
    mp_lineedit[1] = ui->lineEdit_ch_2;
    mp_lineedit[2] = ui->lineEdit_ch_3;
    mp_lineedit[3] = ui->lineEdit_ch_4;
    mp_lineedit[4] = ui->lineEdit_ch_5;
    mp_lineedit[5] = ui->lineEdit_ch_6;
    mp_lineedit[6] = ui->lineEdit_ch_7;
    mp_lineedit[7] = ui->lineEdit_ch_8;
    mp_lineedit[8] = ui->lineEdit_ch_9;
    mp_lineedit[9] = ui->lineEdit_ch_10;
    mp_lineedit[10] = ui->lineEdit_ch_11;
    mp_lineedit[11] = ui->lineEdit_ch_12;
    mp_lineedit[12] = ui->lineEdit_ch_13;
    mp_lineedit[13] = ui->lineEdit_ch_14;
    mp_lineedit[14] = ui->lineEdit_ch_15;
    mp_lineedit[15] = ui->lineEdit_ch_16;
    mp_lineedit[16] = ui->lineEdit_ch_17;
    mp_lineedit[17] = ui->lineEdit_ch_18;
    mp_lineedit[18] = ui->lineEdit_ch_19;
    mp_lineedit[19] = ui->lineEdit_ch_20;

    mp_label[0] = ui->label_ch_1;
    mp_label[1] = ui->label_ch_2;
    mp_label[2] = ui->label_ch_3;
    mp_label[3] = ui->label_ch_4;
    mp_label[4] = ui->label_ch_5;
    mp_label[5] = ui->label_ch_6;
    mp_label[6] = ui->label_ch_7;
    mp_label[7] = ui->label_ch_8;
    mp_label[8] = ui->label_ch_9;
    mp_label[9] = ui->label_ch_10;
    mp_label[10] = ui->label_ch_11;
    mp_label[11] = ui->label_ch_12;
    mp_label[12] = ui->label_ch_13;
    mp_label[13] = ui->label_ch_14;
    mp_label[14] = ui->label_ch_15;
    mp_label[15] = ui->label_ch_16;
    mp_label[16] = ui->label_ch_17;
    mp_label[17] = ui->label_ch_18;
    mp_label[18] = ui->label_ch_19;
    mp_label[19] = ui->label_ch_20;

}

CWTestToolsStatus::~CWTestToolsStatus()
{
    g_CCTest_tools->m_show_status = 0;
    delete ui;
}

void CWTestToolsStatus::show_test_value(uint32_t *dat, uint8_t len)
{
    char buf[20];
    uint8_t led_status[10];
    uint8_t *tp_buf = (uint8_t*)dat;
    for(uint8_t i = 0;i<4;i++)  //获取灯状态
    {
        led_status[i] = tp_buf[15+16*i];
        tp_buf[15+16*i] = 0;
    }
    QPalette palette_yellow;
    QPalette palette_blue;
    palette_yellow.setColor(QPalette::Text,Qt::magenta);
    palette_blue.setColor(QPalette::Text,Qt::blue);
    for(int i = 0;i<len;i++)
    {
        mp_lineedit[i]->clear();
        sprintf(buf,"%.2f",dat[i]*1.0/1000);
        mp_lineedit[i]->setText(buf);
        mp_lineedit[i]->setPalette((i%4 == 2)?palette_yellow:palette_blue);
    }
    for(int i = 0;i<len;i++)
    {
        if (i % 4 == 3)
        {
            mp_label[i]->setText(QApplication::translate("CWTestToolsStatus", \
            "<html><head/><body><p><span style=\" font-weight:600; color:#FFAA00;\">类型</span></p></body></html>", nullptr));
            continue;
        }
        if(i % 4 == 2)
        {
            if (!(led_status[i / 4] & (0x04 << (((i % 4) * 2) + 1))))
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">电流</span></p></body></html>", nullptr));
            }
            else if (!(led_status[i / 4] & (0x04 << ((i % 4) * 2))))
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#39ad00;\">电流</span></p></body></html>", nullptr));
            }
            else
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#FFAA00;\">不用</span></p></body></html>", nullptr));
            }
        }
        else
        {
            if (!(led_status[i / 4] & (0x04 << (((i % 4) * 2) + 1))))
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">电压</span></p></body></html>", nullptr));
            }
            else if (!(led_status[i / 4] & (0x04 << ((i % 4) * 2))))
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#39ad00;\">电压</span></p></body></html>", nullptr));
            }
            else
            {
                mp_label[i]->setText(QApplication::translate("CWTestToolsStatus",
                                                             "<html><head/><body><p><span style=\" font-weight:600; color:#FFAA00;\">不用</span></p></body></html>", nullptr));
            }
        }
    }
}

void CWTestToolsStatus::show_tools_status(bool status)
{
    if(status == true)
    {
        ui->label_show_tools_status->setText(QApplication::translate("CWTestTools", \
        "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ffAA00;\">设备已连接</span></p></body></html>", nullptr));
    }
    else
    {
        ui->label_show_tools_status->setText(QApplication::translate("CWTestTools", \
        "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">设备不可用</span></p></body></html>", nullptr));
    }
}
