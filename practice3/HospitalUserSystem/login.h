#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "common.h"
#include "database.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccess();

private slots:
    void on_btn_login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
