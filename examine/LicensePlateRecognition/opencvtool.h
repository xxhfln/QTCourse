#ifndef OPENCVTOOL_H
#define OPENCVTOOL_H

#include "opencv2/opencv.hpp"
#include "common.h"

class OpenCVTool
{
public:
    OpenCVTool();
    ~OpenCVTool();

    static QImage MatToQImage(const cv::Mat &cvImage);
    static cv::Mat QImageToMat(const QImage &qImage);
};

#endif // OPENCVTOOL_H
