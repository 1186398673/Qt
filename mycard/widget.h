#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();




    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_saveButton_clicked();

    void on_edictButton_clicked();

    void on_exitButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QListWidget *listWidget;
    QListWidgetItem *currentItem;
    bool isEditing; // 标记当前是否处于编辑状态
    bool addEditing;
};
#endif // WIDGET_H
