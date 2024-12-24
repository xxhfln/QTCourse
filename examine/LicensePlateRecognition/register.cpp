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
    emit confirmRegister();
}

void Register::on_cancel_btn_clicked()
{
    emit cancel();
}

