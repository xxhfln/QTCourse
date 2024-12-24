#include "masterview.h"
#include "ui_masterview.h"

MasterView::MasterView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goView(QWidget *view)
{
    qDebug() << "go" << view->windowTitle();
    ui->stackedWidget->addWidget(view);
    pushWidgetToStackView(view);
}

void MasterView::goLoginView()
{
    Login* login = new Login(this);
    goView(login);
    connect(login,&Login::goRegister,this,&MasterView::goRegisterView);
}

void MasterView::goRegisterView()
{
    Register* register_ = new Register(this);
    goView(register_);
    connect(register_,&Register::confirmRegister,this,&MasterView::goPreviousView);
    connect(register_,&Register::cancel,this,&MasterView::goPreviousView);
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->label->setText(widget->windowTitle());
}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();
    if (count > 1){
        QWidget* widget = ui->stackedWidget->currentWidget();
        ui->stackedWidget->removeWidget(widget);
        delete widget;
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->label->setText(ui->stackedWidget->currentWidget()->windowTitle());
    }
}
