#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    // 重写键盘按下事件处理器
    void keyPressEvent(QKeyEvent *event) override {
        // 获取按键的文本
        QString keyText = event->text();
        // 获取按键的键值
        int keyCode = event->key();
        // 输出按键信息
        qDebug() << "按键按下: " << keyText << " (键值: " << keyCode << ")";
        // 调用基类处理其他逻辑
        QWidget::keyPressEvent(event);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.resize(300, 200);
    widget.show();
    return app.exec();
}
