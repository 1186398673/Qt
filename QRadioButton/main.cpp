#include "widget.h"
#include <QApplication>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();
    QRadioButton *radioButton1 = new QRadioButton("Option 1");
    QRadioButton *radioButton2 = new QRadioButton("Option 2");
      QObject::connect(radioButton1, &QRadioButton::clicked, [=](bool checked) {
        if (checked) {
            qInfo() << "Option 1 enabled";
        }
    });
    QObject::connect(radioButton2, &QRadioButton::clicked, [=](bool checked) {
        if (checked) {
            qInfo() << "Option 2 enabled";
        }
    });

    layout->addWidget(radioButton1);
    layout->addWidget(radioButton2);
    w.setLayout(layout);
    w.adjustSize();




    w.show();
    return a.exec();
}
