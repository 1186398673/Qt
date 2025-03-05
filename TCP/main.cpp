#include "widget.h"
#include "server.h"
#include <QApplication>
#include "client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    Server b;
    b.show();






    return a.exec();
}
