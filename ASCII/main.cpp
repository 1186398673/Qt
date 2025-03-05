#include "widget.h"

#include <QApplication>
#include "AsciiArtConverter.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //w.show();
    AsciiArtConverter c;




    return a.exec();
}
