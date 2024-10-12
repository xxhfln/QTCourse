#include "calculator.h"
#include "ui_calculator.h"

#include <QRegExpValidator>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    //只能输入数字
    ui->show_number->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

    setWindowIcon(QIcon(":/images/images/calculator.png"));

}

Calculator::~Calculator()
{
    delete ui;
}

