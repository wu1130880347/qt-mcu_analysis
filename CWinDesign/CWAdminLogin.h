#ifndef CWADMINLOGIN_H
#define CWADMINLOGIN_H

#include <QWidget>

namespace Ui {
class CWAdminLogin;
}

class CWAdminLogin : public QWidget
{
    Q_OBJECT

public:
    explicit CWAdminLogin(QWidget *parent = nullptr);
    ~CWAdminLogin();

private slots:
    void on_pushButton_admin_login_clicked();

    void on_pushButton_tools_config_clicked();

private:
    Ui::CWAdminLogin *ui;
};

#endif // CWADMINLOGIN_H
