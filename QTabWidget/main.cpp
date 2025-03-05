#include "widget.h"
#include <QApplication>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QTabWidget *tabWidget = new QTabWidget();

    QWidget *page1 = new QWidget();
    QLabel *label1 = new QLabel("Content of Tab 1", page1);
    QVBoxLayout *page1Layout = new QVBoxLayout(page1);
    page1Layout->addWidget(label1);
    page1->setLayout(page1Layout);
    tabWidget->addTab(page1, "Tab 1");

    QWidget *page2 = new QWidget();
    QLabel *label2 = new QLabel("Content of Tab 2", page2);
    QVBoxLayout *page2Layout = new QVBoxLayout(page2);
    page2Layout->addWidget(label2);
    page2->setLayout(page2Layout);
    tabWidget->addTab(page2, "Tab 2");

    layout->addWidget(tabWidget);
    w.setLayout(layout);
    w.adjustSize();



    w.show();
    return a.exec();
}
