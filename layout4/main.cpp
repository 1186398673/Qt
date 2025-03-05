#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *widget = new QWidget();
    QStackedLayout *layout = new QStackedLayout(widget);

    QPushButton *button1 = new QPushButton("Page 1");
    QPushButton *button2 = new QPushButton("Page 2");
    QPushButton *button3 = new QPushButton("Page 3");

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    layout->setCurrentIndex(2); // 初始显示第三个窗口部件

    widget->setLayout(layout);
    widget->show();

    return app.exec();
}
