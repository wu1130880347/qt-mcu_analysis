#include "CWTestTools.h"
#include "ui_CWTestTools.h"
#include "CAppManagement.h"

CWTestTools::CWTestTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTestTools)
{
    ui->setupUi(this);
}

CWTestTools::~CWTestTools()
{
    delete ui;
}

void CWTestTools::on_pushButton__test_show_status_clicked()
{
    if(g_CCTest_status == nullptr)
        g_CCTest_status = new CWTestToolsStatus();
    g_CCTest_status->show();
}
