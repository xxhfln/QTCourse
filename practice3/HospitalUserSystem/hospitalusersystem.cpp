#include "hospitalusersystem.h"
#include "ui_hospitalusersystem.h"

HospitalUserSystem::HospitalUserSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HospitalUserSystem)
{
    ui->setupUi(this);
    // 打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();
    // 添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库
    db.setDatabaseName("‪F:\SQLServerDataBase\Lab4.db");
    db.setUserName("xiexiaohui");
    db.setPassword("123456");

    // 打开数据库
    if (!db.open()){
        qDebug() << "不能连接 connect to mysql error" << db.lastError().text();
        return;
    }else {
        qDebug() << "连接成功 connect to mysql OK";
    }
    // 设置模型
    model = new QSqlTableModel(this);
}

HospitalUserSystem::~HospitalUserSystem()
{
    delete ui;
}

