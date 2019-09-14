#include "CWAdminLogin.h"
#include "ui_CWAdminLogin.h"
#include "CAppManagement.h"

CWAdminLogin::CWAdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWAdminLogin)
{
    ui->setupUi(this);
}

CWAdminLogin::~CWAdminLogin()
{
    delete ui;
}

void CWAdminLogin::on_pushButton_clicked()
{
    close();
    g_Cmain_win->show();
}
