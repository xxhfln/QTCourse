#include "licenseplaterecognition.h"
#include "ui_licenseplaterecognition.h"

LicensePlateRecognition::LicensePlateRecognition(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LicensePlateRecognition)
{
    ui->setupUi(this);

    initProgram();
}

LicensePlateRecognition::~LicensePlateRecognition()
{
    delete ui;
}

void LicensePlateRecognition::initProgram()
{
    recognition = new Recognition();
    connect(this,&LicensePlateRecognition::startRecognition,recognition,&Recognition::startRecognition);
    connect(recognition,&Recognition::recognitionResult,this,&LicensePlateRecognition::receiveRecognitionResult);

    ui->recognition_btn->setEnabled(false);

    master_view = new MasterView();
    master_view->show();
    connect(master_view,&MasterView::UserLoginSuccess,this,&LicensePlateRecognition::UserLoginSuccess);
    this->hide();
}


void LicensePlateRecognition::on_select_btn_clicked()
{
    filename = QFileDialog::getOpenFileName(this,"选择图片",
                                                    "../LicensePlateRecognition/image",
                                                    "Images(*.jpg *.png *.jpeg *.bmp *.webp)");
    if (filename.isEmpty()){
        qDebug() << "文件路径为空";
        return;
    }
    image.load(filename);
    pixmap = QPixmap::fromImage(image);
    ui->image_label->setPixmap(pixmap);

    ui->recognition_btn->setEnabled(true);
}

void LicensePlateRecognition::receiveRecognitionResult(const QString &msg)
{
    ui->textEdit->setText(msg);
}


void LicensePlateRecognition::on_recognition_btn_clicked()
{
    emit startRecognition(this->filename);
}

void LicensePlateRecognition::UserLoginSuccess()
{
    master_view->close();
    this->show();
}

