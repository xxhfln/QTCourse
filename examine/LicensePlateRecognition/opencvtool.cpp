#include "opencvtool.h"

OpenCVTool::OpenCVTool()
{

}

OpenCVTool::~OpenCVTool()
{

}

QImage OpenCVTool::MatToQImage(const cv::Mat &cvImage)
{
    QImage image;
    switch(cvImage.type())
    {
    // QImage构造:数据，宽度，高度，每行多少字节，存储结构
    case CV_8UC1:
        image = QImage((const unsigned char*)cvImage.data,cvImage.cols,cvImage.rows
                       ,cvImage.step,QImage::Format_Grayscale8);
        break;
    case CV_8UC3:
        image = QImage((const unsigned char*)cvImage.data,cvImage.cols,cvImage.rows
                       ,cvImage.step,QImage::Format_RGB888);
        image = image.rgbSwapped(); // RGB转为BGR
        break;
    case CV_8UC4:
        image = QImage((const unsigned char*)cvImage.data,cvImage.cols,cvImage.rows
                       ,cvImage.step,QImage::Format_ARGB32);
        break;
    case CV_16UC4:
        image = QImage((const unsigned char*)cvImage.data,cvImage.cols,cvImage.rows
                       ,cvImage.step,QImage::Format_RGBA64);
        image = image.rgbSwapped(); // RGB转为BGR
        break;
    default:
        break;
    }
    return image;
}

cv::Mat OpenCVTool::QImageToMat(const QImage &qImage)
{
    cv::Mat mat;
    switch(qImage.format())
    {
    case QImage::Format_Grayscale8: // 灰度图，每个像素点1个字节（8位）
        // Mat构造：行数，列数，存储结构，数据，step每行多少字节
        mat = cv::Mat(qImage.height(), qImage.width(), CV_8UC1, (void*)qImage.constBits(), qImage.bytesPerLine());
        break;
    case QImage::Format_ARGB32: // uint32存储0xAARRGGBB，pc一般小端存储低位在前，所以字节顺序就成了BGRA
    case QImage::Format_RGB32: // Alpha为FF
        //    case QImage::Format_ARGB32_Premultiplied:
        //        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        //        break;
    case QImage::Format_ARGB32_Premultiplied:
    {
        mat = cv::Mat(qImage.height(), qImage.width(), CV_8UC4, (void*)qImage.constBits(), qImage.bytesPerLine());
        std::vector<cv::Mat>channels;
        split(mat, channels);
        channels.pop_back();
        cv::merge(channels, mat);
        return mat;
    }
    case QImage::Format_RGB888: // RR,GG,BB字节顺序存储
        mat = cv::Mat(qImage.height(), qImage.width(), CV_8UC3, (void*)qImage.constBits(), qImage.bytesPerLine());
        return mat.clone();
        break;
    case QImage::Format_RGBA64: // uint64存储，顺序和Format_ARGB32相反，RGBA
        mat = cv::Mat(qImage.height(), qImage.width(), CV_16UC4, (void*)qImage.constBits(), qImage.bytesPerLine());
        // opencv需要转为BGRA的字节顺序
        cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGRA);
        break;

    case QImage::Format_Mono:
    case QImage::Format_MonoLSB:
    {
        QImage rgbImage = qImage.convertToFormat(QImage::Format_Grayscale8);
        return cv::Mat(rgbImage.height(), rgbImage.width(), CV_8UC1, (void*)rgbImage.bits(), rgbImage.bytesPerLine()).clone();
    }

    case QImage::Format_Indexed8:
    {
        mat = cv::Mat(qImage.height(), qImage.width(), CV_8UC1, (void*)qImage.constBits(), qImage.bytesPerLine());
        return mat.clone();
    }
    default:
        return mat;

    }
    return mat;
}
