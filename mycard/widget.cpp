#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



     ui->plainTextEdit->setReadOnly(true);
     ui->edictButton->setHidden(true);
     ui->saveButton->setHidden(true);
     ui->plainTextEdit->setHidden(true);
     ui->exitButton->setHidden(true);
     ui->groupBox_2->setHidden(true);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_addButton_clicked()
{

    ui->plainTextEdit->setReadOnly(false);
    ui->plainTextEdit->clear();
    addEditing=true;
    isEditing=true;
    ui->groupBox->setHidden(true);
    ui->addButton->setHidden(true);
    ui->deleteButton->setHidden(true);
    ui->listWidget->setHidden(true);
     ui->edictButton->setHidden(false);
     ui->saveButton->setHidden(false);
     ui->plainTextEdit->setHidden(false);
     ui->exitButton->setHidden(false);
     ui->groupBox_2->setHidden(false);
     ui->groupBox_2->move(20, 70);

}


void Widget::on_deleteButton_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item) {
        ui->listWidget->removeItemWidget(item);
        delete item;
        QMessageBox::information(this, tr("成功"), tr("笔记已删除"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("没有选中的笔记"));
    }
    ui->plainTextEdit->clear();
}






void Widget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (item) {
        currentItem = item;
        ui->plainTextEdit->setPlainText(item->text());
    }
    ui->groupBox->setHidden(true);
    ui->addButton->setHidden(true);
    ui->deleteButton->setHidden(true);
    ui->listWidget->setHidden(true);
     ui->plainTextEdit->setReadOnly(true);
      ui->edictButton->setHidden(false);
     ui->saveButton->setHidden(false);
     ui->plainTextEdit->setHidden(false);
     ui->exitButton->setHidden(false);
     ui->groupBox_2->setHidden(false);
      ui->groupBox_2->move(20,70);



}


void Widget::on_saveButton_clicked()
{

     if(addEditing){
     QString text = ui->plainTextEdit->toPlainText().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("卡片内容不能为空"));
        return;
    }

    // 检查是否重复（可选）
    if (ui->listWidget->findItems(text, Qt::MatchExactly).isEmpty()) {
        ui->listWidget->addItem(text);
        QMessageBox::information(this, tr("成功"), tr("卡片已添加"));

    } else {
        QMessageBox::warning(this, tr("警告"), tr("该项目已存在"));
    }
    addEditing=false;
    }

    else{

    if (!isEditing) {
        QMessageBox::warning(this, tr("警告"), tr("没有正在编辑的项目"));
        return;
    }

    QListWidgetItem *item = ui->listWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, tr("警告"), tr("当前没有选中的项目"));
        return;
    }

    QString newText = ui->plainTextEdit->toPlainText();
    if (newText.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("笔记内容不能为空"));
        return;
    }

    // 检查是否重复
    if (ui->listWidget->findItems(newText, Qt::MatchExactly).size() <= 1) {
        item->setText(newText);
        QMessageBox::information(this, tr("成功"), tr("笔记已保存"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("该项目已存在"));
    }
    }

     // 重置编辑状态
    isEditing = false;
    ui->plainTextEdit->setReadOnly(true);

}


void Widget::on_edictButton_clicked()
{
 if (ui->listWidget->count() == 0) {
        QMessageBox::warning(this, tr("警告"), tr("列表中没有项目"));
        return;
    }


 if (isEditing) {
        QMessageBox::warning(this, tr("警告"), tr("当前正在编辑中"));
        return;
    }

    QListWidgetItem *item = ui->listWidget->currentItem();
    if (!item) {
        QString text = ui->plainTextEdit->toPlainText().trimmed();
         // 设置编辑状态
    isEditing = true;
    ui->plainTextEdit->setReadOnly(false);
    ui->plainTextEdit->setPlainText(text);

    }
    else
    {
     // 设置编辑状态
    isEditing = true;
    ui->plainTextEdit->setReadOnly(false);
    ui->plainTextEdit->setPlainText(item->text());
    }



}


void Widget::on_exitButton_clicked()
{


  isEditing = false;
  ui->edictButton->setHidden(true);
  ui->saveButton->setHidden(true);
  ui->plainTextEdit->setHidden(true);
  ui->exitButton->setHidden(true);
  ui->groupBox_2->setHidden(true);
  ui->listWidget->setHidden(false);
  ui->addButton->setHidden(false);
  ui->deleteButton->setHidden(false);
  ui->groupBox->setHidden(false);





}


void Widget::on_pushButton_clicked()
{
     // 弹出文件对话框，让用户选择保存位置和文件名
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存列表到文本文件"),
                                                    "",
                                                    tr("文本文件 (*.txt);;所有文件 (*)"));

    // 如果用户取消了保存操作，直接返回
    if (fileName.isEmpty())
        return;

    // 打开文件，如果文件不存在则创建
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("保存失败"), tr("无法打开文件进行写入。"));
        return;
    }

    // 使用 QTextStream 写入文本
    QTextStream out(&file);
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QString itemText = ui->listWidget->item(i)->text();
        out << itemText << "\n"; // 每个项占一行
    }

    file.close();

    QMessageBox::information(this, tr("保存成功"), tr("列表已成功保存到 %1").arg(fileName));
}


void Widget::on_pushButton_2_clicked()
{
    // 弹出文件对话框，让用户选择要导入的文本文件
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("导入文本文件"),
                                                    "",
                                                    tr("文本文件 (*.txt);;所有文件 (*)"));

    // 如果用户取消了导入操作，直接返回
    if (fileName.isEmpty())
        return;

    // 打开文件进行读取
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("导入失败"), tr("无法打开文件进行读取。"));
        return;
    }

    // 使用 QSet 来跟踪已存在的卡片文本
    QSet<QString> existingItems;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        existingItems.insert(ui->listWidget->item(i)->text());
    }

    // 使用 QTextStream 读取文件内容
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed(); // 去除首尾空格
        if (!line.isEmpty() && !existingItems.contains(line)) {
            ui->listWidget->addItem(line);
            existingItems.insert(line); // 更新已存在的卡片集合
        }
    }

    file.close();

    QMessageBox::information(this, tr("导入成功"), tr("文件已成功导入到列表中。"));
}

