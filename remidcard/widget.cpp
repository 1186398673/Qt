#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList stringlist;
    stringlist<<"清华大学"<<"山东科技大学"<<"北京大学";
    stringlistmodel=new QStringListModel(this);
    stringlistmodel->setStringList(stringlist);
    ui->listView->setModel(stringlistmodel);
}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_addButton_clicked()
{
    QString university=ui->collegeEdit->text();
    QMessageBox::information()
}

