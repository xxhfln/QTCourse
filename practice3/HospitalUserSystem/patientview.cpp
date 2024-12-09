#include "patientview.h"
#include "ui_patientview.h"

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    DataBase &db = DataBase::getInstance();
    if (db.initPatientModel()){
        ui->tableView->setModel(db.patientTabModel.get());
        ui->tableView->setSelectionModel(db.patientSelection.get());
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_pushButton_2_clicked()
{
    int currow = DataBase::getInstance().addNewPatient();
    emit goPatientEdit(currow);
}


void PatientView::on_btn_find_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->lineEdit->text());
    DataBase::getInstance().searchPatient(filter);
}


void PatientView::on_btn_delete_clicked()
{
    DataBase::getInstance().deleteCurrentPatient();
}


void PatientView::on_btn_edit_clicked()
{
    // 获取当前选择单元格的模型索引
    QModelIndex curIndex = DataBase::getInstance().patientSelection->currentIndex();
    emit goPatientEdit(curIndex.row());
}

