#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QMainWindow>

namespace Ui {
class MasterView;
}

class MasterView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterView(QWidget *parent = nullptr);
    ~MasterView();



private:
    Ui::MasterView *ui;
};

#endif // MASTERVIEW_H
