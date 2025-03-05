#include "widget.h"
#include <QApplication>
#include "server.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Server b;
    b.show();



    return a.exec();
}
