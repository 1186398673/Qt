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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *edictButton;
    QPushButton *saveButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(903, 827);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 70, 351, 481));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 341, 471));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(widget);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout->addWidget(deleteButton);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(440, 70, 351, 481));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 341, 471));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(layoutWidget);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_2->addWidget(plainTextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        edictButton = new QPushButton(layoutWidget);
        edictButton->setObjectName("edictButton");

        horizontalLayout_2->addWidget(edictButton);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");

        horizontalLayout_2->addWidget(saveButton);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName("exitButton");

        horizontalLayout_2->addWidget(exitButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox_2->raise();
        groupBox->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QString());
        addButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\345\215\241\347\211\207", nullptr));
        deleteButton->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\345\215\241\347\211\207", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\345\215\241\347\211\207", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\257\274\345\205\245\345\215\241\347\211\207", nullptr));
        groupBox_2->setTitle(QString());
        edictButton->setText(QCoreApplication::translate("Widget", "\347\274\226\350\276\221", nullptr));
        saveButton->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        exitButton->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
