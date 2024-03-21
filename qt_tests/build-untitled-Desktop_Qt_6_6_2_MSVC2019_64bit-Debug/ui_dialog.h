/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButtonMain;
    QLabel *label_image;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_name;
    QLabel *label_text;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(792, 517);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images_ecole/mission.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        pushButtonMain = new QPushButton(Dialog);
        pushButtonMain->setObjectName("pushButtonMain");
        pushButtonMain->setGeometry(QRect(690, 20, 80, 29));
        label_image = new QLabel(Dialog);
        label_image->setObjectName("label_image");
        label_image->setGeometry(QRect(12, 314, 221, 191));
        label_image->setPixmap(QPixmap(QString::fromUtf8(":/images_ecole/serge.png")));
        label_image->setScaledContents(true);
        widget = new QWidget(Dialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(250, 310, 531, 191));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_name = new QLabel(widget);
        label_name->setObjectName("label_name");
        QFont font;
        font.setFamilies({QString::fromUtf8("Lucida Handwriting")});
        font.setPointSize(20);
        label_name->setFont(font);

        verticalLayout->addWidget(label_name);

        label_text = new QLabel(widget);
        label_text->setObjectName("label_text");
        QFont font1;
        font1.setPointSize(12);
        label_text->setFont(font1);
        label_text->setScaledContents(false);
        label_text->setWordWrap(true);

        verticalLayout->addWidget(label_text);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Les missions de Serge", nullptr));
        pushButtonMain->setText(QCoreApplication::translate("Dialog", "Main", nullptr));
        label_image->setText(QString());
        label_name->setText(QCoreApplication::translate("Dialog", "Serge (technicien)", nullptr));
        label_text->setText(QCoreApplication::translate("Dialog", "Vous me devez 1000$, petits.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
