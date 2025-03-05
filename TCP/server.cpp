// server.cpp
#include "server.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

Server::Server(QWidget *parent)
    : QWidget(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    log = new QTextEdit;
    startButton = new QPushButton("Start Server");
    sendButton = new QPushButton("Send Data");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(sendButton);
    mainLayout->addWidget(log);
    mainLayout->addLayout(buttonLayout);

    connect(startButton, &QPushButton::clicked, this, &Server::onStartServer);
    connect(sendButton, &QPushButton::clicked, this, &Server::onSendData);
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
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
    log->append("Received from client: " + QString(data));
}

void Server::onSendData()
{
    if (clientSocket && clientSocket->isOpen()) {
        QString message = "Hello from server";
        clientSocket->write(message.toUtf8());
        log->append("Sent to client: " + message);
    }
}
