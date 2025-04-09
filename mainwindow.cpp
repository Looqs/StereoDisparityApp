#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadImages, &QPushButton::clicked, this, &MainWindow::loadImages);
    connect(ui->btnCompute, &QPushButton::clicked, this, &MainWindow::computeDisparity);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadImages() {
    QString leftPath = QFileDialog::getOpenFileName(this, "Left Image");
    QString rightPath = QFileDialog::getOpenFileName(this, "Right Image");

    if (leftPath.isEmpty() || rightPath.isEmpty()) return;

    leftImage = cv::imread(leftPath.toStdString());
    rightImage = cv::imread(rightPath.toStdString());

    if (leftImage.empty() || rightImage.empty()) {
        QMessageBox::critical(this, "Error", "Could not load images.");
        return;
    }

    displayImage(leftImage, ui->labelLeft);
    displayImage(rightImage, ui->labelRight);
}

void MainWindow::computeDisparity() {
    if (leftImage.empty() || rightImage.empty()) {
        QMessageBox::warning(this, "Warning", "Load both images first.");
        return;
    }

    int windowSize = ui->lineWindowSize->text().toInt();
    if (windowSize < 3 || windowSize > 21 || windowSize % 2 == 0) {
        QMessageBox::warning(this, "Invalid Size", "Window size must be odd and between 3 and 21.");
        return;
    }

    QString methodStr = ui->comboMethod->currentText();
    ImageProcessor::DiffFunction method = nullptr;

    if (methodStr == "SAD") method = &ImageProcessor::computeSAD;
    else if (methodStr == "SSD") method = &ImageProcessor::computeSSD;
    else if (methodStr == "ZNCC") method = &ImageProcessor::computeZNCC;

    if (!method) return;

    cv::Mat result = (processor.*method)(leftImage, rightImage, windowSize);

    displayImage(result, ui->labelOutput);
    cv::imwrite("disparity_map.png", result);
    QMessageBox::information(this, "Success", "Disparity map saved as disparity_map.png");
}

void MainWindow::displayImage(const cv::Mat& mat, QLabel* label) {
    cv::Mat rgb;
    cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
    QImage img(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(img).scaled(label->size(), Qt::KeepAspectRatio));
}
