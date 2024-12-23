#ifndef LICENSEPLATERECOGNITION_H
#define LICENSEPLATERECOGNITION_H

#include <QMainWindow>
#include "common.h"
#include "opencvtool.h"
#include "recognition.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LicensePlateRecognition; }
QT_END_NAMESPACE

class LicensePlateRecognition : public QMainWindow
{
    Q_OBJECT

public:
    LicensePlateRecognition(QWidget *parent = nullptr);
    ~LicensePlateRecognition();
    void initProgram();

signals:
    void startRecognition(const QImage &image);

private slots:
    void on_select_btn_clicked();
    void receiveRecognitionResult(const QString &msg);

    void on_recognition_btn_clicked();

private:
    Ui::LicensePlateRecognition *ui;
    Recognition *recognition;

    QImage image;
    QPixmap pixmap;
};
#endif // LICENSEPLATERECOGNITION_H
