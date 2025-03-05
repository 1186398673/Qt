#include "widget.h"
#include <QApplication>
#include <QSlider>
#include <QVBoxLayout>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setSingleStep(1);
    QObject::connect(slider, &QSlider::valueChanged, [=](int value) {
    qInfo() << "Slider value:" << value;
     });

    layout->addWidget(slider);
    w.setLayout(layout);
    w.adjustSize();
    w.show();
    return a.exec();
}
