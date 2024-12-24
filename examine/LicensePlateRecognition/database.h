#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include "common.h"

class DataBase
{
public:
    DataBase();
    ~DataBase();
    void initDataBase();
    QString userLogin(const QString& username, const QString& password);
    bool isUserNameExist(const QString& username);
    bool registerUser(const QString& username, const QString& password, const QString& phone);

    static DataBase& getDataBase(){
        static DataBase db_;
        return db_;
    }

    QSqlDatabase db;
};

#endif // DATABASE_H
