#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *window = new QWidget();
    window->setWindowTitle("QLabel Example");
    window->setMinimumSize(500,500);
    QLabel *label1 = new QLabel(window);
    label1->setText("<b>Hello, World!</b>"); // 设置加粗文本
    label1->setAlignment(Qt::AlignCenter); // 居中对齐

    label1->setWordWrap(true); // 自动换行
    QLabel *label2 = new QLabel(window);
    label2->setPixmap(QPixmap("/Qtproject/Qlinetext/pikaqiu.jpeg")); // 显示图像
    QVBoxLayout *layout = new QVBoxLayout(window);

    layout->addWidget(label1);
    layout->addWidget(label2);
    window->setLayout(layout);
    window->show();
    return app.exec();
}

