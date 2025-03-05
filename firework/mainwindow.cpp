#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firework.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , frameCount(0)
{
    ui->setupUi(this);

    // 设置场景大小
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // 定时器，每16ms更新一次（大约60 FPS）
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateScene);
    timer->start(16);

    // 定时发射烟花
    QTimer::singleShot(1000, this, &MainWindow::emitFirework);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScene()
{
    scene->advance();
    frameCount++;
    if (frameCount % 60 == 0) { // 每秒发射一次
        emitFirework();
    }
}

void MainWindow::emitFirework()
{
    int x = QRandomGenerator::global()->bounded(100, 700);
    int y = QRandomGenerator::global()->bounded(100, 500);
    Firework *firework = new Firework(x, y, scene);
    scene->addItem(firework);
}
