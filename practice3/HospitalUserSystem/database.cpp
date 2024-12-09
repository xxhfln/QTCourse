#include "database.h"

DataBase::DataBase()
{
    initDataBase();
}

void DataBase::initDataBase()
{
    // 打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();
    // 添加数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库
    QString db_path = "F:/SQLServerDataBase/Lab4.db";
    db.setDatabaseName(db_path);
//    db.setDatabaseName("‪Lab4.db");
//    db.setUserName("xiexiaohui");
//    db.setPassword("123456");

    // 打开数据库
    if (!db.open()){
        qDebug() << "不能连接 connect to mysql error" << db.lastError().text();
        return;
    }else {
        qDebug() << "连接成功 connect to mysql OK";
    }
    // 设置模型
    //    model = new QSqlTableModel(this);
}

QString DataBase::userLogin(QString username, QString password)
{
    QSqlQuery query;
    qDebug()<<username <<" " << password;
    QString qs = QString("select * from User where USERNAME = '%1' and PASSWORD = '%2'").arg(username).arg(password);

    query.exec(qs);
    qDebug()<<query.size();

    if (query.next()){
        return "LoginSuccess";
    }else {
        return "LoginFail";
    }
}
