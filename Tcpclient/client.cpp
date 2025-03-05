#include "client.h"
#include "SnakeGame.h"
#include "Breakout.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextDocument>
#include <QInputDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QUrl>
#include <QDesktopServices>
#include <QApplication>

Client::Client(QWidget *parent)
    : QWidget(parent), socket(new QTcpSocket(this))
{
    log = new QTextEdit;
    log->setReadOnly(true);

    inputArea = new QTextEdit;
    inputArea->setPlaceholderText("Enter your message here...");

    sendButton = new QPushButton("Send Data");
    connectButton = new QPushButton("Connect to Server");
    emojiButton = new QPushButton("😊"); // 表情选择器按钮
    imageButton = new QPushButton("Insert Image"); // 插入图片按钮
    imageButton2 = new QPushButton("Look Image"); // 插入图片按钮
    snakegameButton =new QPushButton("SnakeGame");
    breakoutgameButton =new QPushButton("BreakoutGame");


    // 创建输入框
     urlLineEdit = new QLineEdit(this);
     urlLineEdit->setPlaceholderText("请输入网址，例如 https://www.example.com");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QHBoxLayout *gameLayout = new QHBoxLayout;
    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(sendButton);
    buttonLayout->addWidget(emojiButton);
    buttonLayout->addWidget(imageButton); // 添加插入图片按钮到布局
    buttonLayout->addWidget(imageButton2); // 添加插入图片按钮到布局

    gameLayout->addWidget(snakegameButton);
    gameLayout->addWidget(breakoutgameButton);

    mainLayout->addWidget(log);
    mainLayout->addWidget(inputArea);
    mainLayout->addWidget(urlLineEdit);
    mainLayout->addLayout(buttonLayout);
     mainLayout->addLayout(gameLayout);

    connect(connectButton, &QPushButton::clicked, this, &Client::onConnect);
    connect(sendButton, &QPushButton::clicked, this, &Client::onSendData);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(emojiButton, &QPushButton::clicked, this, &Client::onEmojiButtonClicked);
    connect(imageButton, &QPushButton::clicked, this, &Client::onInsertImage); // 连接插入图片按钮
    connect(imageButton2, &QPushButton::clicked, this, &Client::openUrl); // 连接插入图片按钮
    connect(snakegameButton, &QPushButton::clicked, this, &Client::startGame); // 连接插入图片按钮
     connect(breakoutgameButton, &QPushButton::clicked, this, &Client::startblockGame); // 连接插入图片按钮
}

Client::~Client()
{
    socket->close();
}

void Client::onConnect()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        socket->connectToHost("192.168.0.143", 1234);
        if (socket->waitForConnected(3000)) {
            log->append("Connected to server");
        } else {
            QMessageBox::critical(this, "Connection Error", socket->errorString());
        }
    } else {
        socket->close();
        log->append("Disconnected from server");
    }
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);


        // 处理普通文本消息
        log->append("Received from server: " + message);

}

void Client::onSendData()
{
    if (socket->isOpen()) {
        QString message = inputArea->toPlainText();
        if (!message.isEmpty()) {
            socket->write(message.toUtf8());
            log->append("Sent to server: " + message);
            inputArea->clear();
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter a message to send.");
        }
    } else {
        QMessageBox::warning(this, "Connection Error", "Not connected to server.");
    }
}

void Client::onEmojiButtonClicked()
{
    QStringList emojis = {
        "😊", "😂", "😍", "😎", "👍", "❤️", "🔥", "🙏", "🚀", "🎉",
        "😜", "😘", "😢", "😡", "😱", "😳", "😴", "😇", "😃", "😉",
        "😌","👽"
    };

    QDialog dialog(this);
    dialog.setWindowTitle("Select an Emoji");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QListWidget *listWidget = new QListWidget;
    listWidget->addItems(emojis);
    layout->addWidget(listWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString selectedEmoji = listWidget->currentItem()->text();
        inputArea->insertPlainText(selectedEmoji);
    }
}
/*
void Client::onInsertImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select an Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray imageData = file.readAll();
            QPixmap pixmap;
            if (pixmap.loadFromData(imageData)) {
                inputArea->insertHtml("<img src='data:image/png;base64," + QString::fromUtf8(imageData.toBase64()) + "'/>");
            } else {
                QMessageBox::warning(this, "Image Error", "Failed to load image.");
            }
            file.close();
        } else {
            QMessageBox::warning(this, "File Error", "Failed to open file.");
        }
    }
}
*/

void Client::onInsertImage() {
        // 目标网址
        QUrl url("https://imgur.la/upload/?lang=zh-CN");

        // 使用 QDesktopServices 打开默认浏览器
        bool success = QDesktopServices::openUrl(url);
        if (!success) {
            // 处理打开失败的情况
            qDebug("无法打开指定的网址");
        }
    }
void Client::openUrl() {
        // 获取用户输入的网址
        QString urlString = urlLineEdit->text().trimmed();

        // 检查输入是否为空
        if (urlString.isEmpty()) {
            qDebug() << "请输入一个网址";
            return;
        }

        // 确保网址以 http:// 或 https:// 开头
        if (!urlString.startsWith("http://") && !urlString.startsWith("https://")) {
            urlString = "http://" + urlString;
        }

        // 创建 QUrl 对象
        QUrl url(urlString);

        // 使用 QDesktopServices 打开默认浏览器
        bool success = QDesktopServices::openUrl(url);
        if (!success) {
            // 处理打开失败的情况
            qDebug() << "无法打开指定的网址";
        }
    }
void  Client::startGame() {
        SnakeGame *game = new SnakeGame();
        game->show();
        this->hide();
    }
void  Client::startblockGame() {
        Breakout *game = new Breakout();
        game->show();
        this->hide();
    }
