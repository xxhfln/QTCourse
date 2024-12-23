#include "recognition.h"

Recognition::Recognition()
{
    initFilePaths();
}

Recognition::~Recognition()
{

}

void Recognition::initFilePaths()
{
    char_filepaths.resize(34);
    chinese_filepaths.resize(31);
    char_filepaths.clear();
    chinese_filepaths.clear();
    QString pre = "../LicensePlateRecognition/refer1/";
    for(int i = 0;i < 34;++i){
        QString path = pre + chars[i];
        getFilesInDirectory(path,i,this->char_filepaths);
    }
    for(int i = 0;i < 31;++i){
        QString path = pre + chineses[i];
        getFilesInDirectory(path,i,this->chinese_filepaths);
    }

    for(int i = 0;i < char_filepaths.size();i++){
        for (QString& path : char_filepaths[i]){
            qDebug()<<path;
        }
    }
    for(int i = 0;i < chinese_filepaths.size();i++){
        for (QString& path : chinese_filepaths[i]){
            qDebug()<<path;
        }
    }
}

void Recognition::getFilesInDirectory(const QString &dir_path, const int &index, QVector<QVector<QString> > &paths)
{
    QDir dir(dir_path);
    if (!dir.exists()){
        qWarning() << "Directory does not exist!";
        return;
    }

    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QVector<QString> temp;
    for(const QString& file : files){
        temp.push_back(dir.absoluteFilePath(file));
    }
    paths.push_back(temp);
}

