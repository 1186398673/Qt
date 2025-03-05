#include "widget.h"
#include <QApplication>
#include <QTimeEdit>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QTimeEdit *timeEdit = new QTimeEdit();
    timeEdit->setTimeRange(QTime(0, 0, 0), QTime(23, 59, 59));
    timeEdit->setTime(QTime::currentTime());
   QObject::connect(timeEdit, &QTimeEdit::timeChanged, [=](const QTime &time) {
        qInfo() << "Selected time:" << time.toString();
    });


    layout->addWidget(timeEdit);
    w.setLayout(layout);





    w.show();
    return a.exec();
}
