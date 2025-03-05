#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void timeout_slot();

private slots:
    void on_startButton_clicked();

    void on_closeButton_clicked();

    void on_resetButton_clicked();

    void on_markButton_clicked();

private:
    Ui::Widget *ui;
    QTimer  timer;
    QTime time;
};
#endif // WIDGET_H
