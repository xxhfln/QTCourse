#include "calculator.h"
#include "ui_calculator.h"

#include <QRegExpValidator>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    // 初始化
    init();

    // 设置正则表达式，限制编辑框内只能显示 0-9 +-*/.()这些符号
    ui->show_number->setValidator(new QRegExpValidator(QRegExp("^[0-9+\\-*/().]+$")));
    // 设置窗口图标
    setWindowIcon(QIcon(":/images/images/calculator.png"));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::init(){
    bt_num[0] = ui->num0_bt;
    bt_num[1] = ui->num1_bt;
    bt_num[2] = ui->num2_bt;
    bt_num[3] = ui->num3_bt;
    bt_num[4] = ui->num4_bt;
    bt_num[5] = ui->num5_bt;
    bt_num[6] = ui->num6_bt;
    bt_num[7] = ui->num7_bt;
    bt_num[8] = ui->num8_bt;
    bt_num[9] = ui->num9_bt;

    for (int i = 0;i < 10;i++){
        connect(bt_num[i],SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    }
    connect(ui->point_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->add_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->sub_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->mul_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->div_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->left_parenthesis_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
    connect(ui->right_parenthesis_bt,SIGNAL(clicked(bool)),this,SLOT(bt_input_clicked()));
}

void Calculator::bt_input_clicked(){
    // 提取按键
    QPushButton *btx = static_cast<QPushButton*>(sender());
    // 提取文字
    QString c = btx->text();
    // 追加显示在编辑框
    QString data = ui->show_number->text();
    if (data == "0" && c != "." && data != "0."){
        ui->show_number->setText(c);
    }else{
        data = data + c;
        ui->show_number->setText(data);
    }

}

void Calculator::on_clear_bt_clicked(){
    ui->show_number->setText("0");
}


void Calculator::on_cut_bt_clicked()
{
    QString data = ui->show_number->text();
    data.chop(1);
    ui->show_number->setText(data);
}


void Calculator::on_cal_bt_clicked()
{

}

