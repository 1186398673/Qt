/********************************************************************************
** Form generated from reading UI file 'form1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM1_H
#define UI_FORM1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form1
{
public:
    QPushButton *dateButton;
    QPushButton *SceenButton;
    QPushButton *panelButton;
    QPushButton *alarmButton;
    QPushButton *backButton;

    void setupUi(QWidget *Form1)
    {
        if (Form1->objectName().isEmpty())
            Form1->setObjectName("Form1");
        Form1->resize(600, 400);
        dateButton = new QPushButton(Form1);
        dateButton->setObjectName("dateButton");
        dateButton->setGeometry(QRect(90, 120, 50, 40));
        dateButton->setStyleSheet(QString::fromUtf8("border-image: url(:/class2/date.png);"));
        SceenButton = new QPushButton(Form1);
        SceenButton->setObjectName("SceenButton");
        SceenButton->setGeometry(QRect(170, 120, 50, 40));
        SceenButton->setStyleSheet(QString::fromUtf8("border-image: url(:/class2/screen.png);"));
        panelButton = new QPushButton(Form1);
        panelButton->setObjectName("panelButton");
        panelButton->setGeometry(QRect(250, 120, 50, 40));
        panelButton->setStyleSheet(QString::fromUtf8("border-image: url(:/class2/digital.png);"));
        alarmButton = new QPushButton(Form1);
        alarmButton->setObjectName("alarmButton");
        alarmButton->setGeometry(QRect(330, 120, 50, 40));
        alarmButton->setStyleSheet(QString::fromUtf8("border-image: url(:/class2/bg4.png);"));
        backButton = new QPushButton(Form1);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(430, 120, 50, 40));
        backButton->setStyleSheet(QString::fromUtf8("border-image: url(:/class2/back.png);"));

        retranslateUi(Form1);

        QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(QWidget *Form1)
    {
        Form1->setWindowTitle(QCoreApplication::translate("Form1", "Form", nullptr));
        dateButton->setText(QString());
        SceenButton->setText(QString());
        panelButton->setText(QString());
        alarmButton->setText(QString());
        backButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM1_H
