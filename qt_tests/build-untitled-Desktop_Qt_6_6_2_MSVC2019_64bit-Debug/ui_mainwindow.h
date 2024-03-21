/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
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
    QLabel *label;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonRight;
    QPushButton *pushButtonLeft;
    QPushButton *pushButtonQuit;
    QPushButton *pushButtonDialog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(879, 644);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images_ecole/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(21, 11, 841, 591));
        label->setScaledContents(true);
        pushButtonDown = new QPushButton(centralwidget);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(400, 550, 83, 29));
        pushButtonUp = new QPushButton(centralwidget);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(390, 10, 83, 29));
        pushButtonRight = new QPushButton(centralwidget);
        pushButtonRight->setObjectName("pushButtonRight");
        pushButtonRight->setGeometry(QRect(780, 280, 83, 29));
        pushButtonLeft = new QPushButton(centralwidget);
        pushButtonLeft->setObjectName("pushButtonLeft");
        pushButtonLeft->setGeometry(QRect(10, 280, 83, 29));
        pushButtonQuit = new QPushButton(centralwidget);
        pushButtonQuit->setObjectName("pushButtonQuit");
        pushButtonQuit->setGeometry(QRect(770, 10, 83, 29));
        pushButtonDialog = new QPushButton(centralwidget);
        pushButtonDialog->setObjectName("pushButtonDialog");
        pushButtonDialog->setGeometry(QRect(770, 550, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 879, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Carte", nullptr));
        label->setText(QString());
        pushButtonDown->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        pushButtonRight->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        pushButtonLeft->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        pushButtonQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        pushButtonDialog->setText(QCoreApplication::translate("MainWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
