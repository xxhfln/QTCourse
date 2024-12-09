#ifndef HOSPITALUSERSYSTEM_H
#define HOSPITALUSERSYSTEM_H

#include <QMainWindow>

#include "common.h"
#include "login.h"
#include "welcome.h"
#include "doctorview.h"
#include "labview.h"
#include "patientview.h"
#include "patienteditview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HospitalUserSystem; }
QT_END_NAMESPACE

class HospitalUserSystem : public QMainWindow
{
    Q_OBJECT

public:
    HospitalUserSystem(QWidget *parent = nullptr);
    ~HospitalUserSystem();

public slots:
    void goView(QWidget* view);
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPatientEditView(int index);
    void goPreviousView();
    void pushWidgetToStackView(QWidget* widget);

private slots:
    void on_stackedWidget_currentChanged(int arg1);

    void on_btn_exit_clicked();

    void on_btn_back_clicked();

private:
    Ui::HospitalUserSystem *ui;

};
#endif // HOSPITALUSERSYSTEM_H
