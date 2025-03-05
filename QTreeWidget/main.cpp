#include "widget.h"

#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QVBoxLayout *layout = new QVBoxLayout();

    QTreeWidget *treeWidget = new QTreeWidget();
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, "Root Node");

    QTreeWidgetItem *childItem = new QTreeWidgetItem(rootItem);
    childItem->setText(0, "Child Node");

    treeWidget->addTopLevelItem(rootItem);
    layout->addWidget(treeWidget);
    w.setLayout(layout);
    w.adjustSize();


    w.show();
    return a.exec();
}
