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
}

CWTestToolsStatus::~CWTestToolsStatus()
{
    g_CCTest_tools->m_show_status = 0;
    delete ui;
}

void CWTestToolsStatus::show_test_value(uint32_t *dat, uint8_t len)
{
    char buf[20];
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
