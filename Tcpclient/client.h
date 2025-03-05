#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class Client : public QWidget
{

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void onConnect();
    void onReadyRead();
    void onSendData();
    void onEmojiButtonClicked();
    void onInsertImage(); // 添加插入图片的槽函数
    void openUrl();
    void startGame();
    void startblockGame();


private:
    QTcpSocket *socket;
    QTextEdit *log;
    QTextEdit *inputArea;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QLineEdit *inputLine;
    QPushButton *emojiButton;
    QPushButton *imageButton; // 添加插入图片按钮
    QPushButton *imageButton2;
    QPushButton *snakegameButton;
    QPushButton *breakoutgameButton;
    QLineEdit *urlLineEdit;



};

#endif // CLIENT_H
