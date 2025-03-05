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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QTextBrowser *recvtextBrowser;
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *resetButton;
    QPushButton *markButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 40, 351, 71));
        QFont font;
        font.setPointSize(27);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        recvtextBrowser = new QTextBrowser(Widget);
        recvtextBrowser->setObjectName("recvtextBrowser");
        recvtextBrowser->setGeometry(QRect(140, 200, 371, 231));
        startButton = new QPushButton(Widget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(140, 150, 75, 23));
        closeButton = new QPushButton(Widget);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(230, 150, 75, 23));
        resetButton = new QPushButton(Widget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(330, 150, 75, 23));
        markButton = new QPushButton(Widget);
        markButton->setObjectName("markButton");
        markButton->setGeometry(QRect(430, 150, 75, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        startButton->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        closeButton->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        resetButton->setText(QCoreApplication::translate("Widget", "\351\207\215\347\275\256", nullptr));
        markButton->setText(QCoreApplication::translate("Widget", "\346\211\223\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
