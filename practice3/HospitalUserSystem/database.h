#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

class DataBase
{
//    Q_OBJECT
public:
    DataBase();
    void initDataBase();
    QString userLogin(QString username, QString password);

    QSqlDatabase db;
//    QSqlTableModel *model;
};

#endif // DATABASE_H
