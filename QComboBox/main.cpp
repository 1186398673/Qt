#include <QApplication>
#include "widget.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>





int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout(&w);
    QComboBox *comboBox = new QComboBox(&w);
    comboBox->addItem("Option 1");
    comboBox->addItem("Option 2");
    comboBox->addItem("Option 3");





     QObject::connect(comboBox, &QComboBox::currentTextChanged, [=](const QString &text) {
    qInfo() << "Selected Option:" << text;
   });


    layout->addWidget(comboBox);
    w.setLayout(layout);
     w.adjustSize();

    w.setWindowTitle("QComboBox Example");
    w.show();

    return app.exec();
}

