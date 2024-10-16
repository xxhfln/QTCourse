#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();

//    Expression *exp = new Expression();
//    exp->splitExpression(QString("((1.1+2.2)*3/(23+8.9)-5"));

    return a.exec();
}
