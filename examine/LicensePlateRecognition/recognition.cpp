#include "recognition.h"

Recognition::Recognition()
{

}

Recognition::~Recognition()
{

}

void Recognition::startRecognition(const QImage &image)
{
    cv::Mat cv_image = OpenCVTool::QImageToMat(image);
    cv::imshow("demo",cv_image);
}
