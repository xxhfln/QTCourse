#include "hospitalusersystem.h"
#include "ui_hospitalusersystem.h"

HospitalUserSystem::HospitalUserSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HospitalUserSystem)
{
    ui->setupUi(this);


    goLoginView();
}

HospitalUserSystem::~HospitalUserSystem()
{
    delete ui;
}

void HospitalUserSystem::goView(QWidget *view)
{
    qDebug() << "go" << view->windowTitle();
    ui->stackedWidget->addWidget(view);
    pushWidgetToStackView(view);
}

void HospitalUserSystem::goLoginView()
{
    Login* login = new Login(this);
    goView(login);
    connect(login,&Login::loginSuccess,this,&HospitalUserSystem::goWelcomeView);
}

void HospitalUserSystem::goWelcomeView()
{
    Welcome* wel = new Welcome();
    goView(wel);
    connect(wel,&Welcome::goDepartment,this,&HospitalUserSystem::goDepartmentView);
    connect(wel,&Welcome::goDoctor,this,&HospitalUserSystem::goDoctorView);
    connect(wel,&Welcome::goPatient,this,&HospitalUserSystem::goPatientView);
}

void HospitalUserSystem::goDoctorView()
{
    goView(new DoctorView(this));
}

void HospitalUserSystem::goDepartmentView()
{
    goView(new LabView(this));
}

void HospitalUserSystem::goPatientView()
{
    PatientView* pa = new PatientView();
    goView(pa);
    connect(pa,&PatientView::goPatientEdit,this,&HospitalUserSystem::goPatientEditView);
}

void HospitalUserSystem::goPatientEditView()
{
    PatientEditView* pa = new PatientEditView();
    goView(pa);
    connect(pa,&PatientEditView::cancel,this,&HospitalUserSystem::goPatientView);
}

void HospitalUserSystem::goPreviousView()
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

void HospitalUserSystem::pushWidgetToStackView(QWidget *widget)
{
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->label->setText(widget->windowTitle());
}


void HospitalUserSystem::on_stackedWidget_currentChanged(int arg1)
{
    ui->btn_back->setEnabled(ui->stackedWidget->count() > 1);
    ui->btn_back->setEnabled(ui->stackedWidget->currentWidget()->windowTitle() != "登录");
//    qDebug()<<"11";
}


void HospitalUserSystem::on_btn_exit_clicked()
{
    if (ui->stackedWidget->currentWidget()->windowTitle() == "登录"){
        this->close();
    }
    goPreviousView();
}


void HospitalUserSystem::on_btn_back_clicked()
{
    goPreviousView();
}

