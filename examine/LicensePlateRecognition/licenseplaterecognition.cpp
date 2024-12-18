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


void LicensePlateRecognition::on_select_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"选择图片",
                                                    "../LicensePlateRecognition/image",
                                                    "Images(*.jpg *.png *.jpeg *.bmp)");
    if (filename.isEmpty()){
        QMessageBox::information(this,"warn","文件路径为空");
        return;
    }
    image.load(filename);
    pixmap = QPixmap::fromImage(image);
    ui->image_label->setPixmap(pixmap);
}

