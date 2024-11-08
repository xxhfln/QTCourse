#include "findtext.h"
#include "ui_findtext.h"

FindText::FindText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindText)
{
    ui->setupUi(this);

    init();
}

FindText::~FindText()
{
    delete ui;
}

void FindText::init(){
    this->setWindowIcon(QIcon(":/images/images/find.png"));
    this->setWindowTitle("查找");
}


void FindText::on_findNext_clicked()
{
    if (ui->up_btn->isChecked()){
        emit findPreviousRequested(ui->lineEdit->text());
    }else if (ui->down_btn->isChecked()){
        emit findNextRequested(ui->lineEdit->text());
    }

}

