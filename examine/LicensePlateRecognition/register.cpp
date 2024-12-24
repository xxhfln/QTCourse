#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_register_btn_clicked()
{
    QString username = ui->username_line->text();
    QString password = ui->password_line->text();
    QString confirm_password = ui->confirmPassword_line->text();
    QString phone = ui->phone_line->text();

    if (username.isEmpty() || phone.isEmpty()){
        QMessageBox::information(this,"Input Error","用户名或手机号不可为空");
        return;
    }
    if (password.isEmpty() || confirm_password.isEmpty()){
        QMessageBox::information(this,"Input Error","密码不可为空");
        return;
    }else if (password.length() < 6){
        QMessageBox::information(this,"Input Error","密码不可少于6位");
        return;
    }else if (password != confirm_password){
        QMessageBox::information(this,"Input Error","两次输入密码不相同");
        return;
    }

    if (DataBase::getDataBase().isUserNameExist(username)){
        QMessageBox::warning(this,"UserName Exists","用户名已存在");
        return;
    }

    if (DataBase::getDataBase().registerUser(username,password,phone)){
        QMessageBox::information(this,"Registration Successful","注册成功");
        emit confirmRegister();
    } else {
        QMessageBox::critical(this, "Registration Failed", "An error occurred during registration.");
    }
}

void Register::on_cancel_btn_clicked()
{
    emit cancel();
}

