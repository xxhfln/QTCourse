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

class Expression
{
public:
    Expression();
    ~Expression();
    void init();
    void splitExpression(QString exp);

    QStack<double> num_stack; // 操作数栈
    QStack<QString>op_stack;  // 运算符栈
};

#endif // EXPRESSION_H
