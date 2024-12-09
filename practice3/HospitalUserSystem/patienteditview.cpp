#include "patienteditview.h"
#include "ui_patienteditview.h"

PatientEditView::PatientEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tableModel = DataBase::getInstance().patientTabModel.get();
    dataMapper->setModel(tableModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->id_edit,tableModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->name_edit,tableModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->number_edit,tableModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->height_spin,tableModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->weight_spin,tableModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->phone_edit,tableModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->date,tableModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->sex_box,tableModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->create_date,tableModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);
    // 只有获得焦点才会保存到数据库
    ui->create_date->setFocus();
    ui->sex_box->setFocus();
    ui->id_edit->setFocus();

}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()
{
    DataBase::getInstance().submitPatientEdit();
    emit cancel();
}

void PatientEditView::on_pushButton_2_clicked()
{
    DataBase::getInstance().revertPatientEdit();
    emit cancel();
}
