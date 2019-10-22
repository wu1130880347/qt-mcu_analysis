#ifndef CWTESTTOOLS_H
#define CWTESTTOOLS_H

#include <QWidget>
#include "ui_CWTestTools.h"

namespace Ui {
class CWTestTools;
}

class CWTestTools : public QWidget
{
    Q_OBJECT

public:
    uint8_t m_show_status;//USB数据显示到面板上 1 显示 0不显示
    bool m_test_connect;
    uint32_t m_ch_std[20];//  mv/ma
    uint32_t m_ch_tol[20];//  mv/ma
    explicit CWTestTools(QWidget *parent = nullptr);
    void update_status(bool connect_fg);
    ~CWTestTools();

private slots:
    void on_pushButton__test_show_status_clicked();

    void on_pushButton_get_test_para_clicked();

    void on_pushButton_set_test_para_clicked();

private:
    Ui::CWTestTools *ui;
    QLineEdit *mp_lineedit_std[20];
    QLineEdit *mp_lineedit_tol[20];
};

#endif // CWTESTTOOLS_H
