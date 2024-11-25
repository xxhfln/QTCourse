#include "hospitalusersystem.h"
#include "ui_hospitalusersystem.h"

HospitalUserSystem::HospitalUserSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HospitalUserSystem)
{
    ui->setupUi(this);
}

HospitalUserSystem::~HospitalUserSystem()
{
    delete ui;
}

