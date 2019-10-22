#ifndef CWTESTTOOLS_H
#define CWTESTTOOLS_H

#include <QWidget>
#include <QTimer> 

namespace Ui {
class CWTestTools;
}

class CWTestTools : public QWidget
{
    Q_OBJECT

public:
    explicit CWTestTools(QWidget *parent = nullptr);
    uint8_t m_show_status;//USB数据显示到面板上 1 显示 0不显示
    ~CWTestTools();

private slots:
    void on_pushButton__test_show_status_clicked();

private:
    Ui::CWTestTools *ui;
    QTimer *m_pTimer;  
};

#endif // CWTESTTOOLS_H
