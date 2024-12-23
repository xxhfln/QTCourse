#include "recognition.h"

Recognition::Recognition()
{

}

Recognition::~Recognition()
{

}

cv::Mat Recognition::getCarNumberBorder(cv::Mat &image)
{
    cv::Mat img_HSV = image.clone();
    cv::Mat img_t = image.clone();

    cv::Mat img2_gauss;
    cv::Mat img2_gray,dst_x,abs_X;
    // 高斯去噪
    cv::GaussianBlur(img_HSV, img2_gauss, cv::Size(3,3),0);
    // 转灰度图
    cv::cvtColor(img2_gauss, img2_gray, cv::COLOR_BGR2GRAY);

    cv::Sobel(img2_gray, dst_x, CV_16S, 1, 0); // 梯度算子
    cv::convertScaleAbs(dst_x, abs_X); // 将CV_16S型的输出图像转变成CV_8U型的图像
//    cv::imshow("tests1",img2_gauss);
//    cv::imshow("tests2",img2_gray);
//    cv::imshow("tests3",dst_x);

    cv::Mat img_temo = abs_X;
    cv::threshold(img_temo, img_temo, 0, 255, cv::THRESH_OTSU); // 自适应阀值图像灰度大于阈值
//    cv::imshow("tests4",img_temo);

    // 闭操作，封闭轮廓
    cv::Mat kernelY;
    cv::Mat kernelX = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(17,5));
    cv::morphologyEx(img_temo, img_temo, cv::MORPH_CLOSE, kernelX);
    cv::imshow("tests5",img_temo);
    //用矩形来封闭
    kernelX = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(20, 1));
    kernelY = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 19));
    cv::dilate(img_temo, img_temo, kernelX);
    cv::dilate(img_temo, img_temo, kernelX);
    cv::erode(img_temo, img_temo, kernelX);
    cv::erode(img_temo, img_temo, kernelY);
    cv::dilate(img_temo, img_temo, kernelY);
    // 平滑去噪处理,使边缘检测更准确
    cv::GaussianBlur(img_temo, img_temo, cv::Size(15,0),1);
    cv::imshow("tests6",img_temo);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> vec_4f;
    // 从二值化后的img图中提取所有轮廓
    cv::findContours(img_temo, contours, vec_4f, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat plate;
    int j = 0;
    std::vector<std::vector<cv::Point>> contours_1;
    cv::Rect rect_1;
    for (int i = 0;i < contours.size();i++){
        // 计算轮廓的垂直边界最小矩形
        cv::Rect rect = cv::boundingRect(contours[i]);
        int area = rect.height * rect.width;
        if (rect.width > (rect.height * 2.3) && area > 10000){
            plate = img_HSV(cv::Rect(rect.x,rect.y,rect.width,rect.width)); // 区域提取
            // 将提取出来的区域拿绿色矩形围起来
            cv::rectangle(plate,cv::Point(rect.x,rect.y),cv::Point(rect.x+rect.width,rect.y+rect.height)
                          ,cv::Scalar(0,255,0),1);
            rect_1 = rect;
            contours_1.push_back(contours[i]);
        }
    }
    qDebug() << "1";
    return plate;
}

void Recognition::startRecognition(const QImage &image)
{
    cv::Mat cv_image = OpenCVTool::QImageToMat(image);
    cv::imshow("demo",cv_image);

    getCarNumberBorder(cv_image);
}
