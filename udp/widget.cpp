#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpsocket =new QUdpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openButton_clicked()
{
    if(udpsocket->bind(ui->localEdit->text().toInt())==true)
    {
       connect(udpsocket, &QUdpSocket::readyRead, this, &Widget::readyread_slot);
       QMessageBox::information(this,"提示","成功");
    }
    else
    {
       QMessageBox::information(this,"提示","失败");
    }

}

void Widget::readyread_slot(){
    while (udpsocket->hasPendingDatagrams()) {
       QByteArray array;
       array.resize(udpsocket->pendingDatagramSize());
       udpsocket->readDatagram(array.data(),array.size());
       QString buf;
       buf=array.data();
       ui->recvTextEdit->appendPlainText(buf);
    }

}

void Widget::on_closeButton_clicked()
{
    udpsocket->close();
}


void Widget::on_sendButton_clicked()
{
    quint16 port;
    QString buf;
    QHostAddress hostaddress;

    hostaddress.setAddress(ui->objectipEdit->text());
    buf=ui->sendEdit->text();
    port=ui->objectEdit->text().toInt();
    udpsocket->writeDatagram(buf.toLocal8Bit().data(),buf.length(),hostaddress,port);
}

