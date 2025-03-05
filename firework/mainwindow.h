#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateScene();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    int frameCount;
    void emitFirework();
};

#endif // MAINWINDOW_H
