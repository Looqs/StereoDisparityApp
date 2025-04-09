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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnLoadImages;
    QPushButton *btnCompute;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelLeft;
    QLabel *labelRight;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineWindowSize;
    QComboBox *comboMethod;
    QLabel *labelOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnLoadImages = new QPushButton(centralwidget);
        btnLoadImages->setObjectName("btnLoadImages");

        horizontalLayout->addWidget(btnLoadImages);

        btnCompute = new QPushButton(centralwidget);
        btnCompute->setObjectName("btnCompute");

        horizontalLayout->addWidget(btnCompute);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelLeft = new QLabel(centralwidget);
        labelLeft->setObjectName("labelLeft");
        labelLeft->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelLeft);

        labelRight = new QLabel(centralwidget);
        labelRight->setObjectName("labelRight");
        labelRight->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelRight);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        lineWindowSize = new QLineEdit(centralwidget);
        lineWindowSize->setObjectName("lineWindowSize");

        horizontalLayout_3->addWidget(lineWindowSize);

        comboMethod = new QComboBox(centralwidget);
        comboMethod->addItem(QString());
        comboMethod->addItem(QString());
        comboMethod->addItem(QString());
        comboMethod->setObjectName("comboMethod");

        horizontalLayout_3->addWidget(comboMethod);


        verticalLayout->addLayout(horizontalLayout_3);

        labelOutput = new QLabel(centralwidget);
        labelOutput->setObjectName("labelOutput");
        labelOutput->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelOutput);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Stereo Disparity App", nullptr));
        btnLoadImages->setText(QCoreApplication::translate("MainWindow", "Load Images", nullptr));
        btnCompute->setText(QCoreApplication::translate("MainWindow", "Compute Disparity", nullptr));
        labelLeft->setText(QCoreApplication::translate("MainWindow", "Left Image", nullptr));
        labelRight->setText(QCoreApplication::translate("MainWindow", "Right Image", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Window Size:", nullptr));
        lineWindowSize->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        comboMethod->setItemText(0, QCoreApplication::translate("MainWindow", "SAD", nullptr));
        comboMethod->setItemText(1, QCoreApplication::translate("MainWindow", "SSD", nullptr));
        comboMethod->setItemText(2, QCoreApplication::translate("MainWindow", "ZNCC", nullptr));

        labelOutput->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
