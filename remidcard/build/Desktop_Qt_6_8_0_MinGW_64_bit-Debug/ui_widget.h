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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *addButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label;
    QLineEdit *collegeEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        addButton = new QPushButton(Widget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(50, 20, 75, 23));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(200, 20, 75, 23));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(340, 20, 75, 23));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(480, 20, 75, 23));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(630, 20, 75, 23));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 60, 121, 31));
        collegeEdit = new QLineEdit(Widget);
        collegeEdit->setObjectName("collegeEdit");
        collegeEdit->setGeometry(QRect(160, 60, 191, 31));
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 110, 731, 321));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(widget);
        listView->setObjectName("listView");

        horizontalLayout->addWidget(listView);

        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName("plainTextEdit");

        horizontalLayout->addWidget(plainTextEdit);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        addButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\346\225\260\346\215\256\351\241\271", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\346\225\260\346\215\256\351\241\271", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\217\222\345\205\245\346\225\260\346\215\256\351\241\271", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\225\260\346\215\256\351\241\271", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "\345\261\225\347\244\272\346\225\260\346\215\256\351\241\271", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\257\267\350\276\223\345\205\245\345\244\247\345\255\246\347\232\204\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
