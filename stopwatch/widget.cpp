#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&timer,&QTimer::timeout,this,&Widget::timeout_slot);
    time.setHMS(0,0,0,0);
    ui->label->setText("00:00:00:000");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    timer.start(40);
}
void Widget::timeout_slot()
{
  //qDebug("ha ha ha");
  time=time.addMSecs(40);
  ui->label->setText(time.toString("hh:mm:ss:zzz"));
}

void Widget::on_closeButton_clicked()
{
    timer.stop();
}


void Widget::on_resetButton_clicked()
{
    timer.stop();
    time.setHMS(0,0,0,0);
    ui->label->setText("00:00:00:000");

}


void Widget::on_markButton_clicked()
{
    ui->recvtextBrowser->append(time.toString("hh:mm:ss:zzz"));
}

