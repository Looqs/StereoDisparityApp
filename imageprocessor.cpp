#include "imageprocessor.h"
#include <cmath>

cv::Mat ImageProcessor::computeSAD(const cv::Mat& left, const cv::Mat& right, int winSize) {
    int rows = left.rows;
    int cols = left.cols;
    int d = winSize / 2;
    cv::Mat disp(rows, cols, CV_8U, cv::Scalar(0));

    for (int y = d; y < rows - d; ++y) {
        for (int x = d; x < cols - d; ++x) {
            int minDiff = INT_MAX;
            int bestOffset = 0;
            for (int offset = -d; offset <= d; ++offset) {
                int x2 = x + offset;
                if (x2 < d || x2 >= cols - d) continue;
                int sum = 0;
                for (int v = -d; v <= d; ++v) {
                    for (int u = -d; u <= d; ++u) {
                        cv::Vec3b p1 = left.at<cv::Vec3b>(y + v, x + u);
                        cv::Vec3b p2 = right.at<cv::Vec3b>(y + v, x2 + u);
                        for (int c = 0; c < 3; ++c)
                            sum += std::abs(p1[c] - p2[c]);
                    }
                }
                if (sum < minDiff) {
                    minDiff = sum;
                    bestOffset = std::abs(offset);
                }
            }
            disp.at<uchar>(y, x) = static_cast<uchar>(bestOffset * 255 / d);
        }
    }
    return disp;
}

cv::Mat ImageProcessor::computeSSD(const cv::Mat& left, const cv::Mat& right, int winSize) {
    int rows = left.rows;
    int cols = left.cols;
    int d = winSize / 2;
    cv::Mat disp(rows, cols, CV_8U, cv::Scalar(0));

    for (int y = d; y < rows - d; ++y) {
        for (int x = d; x < cols - d; ++x) {
            int minDiff = INT_MAX;
            int bestOffset = 0;
            for (int offset = -d; offset <= d; ++offset) {
                int x2 = x + offset;
                if (x2 < d || x2 >= cols - d) continue;
                int sum = 0;
                for (int v = -d; v <= d; ++v) {
                    for (int u = -d; u <= d; ++u) {
                        cv::Vec3b p1 = left.at<cv::Vec3b>(y + v, x + u);
                        cv::Vec3b p2 = right.at<cv::Vec3b>(y + v, x2 + u);
                        for (int c = 0; c < 3; ++c)
                            sum += (p1[c] - p2[c]) * (p1[c] - p2[c]);
                    }
                }
                if (sum < minDiff) {
                    minDiff = sum;
                    bestOffset = std::abs(offset);
                }
            }
            disp.at<uchar>(y, x) = static_cast<uchar>(bestOffset * 255 / d);
        }
    }
    return disp;
}

cv::Mat ImageProcessor::computeZNCC(const cv::Mat& left, const cv::Mat& right, int winSize) {
    int rows = left.rows;
    int cols = left.cols;
    int d = winSize / 2;
    cv::Mat disp(rows, cols, CV_8U, cv::Scalar(0));

    for (int y = d; y < rows - d; ++y) {
        for (int x = d; x < cols - d; ++x) {
            double maxCorr = -1.0;
            int bestOffset = 0;

            for (int offset = -d; offset <= d; ++offset) {
                int x2 = x + offset;
                if (x2 < d || x2 >= cols - d) continue;

                double mean1 = 0, mean2 = 0, std1 = 0, std2 = 0, corr = 0;
                std::vector<double> v1, v2;

                for (int v = -d; v <= d; ++v) {
                    for (int u = -d; u <= d; ++u) {
                        cv::Vec3b p1 = left.at<cv::Vec3b>(y + v, x + u);
                        cv::Vec3b p2 = right.at<cv::Vec3b>(y + v, x2 + u);
                        for (int c = 0; c < 3; ++c) {
                            v1.push_back(p1[c]);
                            v2.push_back(p2[c]);
                        }
                    }
                }

                int n = v1.size();
                for (int i = 0; i < n; ++i) {
                    mean1 += v1[i];
                    mean2 += v2[i];
                }
                mean1 /= n; mean2 /= n;

                for (int i = 0; i < n; ++i) {
                    std1 += (v1[i] - mean1) * (v1[i] - mean1);
                    std2 += (v2[i] - mean2) * (v2[i] - mean2);
                    corr += (v1[i] - mean1) * (v2[i] - mean2);
                }

                std1 = sqrt(std1);
                std2 = sqrt(std2);
                if (std1 * std2 == 0) continue;
                double zncc = corr / (std1 * std2);

                if (zncc > maxCorr) {
                    maxCorr = zncc;
                    bestOffset = std::abs(offset);
                }
            }

            disp.at<uchar>(y, x) = static_cast<uchar>(bestOffset * 255 / d);
        }
    }

    return disp;
}
