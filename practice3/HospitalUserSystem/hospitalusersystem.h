#ifndef HOSPITALUSERSYSTEM_H
#define HOSPITALUSERSYSTEM_H

#include <QMainWindow>

#include "common.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HospitalUserSystem; }
QT_END_NAMESPACE

class HospitalUserSystem : public QMainWindow
{
    Q_OBJECT

public:
    HospitalUserSystem(QWidget *parent = nullptr);
    ~HospitalUserSystem();

private:
    Ui::HospitalUserSystem *ui;

    QSqlTableModel *model;
};
#endif // HOSPITALUSERSYSTEM_H
