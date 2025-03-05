#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *widget = new QWidget();
    QFormLayout *layout = new QFormLayout(widget);

    QLabel *label1 = new QLabel("Label 1:");
    QLineEdit *lineEdit1 = new QLineEdit();

    QLabel *label2 = new QLabel("Label 2:");
    QLineEdit *lineEdit2 = new QLineEdit();

    layout->addRow(label1, lineEdit1);
    layout->addRow(label2, lineEdit2);

    widget->setLayout(layout);
    widget->show();

    return app.exec();
}
