#ifndef LICENSEPLATERECOGNITION_H
#define LICENSEPLATERECOGNITION_H

#include <QMainWindow>
#include "common.h"
#include "opencvtool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LicensePlateRecognition; }
QT_END_NAMESPACE

class LicensePlateRecognition : public QMainWindow
{
    Q_OBJECT

public:
    LicensePlateRecognition(QWidget *parent = nullptr);
    ~LicensePlateRecognition();

private slots:
    void on_select_btn_clicked();

private:
    Ui::LicensePlateRecognition *ui;

    QImage image;
    QPixmap pixmap;
};
#endif // LICENSEPLATERECOGNITION_H
