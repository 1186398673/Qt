#include "widget.h"
#include <QApplication>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QListWidget *listWidget = new QListWidget();

    QListWidgetItem *item1 = new QListWidgetItem("Item 1");
    QListWidgetItem *item2 = new QListWidgetItem("Item 2");

    listWidget->addItem(item1);
    listWidget->addItem(item2);
    layout->addWidget(listWidget);


    w.setLayout(layout);
    w.adjustSize();




    w.show();
    return a.exec();
}
