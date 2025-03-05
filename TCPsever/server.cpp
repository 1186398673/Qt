#include "server.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
Server::Server(QWidget *parent)
    : QWidget(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    log = new QTextEdit;
    log->setReadOnly(true); // 设置日志区域为只读

    inputArea = new QTextEdit;
    inputArea->setPlaceholderText("Enter your message here...");

    startButton = new QPushButton("Start Server");
    sendButton = new QPushButton("Send Data");
    emojiButton = new QPushButton("😊"); // 初始化表情选择器按钮
    imageButton = new QPushButton("Insert Image"); // 插入图片按钮


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
     // 添加表情选择器按钮到输入布局

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(sendButton);
    buttonLayout->addWidget(emojiButton);
    buttonLayout->addWidget(imageButton); // 添加插入图片按钮到布局


    mainLayout->addWidget(log);
    mainLayout->addWidget(inputArea);
    mainLayout->addLayout(buttonLayout);


    connect(startButton, &QPushButton::clicked, this, &Server::onStartServer);
    connect(sendButton, &QPushButton::clicked, this, &Server::onSendData);
    connect(emojiButton, &QPushButton::clicked, this, &Server::onEmojiButtonClicked); // 连接表情选择器按钮
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(imageButton, &QPushButton::clicked, this, &Server::onInsertImage); // 连接插入图片按钮
}

Server::~Server()
{
    if (server->isListening()) {
        server->close();
    }
}

void Server::onStartServer()
{
    if (!server->listen(QHostAddress::Any, 1234)) {
        QMessageBox::critical(this, "Server Error", server->errorString());
        return;
    }
    log->append("Server started, listening on port 1234");
}

void Server::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    log->append("New client connected");
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, [=]() {
        log->append("Client disconnected");
        clientSocket->deleteLater();
        clientSocket = nullptr;
    });
}

void Server::onReadyRead()
{
    QByteArray data = clientSocket->readAll();
    QString message = QString::fromUtf8(data);

        log->append("Received from client: " + message);

}

void Server::onSendData()
{
    if (clientSocket && clientSocket->isOpen()) {
        QString message = inputArea->toPlainText();
        if (!message.isEmpty()) {
            clientSocket->write(message.toUtf8());
            log->append("Sent to client: " + message);
            inputArea->clear();
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter a message to send.");
        }
    } else {
        QMessageBox::warning(this, "Connection Error", "No client connected.");
    }
}

void Server::onEmojiButtonClicked()
{
    // 定义一个包含多个表情的列表
    QStringList emojis = {
        "😊", "😂", "😍", "😎", "👍", "❤️", "🔥", "🙏", "🚀", "🎉",
        "😜", "😘", "😢", "😡", "😱", "😳", "😴", "😇", "😃", "😉"
    };

    // 创建一个对话框来显示表情列表
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
        inputArea->insertPlainText(selectedEmoji); // 将选中的表情插入到输入框中
    }
}
void Server::onInsertImage()
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
