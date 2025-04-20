/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *leftImageLabel;
    QLabel *rightImageLabel;
    QLabel *disparityImageLabel;
    QLabel *groundTruthLabel;
    QPushButton *loadLeftImage;
    QPushButton *loadRightImage;
    QPushButton *calculateDisparity;
    QPushButton *loadGroundTruth;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *methodComboBox;
    QLabel *label_2;
    QLineEdit *windowSizeEdit;
    QLabel *timeLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        leftImageLabel = new QLabel(centralwidget);
        leftImageLabel->setObjectName("leftImageLabel");
        leftImageLabel->setMinimumSize(QSize(400, 300));
        leftImageLabel->setFrameShape(QFrame::Box);
        leftImageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leftImageLabel, 0, 0, 1, 1);

        rightImageLabel = new QLabel(centralwidget);
        rightImageLabel->setObjectName("rightImageLabel");
        rightImageLabel->setMinimumSize(QSize(400, 300));
        rightImageLabel->setFrameShape(QFrame::Box);
        rightImageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(rightImageLabel, 0, 1, 1, 1);

        disparityImageLabel = new QLabel(centralwidget);
        disparityImageLabel->setObjectName("disparityImageLabel");
        disparityImageLabel->setMinimumSize(QSize(400, 300));
        disparityImageLabel->setFrameShape(QFrame::Box);
        disparityImageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(disparityImageLabel, 0, 2, 1, 1);

        groundTruthLabel = new QLabel(centralwidget);
        groundTruthLabel->setObjectName("groundTruthLabel");
        groundTruthLabel->setMinimumSize(QSize(400, 300));
        groundTruthLabel->setFrameShape(QFrame::Box);
        groundTruthLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(groundTruthLabel, 0, 3, 1, 1);

        loadLeftImage = new QPushButton(centralwidget);
        loadLeftImage->setObjectName("loadLeftImage");

        gridLayout->addWidget(loadLeftImage, 1, 0, 1, 1);

        loadRightImage = new QPushButton(centralwidget);
        loadRightImage->setObjectName("loadRightImage");

        gridLayout->addWidget(loadRightImage, 1, 1, 1, 1);

        calculateDisparity = new QPushButton(centralwidget);
        calculateDisparity->setObjectName("calculateDisparity");

        gridLayout->addWidget(calculateDisparity, 1, 2, 1, 1);

        loadGroundTruth = new QPushButton(centralwidget);
        loadGroundTruth->setObjectName("loadGroundTruth");

        gridLayout->addWidget(loadGroundTruth, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        methodComboBox = new QComboBox(centralwidget);
        methodComboBox->setObjectName("methodComboBox");

        horizontalLayout->addWidget(methodComboBox);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        windowSizeEdit = new QLineEdit(centralwidget);
        windowSizeEdit->setObjectName("windowSizeEdit");

        horizontalLayout->addWidget(windowSizeEdit);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName("timeLabel");

        horizontalLayout->addWidget(timeLabel);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Stereo G\303\266r\303\274nt\303\274 \304\260\305\237leme", nullptr));
        leftImageLabel->setText(QCoreApplication::translate("MainWindow", "Sol G\303\266r\303\274nt\303\274", nullptr));
        rightImageLabel->setText(QCoreApplication::translate("MainWindow", "Sa\304\237 G\303\266r\303\274nt\303\274", nullptr));
        disparityImageLabel->setText(QCoreApplication::translate("MainWindow", "Disparite Haritas\304\261", nullptr));
        groundTruthLabel->setText(QCoreApplication::translate("MainWindow", "Ger\303\247ek Derinlik", nullptr));
        loadLeftImage->setText(QCoreApplication::translate("MainWindow", "Sol G\303\266r\303\274nt\303\274y\303\274 Y\303\274kle", nullptr));
        loadRightImage->setText(QCoreApplication::translate("MainWindow", "Sa\304\237 G\303\266r\303\274nt\303\274y\303\274 Y\303\274kle", nullptr));
        calculateDisparity->setText(QCoreApplication::translate("MainWindow", "Disparite Hesapla", nullptr));
        loadGroundTruth->setText(QCoreApplication::translate("MainWindow", "Ger\303\247ek Derinli\304\237i Y\303\274kle", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Y\303\266ntem:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Pencere Boyutu:", nullptr));
        windowSizeEdit->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "Hesaplama S\303\274resi: -", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
