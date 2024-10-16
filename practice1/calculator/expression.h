#ifndef EXPRESSION_H
#define EXPRESSION_H
// C++ system
//#include <iostream>
//#include <stack>

// QT include
#include <QMainWindow>
#include <QString>
#include <QRegularExpression>
#include <QStack>
#include <QDebug>
#include <QMessageBox>


class Expression : public QMainWindow
{
public:
    Expression();
    ~Expression();
    void init();
    int splitExpression(QString exp);
    int compareOp(QString op1,QString op2);
    int handleOp(QString cur_op);
    void compute(double num1,double num2,QString ot,double &result);

    QStack<double> num_stack; // 操作数栈
    QStack<QString>op_stack;  // 运算符栈
};

#endif // EXPRESSION_H
