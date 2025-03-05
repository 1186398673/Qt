/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *recvTextEdit;
    QLabel *label;
    QLineEdit *numberEdit;
    QLineEdit *sendEdit;
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *sendButton;
    QLabel *label_2;
    QLineEdit *ipEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        recvTextEdit = new QPlainTextEdit(Widget);
        recvTextEdit->setObjectName("recvTextEdit");
        recvTextEdit->setGeometry(QRect(160, 10, 481, 231));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 270, 53, 15));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        numberEdit = new QLineEdit(Widget);
        numberEdit->setObjectName("numberEdit");
        numberEdit->setGeometry(QRect(240, 260, 151, 31));
        sendEdit = new QLineEdit(Widget);
        sendEdit->setObjectName("sendEdit");
        sendEdit->setGeometry(QRect(180, 320, 461, 31));
        openButton = new QPushButton(Widget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(180, 370, 75, 23));
        closeButton = new QPushButton(Widget);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(380, 370, 75, 23));
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(570, 370, 75, 23));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(480, 270, 53, 15));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ipEdit = new QLineEdit(Widget);
        ipEdit->setObjectName("ipEdit");
        ipEdit->setGeometry(QRect(540, 260, 151, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", nullptr));
        openButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\234\215\345\212\241\347\253\257", nullptr));
        closeButton->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\346\234\215\345\212\241\347\253\257", nullptr));
        sendButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "IP\345\234\260\345\235\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
