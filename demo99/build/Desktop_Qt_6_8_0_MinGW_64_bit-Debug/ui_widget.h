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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *NumberEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *PasswordEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *logoinButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(600, 400);
        Widget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer = new QSpacerItem(20, 137, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(180, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(Widget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        NumberEdit = new QLineEdit(Widget);
        NumberEdit->setObjectName("NumberEdit");
        NumberEdit->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(NumberEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        PasswordEdit = new QLineEdit(Widget);
        PasswordEdit->setObjectName("PasswordEdit");
        PasswordEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        PasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(PasswordEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        registerButton = new QPushButton(Widget);
        registerButton->setObjectName("registerButton");
        registerButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(registerButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        logoinButton = new QPushButton(Widget);
        logoinButton->setObjectName("logoinButton");
        logoinButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(logoinButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(179, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 136, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "QQ\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        registerButton->setText(QCoreApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
        logoinButton->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
