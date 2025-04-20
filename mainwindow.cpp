#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <cmath>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // ComboBox'a yöntemleri ekle
    ui->methodComboBox->addItem("SAD");
    ui->methodComboBox->addItem("SSD");
    ui->methodComboBox->addItem("ZNCC");
    
    // Varsayılan yöntemi ayarla
    disparityMethod = std::make_unique<std::function<double(const QImage&, const QImage&, int, int, int, int)>>(
        std::bind(&MainWindow::calculateSAD_Optimized, this, std::placeholders::_1, std::placeholders::_2,
                 std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    
    // Thread sayısını belirle
    numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4; // Varsayılan olarak 4 thread
}

MainWindow::~MainWindow()
{
    cleanupThreads();
    delete ui;
}

void MainWindow::initializeThreads()
{
    workerThreads.reserve(numThreads);
}

void MainWindow::cleanupThreads()
{
    for (auto& thread : workerThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    workerThreads.clear();
}

void MainWindow::on_loadLeftImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sol Görüntüyü Aç", "", "Resim Dosyaları (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        leftImage.load(fileName);
        ui->leftImageLabel->setPixmap(QPixmap::fromImage(leftImage).scaled(ui->leftImageLabel->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::on_loadRightImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sağ Görüntüyü Aç", "", "Resim Dosyaları (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        rightImage.load(fileName);
        ui->rightImageLabel->setPixmap(QPixmap::fromImage(rightImage).scaled(ui->rightImageLabel->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::on_methodComboBox_currentIndexChanged(int index)
{
    switch (index) {
        case 0: // SAD
            disparityMethod = std::make_unique<std::function<double(const QImage&, const QImage&, int, int, int, int)>>(
                std::bind(&MainWindow::calculateSAD_Optimized, this, std::placeholders::_1, std::placeholders::_2,
                         std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
            break;
        case 1: // SSD
            disparityMethod = std::make_unique<std::function<double(const QImage&, const QImage&, int, int, int, int)>>(
                std::bind(&MainWindow::calculateSSD_Optimized, this, std::placeholders::_1, std::placeholders::_2,
                         std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
            break;
        case 2: // ZNCC
            disparityMethod = std::make_unique<std::function<double(const QImage&, const QImage&, int, int, int, int)>>(
                std::bind(&MainWindow::calculateZNCC, this, std::placeholders::_1, std::placeholders::_2,
                         std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
            break;
    }
}

double MainWindow::calculateSAD_Optimized(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity)
{
    double minCost = std::numeric_limits<double>::max();
    int bestDisparity = 0;
    int halfWindow = windowSize / 2;
    
    // Önbellek için yerel değişkenler
    std::vector<QRgb> leftPixels(windowSize * windowSize);
    std::vector<QRgb> rightPixels(windowSize * windowSize);
    
    // Sol görüntüdeki pikselleri önbelleğe al
    int idx = 0;
    for (int i = -halfWindow; i <= halfWindow; ++i) {
        for (int j = -halfWindow; j <= halfWindow; ++j) {
            if (x + i >= 0 && x + i < left.width() && y + j >= 0 && y + j < left.height()) {
                leftPixels[idx++] = left.pixel(x + i, y + j);
            }
        }
    }
    
    for (int d = 0; d < maxDisparity; ++d) {
        double cost = 0.0;
        idx = 0;
        
        // Sağ görüntüdeki pikselleri önbelleğe al
        for (int i = -halfWindow; i <= halfWindow; ++i) {
            for (int j = -halfWindow; j <= halfWindow; ++j) {
                if (x + i - d >= 0 && x + i - d < right.width() && y + j >= 0 && y + j < right.height()) {
                    rightPixels[idx] = right.pixel(x + i - d, y + j);
                    QRgb leftPixel = leftPixels[idx];
                    QRgb rightPixel = rightPixels[idx];
                    
                    cost += std::abs(qRed(leftPixel) - qRed(rightPixel)) +
                            std::abs(qGreen(leftPixel) - qGreen(rightPixel)) +
                            std::abs(qBlue(leftPixel) - qBlue(rightPixel));
                }
                idx++;
            }
        }
        
        if (cost < minCost) {
            minCost = cost;
            bestDisparity = d;
        }
    }
    return bestDisparity;
}

double MainWindow::calculateSSD_Optimized(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity)
{
    double minCost = std::numeric_limits<double>::max();
    int bestDisparity = 0;
    int halfWindow = windowSize / 2;
    
    // Önbellek için yerel değişkenler
    std::vector<QRgb> leftPixels(windowSize * windowSize);
    std::vector<QRgb> rightPixels(windowSize * windowSize);
    
    // Sol görüntüdeki pikselleri önbelleğe al
    int idx = 0;
    for (int i = -halfWindow; i <= halfWindow; ++i) {
        for (int j = -halfWindow; j <= halfWindow; ++j) {
            if (x + i >= 0 && x + i < left.width() && y + j >= 0 && y + j < left.height()) {
                leftPixels[idx++] = left.pixel(x + i, y + j);
            }
        }
    }
    
    for (int d = 0; d < maxDisparity; ++d) {
        double cost = 0.0;
        idx = 0;
        
        // Sağ görüntüdeki pikselleri önbelleğe al
        for (int i = -halfWindow; i <= halfWindow; ++i) {
            for (int j = -halfWindow; j <= halfWindow; ++j) {
                if (x + i - d >= 0 && x + i - d < right.width() && y + j >= 0 && y + j < right.height()) {
                    rightPixels[idx] = right.pixel(x + i - d, y + j);
                    QRgb leftPixel = leftPixels[idx];
                    QRgb rightPixel = rightPixels[idx];
                    
                    double diffR = qRed(leftPixel) - qRed(rightPixel);
                    double diffG = qGreen(leftPixel) - qGreen(rightPixel);
                    double diffB = qBlue(leftPixel) - qBlue(rightPixel);
                    
                    cost += diffR * diffR + diffG * diffG + diffB * diffB;
                }
                idx++;
            }
        }
        
        if (cost < minCost) {
            minCost = cost;
            bestDisparity = d;
        }
    }
    return bestDisparity;
}

double MainWindow::calculateZNCC(const QImage& left, const QImage& right, int x, int y, int windowSize, int maxDisparity)
{
    double maxZNCC = -1.0;
    int bestDisparity = 0;
    
    for (int d = 0; d < maxDisparity; ++d) {
        double sumLeft = 0.0, sumRight = 0.0;
        double sumLeftSq = 0.0, sumRightSq = 0.0;
        double sumProduct = 0.0;
        int count = 0;
        
        for (int i = -windowSize/2; i <= windowSize/2; ++i) {
            for (int j = -windowSize/2; j <= windowSize/2; ++j) {
                if (x + i >= 0 && x + i < left.width() && y + j >= 0 && y + j < left.height() &&
                    x + i - d >= 0 && x + i - d < right.width()) {
                    QRgb leftPixel = left.pixel(x + i, y + j);
                    QRgb rightPixel = right.pixel(x + i - d, y + j);
                    
                    double leftIntensity = (qRed(leftPixel) + qGreen(leftPixel) + qBlue(leftPixel)) / 3.0;
                    double rightIntensity = (qRed(rightPixel) + qGreen(rightPixel) + qBlue(rightPixel)) / 3.0;
                    
                    sumLeft += leftIntensity;
                    sumRight += rightIntensity;
                    sumLeftSq += leftIntensity * leftIntensity;
                    sumRightSq += rightIntensity * rightIntensity;
                    sumProduct += leftIntensity * rightIntensity;
                    count++;
                }
            }
        }
        
        if (count > 0) {
            double meanLeft = sumLeft / count;
            double meanRight = sumRight / count;
            double stdLeft = std::sqrt(sumLeftSq / count - meanLeft * meanLeft);
            double stdRight = std::sqrt(sumRightSq / count - meanRight * meanRight);
            
            if (stdLeft > 0 && stdRight > 0) {
                double zncc = (sumProduct / count - meanLeft * meanRight) / (stdLeft * stdRight);
                if (zncc > maxZNCC) {
                    maxZNCC = zncc;
                    bestDisparity = d;
                }
            }
        }
    }
    return bestDisparity;
}

void MainWindow::processDisparityRange(const QImage& left, const QImage& right, QImage& disparityMap, 
                                     int startY, int endY, int windowSize, int maxDisparity)
{
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < left.width(); ++x) {
            double disparity = (*disparityMethod)(left, right, x, y, windowSize, maxDisparity);
            std::lock_guard<std::mutex> lock(mutex);
            disparityMap.setPixel(x, y, qRgb(disparity * 4, disparity * 4, disparity * 4));
        }
    }
}

void MainWindow::on_calculateDisparity_clicked()
{
    if (leftImage.isNull() || rightImage.isNull()) {
        QMessageBox::warning(this, "Hata", "Lütfen önce her iki görüntüyü de yükleyin.");
        return;
    }
    
    bool ok;
    int windowSize = ui->windowSizeEdit->text().toInt(&ok);
    if (!ok || windowSize < 3 || windowSize > 21 || windowSize % 2 == 0) {
        QMessageBox::warning(this, "Hata", "Pencere boyutu 3 ile 21 arasında tek bir sayı olmalıdır.");
        return;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    QImage disparityMap(leftImage.size(), QImage::Format_Grayscale8);
    int maxDisparity = 64;
    
    // Thread'leri temizle ve yeniden başlat
    cleanupThreads();
    initializeThreads();
    
    // Görüntüyü thread'lere böl
    int rowsPerThread = leftImage.height() / numThreads;
    int remainingRows = leftImage.height() % numThreads;
    int currentRow = 0;
    
    for (int i = 0; i < numThreads; ++i) {
        int threadRows = rowsPerThread + (i < remainingRows ? 1 : 0);
        workerThreads.emplace_back(&MainWindow::processDisparityRange, this,
                                 std::ref(leftImage), std::ref(rightImage), std::ref(disparityMap),
                                 currentRow, currentRow + threadRows, windowSize, maxDisparity);
        currentRow += threadRows;
    }
    
    // Thread'lerin tamamlanmasını bekle
    for (auto& thread : workerThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    
    ui->disparityImageLabel->setPixmap(QPixmap::fromImage(disparityMap).scaled(ui->disparityImageLabel->size(), Qt::KeepAspectRatio));
    ui->timeLabel->setText(QString("Hesaplama Süresi: %1 saniye").arg(duration.count(), 0, 'f', 3));

    // Doğruluk ölçümlerini hesapla ve göster
    if (!groundTruthImage.isNull()) {
        double ssdAccuracy = calculateSSDAccuracy(disparityMap, groundTruthImage);
        double sadAccuracy = calculateSADAccuracy(disparityMap, groundTruthImage);
        showAccuracyResults(ssdAccuracy, sadAccuracy);
    }
}

void MainWindow::saveDisparityMap(const QImage& disparityMap)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Disparite Haritasını Kaydet", "", "PNG Dosyası (*.png)");
    if (!fileName.isEmpty()) {
        disparityMap.save(fileName);
    }
}

void MainWindow::on_loadGroundTruth_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Gerçek Derinlik Görüntüsünü Aç", "", "Resim Dosyaları (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        groundTruthImage.load(fileName);
        ui->groundTruthLabel->setPixmap(QPixmap::fromImage(groundTruthImage).scaled(ui->groundTruthLabel->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::on_compareDisparity_clicked() {} // Boş bırak veya tamamen kaldır

double MainWindow::calculateSSDAccuracy(const QImage& computed, const QImage& groundTruth)
{
    double totalError = 0.0;
    int validPixels = 0;
    const double threshold = 3.0; // 3 piksellik bir tolerans
    int matchedPixels = 0;

    for (int y = 0; y < computed.height(); ++y) {
        for (int x = 0; x < computed.width(); ++x) {
            QRgb computedPixel = computed.pixel(x, y);
            QRgb groundTruthPixel = groundTruth.pixel(x, y);

            // Sadece geçerli pikselleri hesapla (0 değerli pikselleri atla)
            if (qRed(groundTruthPixel) > 0) {
                double diff = std::abs(qRed(computedPixel) - qRed(groundTruthPixel));
                if (diff <= threshold) {
                    matchedPixels++;
                }
                validPixels++;
            }
        }
    }

    if (validPixels == 0) return 0.0;
    return (double)matchedPixels / validPixels * 100.0; // Yüzdelik olarak döndür
}

double MainWindow::calculateSADAccuracy(const QImage& computed, const QImage& groundTruth)
{
    double totalError = 0.0;
    int validPixels = 0;
    const double threshold = 3.0; // 3 piksellik bir tolerans
    int matchedPixels = 0;

    for (int y = 0; y < computed.height(); ++y) {
        for (int x = 0; x < computed.width(); ++x) {
            QRgb computedPixel = computed.pixel(x, y);
            QRgb groundTruthPixel = groundTruth.pixel(x, y);

            // Sadece geçerli pikselleri hesapla (0 değerli pikselleri atla)
            if (qRed(groundTruthPixel) > 0) {
                double diff = std::abs(qRed(computedPixel) - qRed(groundTruthPixel));
                if (diff <= threshold) {
                    matchedPixels++;
                }
                validPixels++;
            }
        }
    }

    if (validPixels == 0) return 0.0;
    return (double)matchedPixels / validPixels * 100.0; // Yüzdelik olarak döndür
}

void MainWindow::showAccuracyResults(double ssdAccuracy, double sadAccuracy)
{
    QString message = QString("Doğruluk Sonuçları:\n\n"
                            "SSD Metodu ile %1% eşleşme sağlandı\n"
                            "SAD Metodu ile %2% eşleşme sağlandı\n\n"
                            "(3 piksel tolerans ile hesaplandı)")
                     .arg(ssdAccuracy, 0, 'f', 2)
                     .arg(sadAccuracy, 0, 'f', 2);

    QMessageBox::information(this, "Doğruluk Sonuçları", message);
}
