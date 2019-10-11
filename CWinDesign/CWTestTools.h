#ifndef CWTESTTOOLS_H
#define CWTESTTOOLS_H

#include <QWidget>

namespace Ui {
class CWTestTools;
}

class CWTestTools : public QWidget
{
    Q_OBJECT

public:
    explicit CWTestTools(QWidget *parent = nullptr);
    ~CWTestTools();

private slots:
    void on_pushButton__test_show_status_clicked();

private:
    Ui::CWTestTools *ui;
};

#endif // CWTESTTOOLS_H
