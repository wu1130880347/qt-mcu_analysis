#include "CWAdminLogin.h"
#include "ui_CWAdminLogin.h"
#include "CAppManagement.h"

CWAdminLogin::CWAdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWAdminLogin)
{
    ui->setupUi(this);
    if(g_Cmain_win == nullptr)
    g_Cmain_win = new MainWindow();
}

CWAdminLogin::~CWAdminLogin()
{
    delete ui;
}

void CWAdminLogin::on_pushButton_admin_login_clicked()
{
    //close();
    g_ISerial->config();
    g_ISerial->open_serial();
    g_Cmain_win->show();
}

void CWAdminLogin::on_pushButton_tools_config_clicked()
{
    close();
    if(g_CCTest_tools == nullptr)
        g_CCTest_tools = new CWTestTools();
    g_CCTest_tools->show();
}
