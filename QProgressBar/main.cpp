#include "widget.h"
#include <QApplication>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setRange(0, 100); // 设置范围为 0 到 100
    progressBar->setValue(0); // 初始值为 0

    QTimer *timer = new QTimer();
    timer->start(1000); // 每秒更新一次进度
    QObject::connect(timer, &QTimer::timeout, [=]() {
    int value = progressBar->value();
    if (value < 100) {
        progressBar->setValue(value + 1);
    } else {
        timer->stop();
    }
});

    layout->addWidget(progressBar);
    w.setLayout(layout);
    w.adjustSize();





    w.show();
    return a.exec();
}
