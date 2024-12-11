#include "licenseplaterecognition.h"
#include "ui_licenseplaterecognition.h"

LicensePlateRecognition::LicensePlateRecognition(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LicensePlateRecognition)
{
    ui->setupUi(this);
}

LicensePlateRecognition::~LicensePlateRecognition()
{
    delete ui;
}

