
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
    void onEmojiButtonClicked(); // 添加表情选择器槽函数
    void onInsertImage(); // 添加插入图片的槽函数

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QTextEdit *log;
    QPushButton *startButton;
    QPushButton *sendButton;
    QTextEdit *inputArea;
    QPushButton *emojiButton; // 添加表情选择器按钮
    QPushButton *imageButton;
};

#endif // SERVER_H
