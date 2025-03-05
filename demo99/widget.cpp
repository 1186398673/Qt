#include "widget.h"
#include "ui_widget.h"
#include "form1.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->logoinButton,SIGNAL(clicked()),this,SLOT(on_logoinButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_registerButton_clicked()
{
    qDebug("hello ");
}


void Widget::on_logoinButton_clicked()
{
   Form1 *ct=new Form1;
   ct->setGeometry(this->geometry());
   ct->show();
}

