#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "common.h"
#include "database.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void confirmRegister();
    void cancel();

private slots:
    void on_register_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
