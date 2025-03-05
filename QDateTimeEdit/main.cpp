#include "widget.h"
#include <QApplication>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit();
    dateTimeEdit->setDateRange(QDate(2000, 1, 1), QDate(2100, 12, 31)); // 设置日期范围
    dateTimeEdit->setTimeRange(QTime(0, 0, 0), QTime(23, 59, 59)); // 设置时间范围
    dateTimeEdit->setDateTime(QDateTime::currentDateTime()); // 设置默认日期和时间为当前日期和时间
    QObject::connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, [=](const QDateTime &dateTime) {
        qInfo() << "Selected date and time:" << dateTime.toString();
        // 执行其他操作
    });

    layout->addWidget(dateTimeEdit);
    w.setLayout(layout);
    w.adjustSize();






    w.show();
    return a.exec();
}
