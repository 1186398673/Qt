#include "widget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QPushButton btn;
    QString text="第一个项目";
    btn.setText("btn1");
    btn.setParent(&w);
    btn.show();
    QPushButton btn2("btn2",&w);
    btn2.move(100,100);
    btn2.resize(300,300);
    QPushButton btn3("btn3",&btn2);
    w.setWindowTitle(text);
    w.setFixedSize(600,400);

    w.show();



    return a.exec();
}
