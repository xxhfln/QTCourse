#include "database.h"

DataBase::DataBase()
{
    initDataBase();
}

DataBase::~DataBase()
{

}

void DataBase::initDataBase()
{
    // 添加数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库
    QString db_path = "../LicensePlateRecognition/database/LicensePlateRecognitionDB.db";
    db.setDatabaseName(db_path);

    // 打开数据库
    if (!db.open()){
        qDebug() << "不能连接 Failed to connect to database" << db.lastError().text();
        return;
    }else {
        qDebug() << "连接成功 connect to database successfully";
    }
}

QString DataBase::userLogin(const QString& username, const QString& password)
{
    QSqlQuery query;
    QString qs = QString("select * from User where UserName = '%1' and Password = '%2'").arg(username).arg(password);;
    query.exec(qs);
    if (query.next()){
        return "LoginSuccess";
    }else {
        return "LoginFail";
    }
}

bool DataBase::isUserNameExist(const QString &username)
{
    QSqlQuery query;
    query.prepare("select count(*) from User where UserName = :username");
    query.bindValue(":username", username);
    if (!query.exec()){
        QMessageBox::critical(nullptr,"Database Error",query.lastError().text());
        return false;
    }
    query.next();
    return query.value(0).toInt() > 0; // 如果计数大于0，则用户名已存在
}

bool DataBase::registerUser(const QString &username, const QString &password, const QString &phone)
{
    QSqlQuery query;
    query.prepare("insert into User (UserName,Password,Phone) values (:username,:password,:phone)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":phone",phone);
    if (!query.exec()){
        QMessageBox::critical(nullptr,"Database Error",query.lastError().text());
        return false;
    }
    return true;
}
