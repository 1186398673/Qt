#include <QApplication>
#include <QWidget>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QDoubleSpinBox Example");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(&window);
    doubleSpinBox->setRange(0.0, 100.0); // 设置范围为 0 到 100
    doubleSpinBox->setSingleStep(0.1); // 步长为 0.1
    doubleSpinBox->setDecimals(2); // 小数点后保留两位

    layout->addWidget(doubleSpinBox);
    window.setLayout(layout);

    window.show();
    return app.exec();
}
