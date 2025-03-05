#include <QApplication>
#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QSpinBox Example");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QSpinBox *spinBox = new QSpinBox(&window);
    spinBox->setRange(0, 100); // 设置范围为 0 到 100
    spinBox->setSingleStep(1); // 步长为 1

    layout->addWidget(spinBox);
    window.setLayout(layout);

    window.show();
    return app.exec();
}

