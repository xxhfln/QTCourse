#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    emit goRegister();
}


void Login::on_pushButton_2_clicked()
{
    QString username = ui->username_line->text();
    QString password = ui->password_line->text();
    if (DataBase::getDataBase().userLogin(username,password) == "LoginSuccess"){
        emit LoginSuccess();
    }else {
        QMessageBox::information(this,"Login Failed","用户名或密码错误");
        return;
    }
}

