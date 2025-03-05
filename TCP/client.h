#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>

class Client : public QWidget
{

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void onConnect();
    void onReadyRead();
    void onSendData();

private:
    QTcpSocket *socket;
    QTextEdit *log;
    QPushButton *connectButton;
    QPushButton *sendButton;
};

#endif // CLIENT_H
