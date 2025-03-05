#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QPushButton *button1 = new QPushButton("Button 1");
    QObject::connect(button1, &QPushButton::clicked, [=]() {
        qInfo() << "Button1 Clicked!";
    });
    QPushButton *button2 = new QPushButton("Button 2");
    QObject::connect(button2, &QPushButton::clicked, [=]() {
        qInfo() << "Button2 Clicked!";
    });

    layout->addWidget(button1);
    layout->addWidget(button2);

    widget->setLayout(layout);
    widget->show();

    return app.exec();
}
