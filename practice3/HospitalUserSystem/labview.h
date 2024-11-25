#ifndef LABVIEW_H
#define LABVIEW_H

#include <QWidget>

namespace Ui {
class LabView;
}

class LabView : public QWidget
{
    Q_OBJECT

public:
    explicit LabView(QWidget *parent = nullptr);
    ~LabView();

private:
    Ui::LabView *ui;
};

#endif // LABVIEW_H
