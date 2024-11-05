#include "replace.h"
#include "ui_replace.h"

Replace::Replace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Replace)
{
    ui->setupUi(this);

    this->setWindowTitle("替换");
    this->setWindowIcon(QIcon(":/images/images/replace.png"));
}

Replace::~Replace()
{
    delete ui;
}
