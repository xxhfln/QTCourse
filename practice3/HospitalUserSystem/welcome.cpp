#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::on_pushButton_clicked()
{
    emit goDepartment();
}


void Welcome::on_pushButton_2_clicked()
{
    emit goDoctor();
}


void Welcome::on_pushButton_3_clicked()
{
    emit goPatient();
}

