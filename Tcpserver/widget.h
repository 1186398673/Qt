#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
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

private slots:
    void on_openButton_clicked();

    void on_closeButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    void newconection_slot();
    void readyread_slot();
};
#endif // WIDGET_H
