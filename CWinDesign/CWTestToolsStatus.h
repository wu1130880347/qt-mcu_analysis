#ifndef CWTESTTOOLSSTATUS_H
#define CWTESTTOOLSSTATUS_H

#include <QWidget>

namespace Ui {
class CWTestToolsStatus;
}

class CWTestToolsStatus : public QWidget
{
    Q_OBJECT

public:
    explicit CWTestToolsStatus(QWidget *parent = nullptr);
    ~CWTestToolsStatus();

private:
    Ui::CWTestToolsStatus *ui;
};

#endif // CWTESTTOOLSSTATUS_H
