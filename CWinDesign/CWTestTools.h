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
    uint8_t m_show_status;//USB������ʾ������� 1 ��ʾ 0����ʾ
    ~CWTestTools();

private slots:
    void on_pushButton__test_show_status_clicked();

private:
    Ui::CWTestTools *ui;
    QTimer *m_pTimer;  
};

#endif // CWTESTTOOLS_H