cv::Mat Recognition::getCarNumberBorder(cv::Mat &image)
{
    if (image.empty()){
        QMessageBox::critical(nullptr,"ERROR","Input image is not a valid binary image!");
        return cv::Mat();
    }
    cv::Mat img_HSV = image.clone();
    cv::Mat img_clone = image.clone();
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
//    cv::imshow("tests5",img_temo);
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
//    cv::imshow("tests6",img_temo);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> vec_4f;
    // 从二值化后的img图中提取所有轮廓
    cv::findContours(img_temo, contours, vec_4f, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat plate;
    std::vector<std::vector<cv::Point>> contours_1;
    cv::Rect rect_1;
    for (int i = 0;i < contours.size();i++){
        // 计算轮廓的垂直边界最小矩形
        cv::Rect rect = cv::boundingRect(contours[i]);
        int area = rect.height * rect.width;
        if (rect.width > (rect.height * 2.3) && area > 10000){
            plate = img_clone(cv::Rect(rect.x,rect.y,rect.width,rect.height)); // 区域提取
            // 将提取出来的区域拿绿色矩形围起来
            cv::rectangle(img_HSV,cv::Point(rect.x,rect.y),cv::Point(rect.x+rect.width,rect.y+rect.height)
                          ,cv::Scalar(0,255,0),3);
            rect_1 = rect;
            contours_1.push_back(contours[i]);
        }
    }
    cv::imshow("plate",img_HSV);
    return plate;
}

cv::Mat Recognition::getLicensePlateROI(cv::Mat &src)
{
    if (src.empty()){
        QMessageBox::critical(nullptr,"ERROR","Input image is not a valid binary image!");
        return cv::Mat();
    }
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::Mat thresh;
    cv::threshold(gray, thresh, 0, 255, cv::THRESH_OTSU);

    // 形态学开操作去除小轮廓
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
    cv::Mat open;
    cv::morphologyEx(thresh, open, cv::MORPH_OPEN, kernel);

    int black_count = 0,white_count = 0;
    PixelCounter(open, black_count, white_count);
    qDebug() << "黑像素点：" << black_count << " 白像素点：" << white_count;
    if (black_count < white_count){
        cv::bitwise_not(open, open); // 反转黑白像素点
    }

    return open;
}

bool Recognition::PixelCounter(const cv::Mat &img, int &blackCount, int &whiteCount)
{
    // 检查图像是否为二值化图像（只有两种像素值）
    if (img.empty() || img.type() != CV_8UC1){
        QMessageBox::critical(nullptr,"ERROR","Input image is not a valid binary image!");
        return false;
    }
    blackCount = whiteCount = 0; // 清零

    // 遍历每个像素
    for (int i = 0;i < img.rows;++i){
        for (int j = 0;j < img.cols;++j){
            if (img.at<uchar>(i,j) == 0){
                ++blackCount;
            }else {
                ++whiteCount;
            }
        }
    }

    return true;
}

cv::Mat Recognition::HoriconCut(cv::Mat &image)
{
    // 检查图像是否为二值化图像（只有两种像素值）
    if (image.empty() || image.type() != CV_8UC1){
        QMessageBox::critical(nullptr,"ERROR","Input image is not a valid binary image!");
        return cv::Mat();
    }
    cv::Mat temp = image.clone();
    int rows = temp.rows;
    int cols = temp.cols;

    QVector<int> white_n;
    for(int row = 0;row < rows;++row){
        int tem = 0;
        for(int col = 0;col < cols;++col){
            if (temp.at<uchar>(row,col) > 0){
                ++tem;
            }
        }
        white_n.append(tem);
    }

    int mid = 0;
    for (int i = 0;i < rows/2;++i){
        mid += white_n[i];
    }
    mid = mid/(rows/2 + 1);

    int i_0 = 0, i_1 = 0;
    for(int i = rows/2;i >= 2;--i){
        if (white_n[i] < mid){
            i_0 = i;
            break;
        }
    }
    for(int i = rows/2;i < rows;++i){
        if (white_n[i] < mid){
            i_1 = i;
            break;
        }
    }
    cv::Mat test = temp(cv::Range(i_0,i_1),cv::Range(0,cols));

    return test;
}

QVector<QVector<int> > Recognition::RemoveVertialBorder(cv::Mat &image)
{
    // 检查图像是否为二值化图像（只有两种像素值）
    if (image.empty() || image.type() != CV_8UC1){
        QMessageBox::critical(nullptr,"ERROR","Input image is not a valid binary image!");
        return QVector<QVector<int>>();
    }
    cv::Mat temp = image.clone();
    int rows = temp.rows;
    int cols = temp.cols;

    QVector<int> white_n;
    for(int col = 0;col < cols;++col){
        int tem = 0;
        for(int row = 0;row < rows;++row){
            if (temp.at<uchar>(row,col) > 0){
                ++tem;
            }
        }
        white_n.append(tem);
    }
    QVector<QVector<int>> region1;
    QVector<int> reg;
    if (white_n[0] != 0){
        reg.append(0);
    }
    for(int i = 0;i < cols - 1;++i){
        if (white_n[i] == 0 && white_n[i+1] != 0){
            reg.append(i);
        }
        if (white_n[i] != 0 && white_n[i+1] == 0){
            reg.append(i+1);
        }
        if (reg.size() == 2){
            if (reg[1] - reg[0] > 10){
                region1.append(reg);
            }
            reg.clear();
        }
    }
    return region1;
}

void Recognition::startRecognition(const QImage &image)
{
    cv::Mat cv_image = OpenCVTool::QImageToMat(image);
    cv::imshow("demo",cv_image);

    cv::Mat plate = getCarNumberBorder(cv_image);
    cv::imshow("plate_ROI",plate);

    cv::Mat thresh = getLicensePlateROI(plate);
    cv::imshow("plate_ROI_thresh",thresh);

    cv::Mat cut = HoriconCut(thresh);
    cv::imshow("cut",cut);

    QVector<QVector<int>> t = RemoveVertialBorder(cut);
    int j = 0;
    for(int i = 0;i < t.size();++i){
        cv::Mat str = cut(cv::Range(0,cut.rows),cv::Range(t[i][0],t[i][1]));
        ++j;
        QString t_s = QString::number(j);
        std::string s = std::string((const char *)t_s.toLocal8Bit());
        cv::imwrite("../LicensePlateRecognition/car_each_number/" + s + ".jpg",str);
        cv::imshow(s,str);
    }
}
