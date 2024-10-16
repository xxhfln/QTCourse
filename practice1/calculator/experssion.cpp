#include "expression.h"

Expression::Expression(){

}

Expression::~Expression(){

}

void Expression::init(){
    op_stack.push("#");
}

void Expression::splitExpression(QString exp){
    QRegularExpression re("([0-9]+\\.[0-9]+|[0-9]+|[+\\-*/()])");
    QRegularExpressionMatchIterator iter = re.globalMatch(exp);

    while(iter.hasNext()){
        QRegularExpressionMatch match = iter.next();
        QString matched = match.captured(0);

        if (matched.contains('.') || matched.contains('+')
            || matched.contains('-') || matched.contains('*')
            || matched.contains('/') || matched.contains('(')
            || matched.contains(')')){
            for (int i = 0;i < matched.length();++i){
                if (matched[i].isDigit() || matched[i] == '.'){
                    QString numberStr;
                    while(i < matched.length()
                           && (matched[i].isDigit() || matched[i] == '.')){
                        numberStr += matched[i];
                        ++i;
                    }
                    num_stack.push(numberStr.toDouble());
                    --i;
                }else {
                    op_stack.push(QString(matched[i]));
                }
            }
        }else{
            num_stack.push(matched.toDouble());
        }
    }
    qDebug()<<"Numbers:";
    while(!num_stack.isEmpty()){
        qDebug()<<num_stack.pop();
    }
    qDebug()<<"Operators:";
    while(!op_stack.isEmpty()){
        qDebug()<<op_stack.pop();
    }
}
