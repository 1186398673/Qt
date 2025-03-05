#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 设置窗口大小
        this->resize(400, 300);
    }

protected:
    // 重写鼠标按下事件处理器
    void mousePressEvent(QMouseEvent *event) override {
        // 获取鼠标点击的坐标
        int x = event->x();
        int y = event->y();

        // 获取鼠标按钮类型
        Qt::MouseButton button = event->button();

        // 输出点击信息
        qDebug() << "鼠标按下: (" << x << ", " << y << ") 按键: " << button;

        // 调用基类方法以确保默认行为（如事件传播）不被中断
        QWidget::mousePressEvent(event);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
