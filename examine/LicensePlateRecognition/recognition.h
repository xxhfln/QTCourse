#ifndef RECOGNITION_H
#define RECOGNITION_H

#include "opencv2/opencv.hpp"
#include "opencvtool.h"
#include "common.h"

class Recognition: public QObject
{
    Q_OBJECT
public:
    Recognition();
    ~Recognition();
    cv::Mat getCarNumberBorder(cv::Mat &image);

signals:
    void recognitionResult(const QString &msg);

public slots:
    void startRecognition(const QImage &image);

};

#endif // RECOGNITION_H
