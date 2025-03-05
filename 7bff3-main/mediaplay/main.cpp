#include "mediaplay.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mediaplay w;
    w.setWindowTitle("万能播放器");
    w.setWindowIcon(QIcon(":/widgeticon.jpg"));
    w.show();

    return a.exec();
}
