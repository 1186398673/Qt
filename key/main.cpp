#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class CustomWidget : public QWidget {
public:
    CustomWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    bool event(QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                qDebug() << "Left mouse button pressed at (" << mouseEvent->x() << ", " << mouseEvent->y() << ")";
                return true; // 表示事件已被处理
            }
        }
        return QWidget::event(event); // 返回false表示事件未被处理，继续传递
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.setWindowTitle("Event Dispatching Example");
    widget.setGeometry(100, 100, 300, 200);
    widget.show();

    return app.exec();
}
