#ifndef CWTESTTOOLSSTATUS_H
#define CWTESTTOOLSSTATUS_H

#include <QWidget>
#include "ui_CWTestToolsStatus.h"
namespace Ui {
class CWTestToolsStatus;
}

class CWTestToolsStatus : public QWidget
{
    Q_OBJECT

public:
    explicit CWTestToolsStatus(QWidget *parent = nullptr);
    ~CWTestToolsStatus();
    void show_test_value(uint32_t *dat,uint8_t len);
private:
    Ui::CWTestToolsStatus *ui;
    QLineEdit *mp_lineedit[20];
};

#endif // CWTESTTOOLSSTATUS_H
