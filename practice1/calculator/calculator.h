#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>

#include "expression.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    void init();

    QPushButton *bt_num[10];  // 存放 0-9 十个按键

public slots:
    void bt_input_clicked();  // 按键输入捕获

private slots:
    void on_clear_bt_clicked();

    void on_cut_bt_clicked();

    void on_cal_bt_clicked();

private:
    Ui::Calculator *ui;
    Expression *exp;
};
#endif // CALCULATOR_H
