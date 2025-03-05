// client.cpp
#include "client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

Client::Client(QWidget *parent)
    : QWidget(parent), socket(new QTcpSocket(this))
{
    log = new QTextEdit;
    connectButton = new QPushButton("Connect to Server");
    sendButton = new QPushButton("Send Data");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(sendButton);
    mainLayout->addWidget(log);
    mainLayout->addLayout(buttonLayout);

    connect(connectButton, &QPushButton::clicked, this, &Client::onConnect);
    connect(sendButton, &QPushButton::clicked, this, &Client::onSendData);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
{
    socket->close();
}

void Client::onConnect()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        socket->connectToHost("127.0.0.1", 1234);
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
    log->append("Received from server: " + QString(data));
}

void Client::onSendData()
{
    if (socket->isOpen()) {
        QString message = "Hello from client";
        socket->write(message.toUtf8());
        log->append("Sent to server: " + message);
    }
}
