#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
     QPushButton btn;
     btn.setText("btn1");
     btn.resize(300,300);
     btn.show();
    // QPushButton的默认信号（clicked）与槽的连接
    QPushButton *button = new QPushButton("Click Me",&btn);
    QObject::connect(button, &QPushButton::clicked, [=]() {
        qInfo() << "Button Clicked!";
    });

    // QLineEdit的默认信号（textChanged）与槽的连接
    QLineEdit *lineEdit = new QLineEdit(&btn);
    lineEdit->move(100,100);
    QObject::connect(lineEdit, &QLineEdit::textChanged, [=](const QString &text) {
        qInfo() << "Text Changed: " << text;
    });

    // 显示窗口
    button->show();
    lineEdit->show();

    return app.exec();
}
