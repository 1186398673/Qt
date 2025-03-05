#include <QApplication>
#include "widget.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>










int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();
    QCheckBox *checkBox = new QCheckBox("Enable Option");

    QObject::connect(checkBox, &QCheckBox::clicked, [=](bool checked) {
        if (checked) {
            qInfo() << "Option enabled";
        } else {
            qInfo() << "Option disabled";
        }
    });

    layout->addWidget(checkBox);
    w.setLayout(layout);
    w.adjustSize();

    w.setWindowTitle("QCheckBox Example");
    w.show();

    return app.exec();
}

