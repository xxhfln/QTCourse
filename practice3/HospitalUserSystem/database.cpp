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

    // 打开数据库
    if (!db.open()){
        qDebug() << "不能连接 connect to mysql error" << db.lastError().text();
        return;
    }else {
        qDebug() << "连接成功 connect to mysql OK";
    }
}

bool DataBase::initPatientModel()
{
    patientTabModel = std::make_unique<QSqlTableModel>(this,db);
    patientTabModel->setTable("Patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("NAME"), Qt::AscendingOrder);

    if (!patientTabModel->select()){
        qDebug()<<"Failed to select data from patient table" << patientTabModel->lastError().text();
        return false;
    }
    patientSelection = std::make_unique<QItemSelectionModel>(patientTabModel.get());
    return true;
}

QString DataBase::userLogin(QString username, QString password)
{
    QSqlQuery query;
    qDebug()<<username <<" " << password;
    QString qs = QString("select * from User where USERNAME = '%1' and PASSWORD = '%2'").arg(username).arg(password);

    query.exec(qs);

    if (query.next()){
        return "LoginSuccess";
    }else {
        return "LoginFail";
    }
}

bool DataBase::searchPatient(const QString &filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool DataBase::deleteCurrentPatient()
{
    QModelIndex curIndex = patientSelection->currentIndex();
    if (curIndex.isValid()){
        patientTabModel->removeRow(curIndex.row());
        if (patientTabModel->submitAll()){
            patientTabModel->select();
            return true;
        }else {
            qDebug()<<"Failed to submit changes to the patient table";
            return false;
        }
    }else {
        qDebug()<<"Invaild current index";
        return false;
    }
}

int DataBase::addNewPatient()
{
    int rowCount = patientTabModel->rowCount();
    patientTabModel->insertRow(rowCount, QModelIndex()); // 在末尾添加一行
    QModelIndex curIndex = patientTabModel->index(rowCount, 1); // 创建最后一行的modelIndex
    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo); // 获取当前记录
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithBraces));
    patientTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool DataBase::submitPatientEdit()
{
    if (patientTabModel->submitAll()){
        qDebug() << "Patient data submitted successfully";
        return true;
    }else {
        qDebug() << "Failed to submit patient data";
        return false;
    }
}

void DataBase::revertPatientEdit()
{
    patientTabModel->revertAll();
    qDebug() << "Patient data reverted";
}
