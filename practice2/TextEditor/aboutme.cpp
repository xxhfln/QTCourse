#include "aboutme.h"
#include "ui_aboutme.h"

AboutMe::AboutMe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutMe)
{
    ui->setupUi(this);

    this->setWindowTitle("About me");
    this->setWindowIcon(QIcon(":/images/images/main_icon.png"));
}

AboutMe::~AboutMe()
{
    delete ui;
}
