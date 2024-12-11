#ifndef LICENSEPLATERECOGNITION_H
#define LICENSEPLATERECOGNITION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LicensePlateRecognition; }
QT_END_NAMESPACE

class LicensePlateRecognition : public QMainWindow
{
    Q_OBJECT

public:
    LicensePlateRecognition(QWidget *parent = nullptr);
    ~LicensePlateRecognition();

private:
    Ui::LicensePlateRecognition *ui;
};
#endif // LICENSEPLATERECOGNITION_H
