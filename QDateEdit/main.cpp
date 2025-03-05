#include "widget.h"
#include <QApplication>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QDateEdit *dateEdit = new QDateEdit();
    dateEdit->setDateRange(QDate(2000, 1, 1), QDate(2100, 12, 31)); // 设置日期范围
    dateEdit->setDate(QDate::currentDate()); // 设置默认日期为当前日期
     QObject::connect(dateEdit, &QDateEdit::dateChanged, [=](const QDate &date) {
        qInfo() << "Selected date:" << date.toString();
    });
    layout->addWidget(dateEdit);
    w.setLayout(layout);
    w.adjustSize();
    w.show();
    return a.exec();
}
