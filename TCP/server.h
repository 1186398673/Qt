#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>

class Server : public QWidget
{

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void onStartServer();
    void onNewConnection();
    void onReadyRead();
    void onSendData();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QTextEdit *log;
    QPushButton *startButton;
    QPushButton *sendButton;
};

#endif // SERVER_H
