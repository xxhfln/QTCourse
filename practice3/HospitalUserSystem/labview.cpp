#include "labview.h"
#include "ui_labview.h"

LabView::LabView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabView)
{
    ui->setupUi(this);
}

LabView::~LabView()
{
    delete ui;
}
