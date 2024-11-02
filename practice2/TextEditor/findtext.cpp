#include "findtext.h"
#include "ui_findtext.h"

FindText::FindText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindText)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/images/find.png"));
    this->setWindowTitle("查找");
}

FindText::~FindText()
{
    delete ui;
}
