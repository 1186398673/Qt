#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 设置窗口大小
        this->resize(400, 300);
    }

protected:
    // 重写绘制事件处理器
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event); // 标记未使用的参数

        QPainter painter(this); // 创建 QPainter 对象，关联到当前窗口

        // 设置绘制颜色为红色
        painter.setBrush(QBrush(Qt::red));
        painter.setPen(QPen(Qt::black, 2)); // 设置边框颜色为黑色，线宽为2

        // 绘制一个圆形
        painter.drawEllipse(100, 100, 200, 100); // (x, y, width, height)
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
