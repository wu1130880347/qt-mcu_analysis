#include "CWTestToolsStatus.h"
#include "ui_CWTestToolsStatus.h"

CWTestToolsStatus::CWTestToolsStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTestToolsStatus)
{
    ui->setupUi(this);
}

CWTestToolsStatus::~CWTestToolsStatus()
{
    delete ui;
}
