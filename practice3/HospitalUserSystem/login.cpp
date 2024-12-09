#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString ret = DataBase::getInstance().userLogin(username,password);
    if (ret == "LoginSuccess"){
        qDebug()<<"登录成功";
        emit loginSuccess();
    }else if (ret == "LoginFail"){
        qDebug()<<"登录失败";
        QMessageBox::information(this,"登录失败","用户名或密码错误");
    }

}

