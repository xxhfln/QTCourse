#include "expression.h"

Expression::Expression(){

}

Expression::~Expression(){

}

void Expression::init(){
    num_stack.clear();
    op_stack.clear();
    op_stack.push("#");
}

/*表达式求值算法描述：
（1）计算算术表达式的值时，可用两个堆栈作辅助工具。
（2）对于给出的一个字符串类型表达式，从左向右扫描它的字符进行单词（单词有三种：操作符、操作数、其他错误输入）的识别和分割，扫描到操作数时放入栈S1中，但每次扫描到运算符时，要把它同S2的栈顶运算符进行优先级比较并分三种情况如下：
当扫描到的运算符的优先级<=栈顶运算符的优先级时进行运算，即取出栈S1的栈顶和次栈顶的两个数据元素，以及栈S2的栈顶运算符进行运算并将结果放入栈S1中。
当扫描到的运算符的优先级>栈顶运算符的优先级时,把当前运算符放入栈S2。
当扫描到的运算符的优先级==栈顶运算符的优先级时（只有左右括号或#和#号会出现这种情况）,如果是括号，则匹配括号，即弹出S2栈顶符号，如果是#，则如果S1中只有一个元素，则算法结束，表达式正确，且计算结果在s1中，如果不是则报错。
（3）为方便比较，假设栈S2的初始栈顶为#（#运算符的优先级低于加、减、乘、除中任何一种运算）。。
*/
int Expression::splitExpression(QString exp){
    init();
    exp += "#"; // 在表达式末尾添加#，方便处理表达式
    QRegularExpression re("([0-9]+\\.[0-9]+|[0-9]+|[+\\-*/()#])");
    QRegularExpressionMatchIterator iter = re.globalMatch(exp);

    while(iter.hasNext()){
        QRegularExpressionMatch match = iter.next();
        QString matched = match.captured(0);
//        qDebug()<<"matched:"<<matched;
        if (matched.contains('.') || matched.contains('+')
            || matched.contains('-') || matched.contains('*')
            || matched.contains('/') || matched.contains('(')
            || matched.contains(')') || matched.contains('#')){
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
                }else { // 当找到操作符时，处理操作符
                    QString cur_op = QString(matched[i]);
                    int ret = handleOp(cur_op);
                    if (ret == -1) { // 计算出错或非法表达式
                        qDebug()<<"return -1";
                        return -1;
                    }
                }
            }
        }else{
            num_stack.push(matched.toDouble());
//            qDebug()<<"num_top:"<<num_stack.top();
        }
    }
//    qDebug()<<"Numbers:";
//    while(!num_stack.isEmpty()){
//        qDebug()<<num_stack.pop();
//    }
//    qDebug()<<"Operators:";
//    while(!op_stack.isEmpty()){
//        qDebug()<<op_stack.pop();
//    }
//    QMessageBox::critical(this,"Error","非法表达式!");
    return 0;
}

// 运算符优先表，用函数来表示，比较运算符 op1 和 op2的优先级
// op1>op2 返回1; < 返回-1 ; == 返回0; 其他非法情况返回-2
int Expression::compareOp(QString op1,QString op2){
    if (op1 == "+" || op1 == "-"){
        if (op2=="+"||op2=="-")return -1;
        if (op2=="*"||op2=="/")return -1;
        if (op2=="(")return 1;if (op2==")")return 1;
        if (op2=="#")return 1;
    }
    else if (op1 == "*" || op1 == "/"){
        if (op2=="+"||op2=="-")return 1;
        if (op2=="*"||op2=="/")return -1;
        if (op2=="(")return 1;if (op2==")")return 1;
        if (op2=="#")return 1;
    }
    else if (op1 == "("){
        if (op2=="+"||op2=="-")return 1;
        if (op2=="*"||op2=="/")return 1;
        if (op2=="(")return 1;if (op2==")")return 0;
        if (op2=="#")return 1;
    }
    else if (op1 == ")"){
        if (op2=="+"||op2=="-")return -1;
        if (op2=="*"||op2=="/")return -1;
        if (op2=="(")return 0;if (op2==")")return -2;
        if (op2=="#")return -2;
    }
    else if (op1 == "#"){
        if (op2=="+"||op2=="-")return -1;
        if (op2=="*"||op2=="/")return -1;
        if (op2=="(")return -1;if (op2==")"){QMessageBox::critical(this,"Error","非法表达式!");return -2;}
        if (op2=="#")return 0;
    }
    qDebug()<<"op1:"<<op1<<" op2:"<<op2;
    QMessageBox::critical(this,"Error","非法表达式!");return -2;
}

int Expression::handleOp(QString cur_op){
    while(1){
        QString top_op = op_stack.top();
        int ret = compareOp(cur_op,top_op);
        switch (ret) {
            case 1:{ // 当前操作符比栈顶操作符优先级高
                op_stack.push(cur_op);
                return 0;
            }
            case -1:{ // 当前操作符比栈顶操作符优先级低
                double num1,num2,result;
                QString ot;
                if (num_stack.size()<2 || op_stack.empty()){
                    qDebug()<<"1111";
                    QMessageBox::information(this,"Warning","计算报错，请检查表达式");
                    return -1;
                }
                qDebug()<<"num_stack_size:"<<num_stack.size();
                qDebug()<<"op_stack_size:"<<op_stack.size();
                ot = op_stack.pop();
                num2 = num_stack.pop();
                num1 = num_stack.pop();
                compute(num1,num2,ot,result);
                num_stack.push(result);
                break;
            }
            case 0:{ // 当前操作符与栈顶操作符优先级相等
                qDebug()<<"cur:"<<cur_op<<" top:"<<top_op;
                if (cur_op == ")" && top_op == "("){
                    op_stack.pop();
                    return 0;
                }
                else if (cur_op == "#" && top_op == "#" && op_stack.size() == 1){
//                    qDebug()<<"op_stack_size:"<<op_stack.size();
                    return 0;
                }
                else return -1;
            }
            case -2:{ // 非法表达式
                QMessageBox::critical(this,"Error","非法表达式");
                return -1;
            }
        }
    }
    return 0;
}

void Expression::compute(double num1,double num2,QString ot,double &result){
    if (ot == "+"){
        result = num1 + num2;
    }else if (ot == "-"){
        result = num1 - num2;
    }else if (ot == "*"){
        result = num1 * num2;
    }else if (ot == "/"){
        result = num1 / num2;
    }else{
        qDebug()<<"计算出错";
    }
}
