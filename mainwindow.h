#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include "imageprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void loadImages();
    void computeDisparity();

private:
    Ui::MainWindow* ui;
    cv::Mat leftImage, rightImage;
    ImageProcessor processor;

    void displayImage(const cv::Mat& mat, QLabel* label);
};

#endif // MAINWINDOW_H
