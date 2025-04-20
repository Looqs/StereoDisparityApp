#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <memory>
#include <functional>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadLeftImage_clicked();
    void on_loadRightImage_clicked();
    void on_calculateDisparity_clicked();
    void on_methodComboBox_currentIndexChanged(int index);
    void on_loadGroundTruth_clicked();
    void on_compareDisparity_clicked();

private:
    Ui::MainWindow *ui;
    QImage leftImage;
    QImage rightImage;
    QImage groundTruthImage;
    std::unique_ptr<std::function<double(const QImage&, const QImage&, int, int, int, int)>> disparityMethod;
    std::vector<std::thread> workerThreads;
    std::mutex mutex;
    int numThreads;

    // Disparity calculation methods
    double calculateSAD(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity);
    double calculateSSD(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity);
    double calculateZNCC(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity);

    // Optimized calculation methods
    double calculateSAD_Optimized(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity);
    double calculateSSD_Optimized(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity);
    
    // Thread worker functions
    void processDisparityRange(const QImage& left, const QImage& right, QImage& disparityMap, 
                             int startY, int endY, int windowSize, int maxDisparity);

    void updateDisparityMap();
    void saveDisparityMap(const QImage& disparityMap);
    
    // Accuracy measurement methods
    double calculateSSDAccuracy(const QImage& computed, const QImage& groundTruth);
    double calculateSADAccuracy(const QImage& computed, const QImage& groundTruth);
    void showAccuracyResults(double ssdAccuracy, double sadAccuracy);

    // Helper functions
    void initializeThreads();
    void cleanupThreads();
};
#endif // MAINWINDOW_H
