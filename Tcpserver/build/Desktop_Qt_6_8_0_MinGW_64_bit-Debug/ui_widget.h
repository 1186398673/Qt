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
    QLineEdit *numberEdit;
    QLabel *label;
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *sendButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        recvTextEdit = new QPlainTextEdit(Widget);
        recvTextEdit->setObjectName("recvTextEdit");
        recvTextEdit->setGeometry(QRect(130, 10, 471, 271));
        numberEdit = new QLineEdit(Widget);
        numberEdit->setObjectName("numberEdit");
        numberEdit->setGeometry(QRect(200, 290, 121, 31));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 300, 53, 15));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        openButton = new QPushButton(Widget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(140, 400, 75, 23));
        closeButton = new QPushButton(Widget);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(310, 400, 75, 23));
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(520, 400, 75, 23));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(150, 340, 441, 31));

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
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
