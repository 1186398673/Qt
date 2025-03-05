#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpserver =new QTcpServer(this);
    tcpsocket =new QTcpSocket(this);

    connect(tcpserver, &QTcpServer::newConnection, this, &Widget::newconection_slot);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::newconection_slot(){
  tcpsocket=tcpserver->nextPendingConnection();
  //connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readyread_slot()));
  connect(tcpsocket, &QTcpSocket::readyRead, this, &Widget::readyread_slot);
}
void Widget::readyread_slot(){
  QString buf;
  buf=tcpsocket->readAll();
  ui->recvTextEdit->appendPlainText(buf);
}



void Widget::on_openButton_clicked()
{
  tcpserver->listen(QHostAddress::Any,ui->numberEdit->text().toInt());
}


void Widget::on_closeButton_clicked()
{
     tcpserver->close();
}


void Widget::on_sendButton_clicked()
{
    tcpsocket->write(ui->lineEdit->text().toLocal8Bit().data());
}

