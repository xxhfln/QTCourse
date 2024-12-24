#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QMainWindow>
#include "common.h"
#include "login.h"
#include "register.h"

namespace Ui {
class MasterView;
}

class MasterView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterView(QWidget *parent = nullptr);
    ~MasterView();

signals:
    void UserLoginSuccess();

public slots:
    void goView(QWidget* view);
    void goLoginView();
    void goRegisterView();
    void pushWidgetToStackView(QWidget* widget);
    void goPreviousView();
    void LoginSuccess();

private:
    Ui::MasterView *ui;
};

#endif // MASTERVIEW_H
