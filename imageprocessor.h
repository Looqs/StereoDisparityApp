#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    typedef cv::Mat(ImageProcessor::* DiffFunction)(const cv::Mat&, const cv::Mat&, int);

    cv::Mat computeSAD(const cv::Mat& left, const cv::Mat& right, int winSize);
    cv::Mat computeSSD(const cv::Mat& left, const cv::Mat& right, int winSize);
    cv::Mat computeZNCC(const cv::Mat& left, const cv::Mat& right, int winSize);
};

#endif // IMAGEPROCESSOR_H
