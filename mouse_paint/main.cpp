#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>

class DrawingWidget : public QWidget {

public:
    DrawingWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Qt 鼠标绘图示例");
        setMinimumSize(800, 600);
    }

protected:
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            drawing = true;
            lastPoint = event->pos();
            points.append(lastPoint);
        }
    }

    // 重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override {
        if ((event->buttons() & Qt::LeftButton) && drawing) {
            QPoint currentPoint = event->pos();
            points.append(currentPoint);
            lastPoint = currentPoint;
            update(); // 触发重绘
        }
    }

    // 重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton && drawing) {
            drawing = false;
            points.append(event->pos());
            update(); // 触发重绘
        }
    }

    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 开启抗锯齿
        painter.setPen(QPen(Qt::blue, 2)); // 设置画笔颜色和宽度

        // 绘制所有点
        for (int i = 1; i < points.size(); ++i) {
            painter.drawLine(points[i - 1], points[i]);
        }
    }

private:
    bool drawing = false; // 是否正在绘图
    QPoint lastPoint; // 上一个点
    QVector<QPoint> points; // 存储所有点
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DrawingWidget window;
    window.show();
    return app.exec();
}
