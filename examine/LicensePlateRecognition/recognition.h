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
    void initFilePaths();
    void getFilesInDirectory(const QString& dir_path,const int& index,QVector<QVector<QString>>& paths);
    cv::Mat getCarNumberBorder(cv::Mat &image);
    cv::Mat getLicensePlateROI(cv::Mat &src);
    bool PixelCounter(const cv::Mat& img, int& blackCount, int& whiteCount);
    cv::Mat HoriconCut(cv::Mat& image);
    QVector<QVector<int>> RemoveVertialBorder(cv::Mat& image);

signals:
    void recognitionResult(const QString &msg);

public slots:
    void startRecognition(const QImage &image);

public:
    QString chars[34]{
      "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
      "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W",
      "X", "Y", "Z"
    };
    QString chineses[31]{
      "藏", "川", "鄂", "甘", "赣", "贵",
      "桂", "黑", "沪", "吉", "冀", "津",
      "晋", "京", "辽", "鲁", "蒙", "闽",
      "宁", "青", "琼", "陕", "苏", "皖",
      "湘", "新", "渝", "豫", "粤", "云", "浙"
    };
    QVector<QVector<QString>> char_filepaths;
    QVector<QVector<QString>> chinese_filepaths;
};

#endif // RECOGNITION_H
