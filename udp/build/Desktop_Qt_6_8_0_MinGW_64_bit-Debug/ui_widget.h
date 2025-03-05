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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox;
    QPlainTextEdit *recvTextEdit;
    QLineEdit *objectEdit;
    QLineEdit *objectipEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *sendButton;
    QGroupBox *groupBox_2;
    QLineEdit *sendEdit;
    QLineEdit *localEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(230, 20, 381, 201));
        recvTextEdit = new QPlainTextEdit(groupBox);
        recvTextEdit->setObjectName("recvTextEdit");
        recvTextEdit->setGeometry(QRect(10, 20, 361, 171));
        objectEdit = new QLineEdit(Widget);
        objectEdit->setObjectName("objectEdit");
        objectEdit->setGeometry(QRect(500, 260, 113, 21));
        objectipEdit = new QLineEdit(Widget);
        objectipEdit->setObjectName("objectipEdit");
        objectipEdit->setGeometry(QRect(270, 300, 113, 21));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 260, 53, 15));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(420, 260, 53, 15));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(210, 300, 53, 15));
        openButton = new QPushButton(Widget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(240, 390, 75, 23));
        closeButton = new QPushButton(Widget);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(390, 390, 75, 23));
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(540, 390, 75, 23));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(240, 330, 401, 51));
        sendEdit = new QLineEdit(groupBox_2);
        sendEdit->setObjectName("sendEdit");
        sendEdit->setGeometry(QRect(10, 20, 381, 21));
        localEdit = new QLineEdit(Widget);
        localEdit->setObjectName("localEdit");
        localEdit->setGeometry(QRect(270, 250, 101, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\216\245\346\224\266\346\241\206", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\234\254\345\234\260\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\347\233\256\346\240\207\347\253\257\345\217\243", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\347\233\256\346\240\207IP", nullptr));
        openButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        closeButton->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        sendButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\346\241\206", nullptr));
        localEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
