#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

// 自定义事件过滤器类
class MyEventFilter : public QObject {

public:
    MyEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    // 重写 eventFilter 方法
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "事件过滤器捕捉到按键按下: " << keyEvent->text() << " (键值: " << keyEvent->key() << ")";
            // 如果需要，可以选择是否阻止事件传递到目标对象
            // return true; // 阻止事件传递
        }
        // 其他事件继续传递
        return QObject::eventFilter(obj, event);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(300, 200);

    QLineEdit lineEdit(&window);
    lineEdit.setPlaceholderText("输入文本");
    lineEdit.move(50, 80);

    // 创建事件过滤器实例
    MyEventFilter *filter = new MyEventFilter(&window);
    // 将事件过滤器安装到 QLineEdit 对象上
    lineEdit.installEventFilter(filter);

    window.show();
    return app.exec();
}

