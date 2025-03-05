#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpsocket=new QTcpSocket((this));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openButton_clicked()
{
    tcpsocket->connectToHost(ui->ipEdit->text(),ui->numberEdit->text().toInt());
    connect(tcpsocket, &QTcpSocket::connected, this, &Widget::newconection_slot);
}

void Widget::newconection_slot(){
     connect(tcpsocket, &QTcpSocket::readyRead, this, &Widget::readyread_slot);
}
void Widget::readyread_slot(){

  QString buf;
  buf=tcpsocket->readAll();
  ui->recvTextEdit->appendPlainText(buf);

}

void Widget::on_closeButton_clicked()
{
    tcpsocket->close();
}


void Widget::on_sendButton_clicked()
{
   tcpsocket->write(ui->sendEdit->text().toLocal8Bit().data());
}

