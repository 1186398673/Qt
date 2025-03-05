#include <QApplication>
#include <QWidget>
#include <QLineEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QLineEdit Example");
    window.setMinimumSize(500,500);
    QLineEdit *lineEdit = new QLineEdit(&window);
    lineEdit->setPlaceholderText("Enter your text here"); // 占位符文本
    lineEdit->setMaxLength(10); // 最多输入10个字符

    window.show();
    return app.exec();
}

