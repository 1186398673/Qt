#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QRandomGenerator>
#include <QPixmap>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerSpeed(20)
    , gravity(1)
    , velocity(0)
    , obstacleSpeed(10)
    , obstacleInterval(1500)
    , obstacleTimer(0)
    , isJumping(false)
    , score(0)
{
    ui->setupUi(this);

    // 设置窗口大小
    setFixedSize(800, 100);

    // 创建场景
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 100);

    // 设置背景颜色
    scene->setBackgroundBrush(QBrush(Qt::white));

    // 创建视图
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800, 100);
    view->setSceneRect(0, 0, 800, 100);

    // 创建玩家（恐龙）
    player = new QGraphicsPixmapItem(QPixmap(":/images/dino.png"));
    player->setPos(100, 96 - player->boundingRect().height());
    scene->addItem(player);

    // 添加分数标签
    scoreLabel = new QLabel(this);
    scoreLabel->setText("分数: 0");
    scoreLabel->setGeometry(100, 10, 100, 30);
    scoreLabel->setStyleSheet("color: black; font-size: 16px;");
    scoreLabel->show();

    // 启动定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Up)
    {
       timer->start(16); // 大约60 FPS
        if(!isJumping)
        {
            isJumping = true;
            velocity = -15;
            canDoubleJump = true; // 允许第二次跳跃
        }
        else if(canDoubleJump)
        {
            velocity += -5; // 第二次跳跃的力度可以小一些
            canDoubleJump = false;
        }
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::updateGame()
{
    // 处理跳跃
    if(isJumping)
    {
        player->moveBy(0, velocity);
        velocity += gravity;
        if(player->y() >= 96 - player->boundingRect().height())
        {
            player->setPos(100, 96 - player->boundingRect().height());
            isJumping = false;
            velocity = 0;
            canDoubleJump = false; // 重置双跳状态
        }
    }

    // 移动障碍物
    moveObstacles();

    // 生成障碍物
    obstacleTimer += 16;
    if(obstacleTimer >= obstacleInterval)
    {
        spawnObstacle();
        obstacleTimer = 0;
    }

    // 检查碰撞
    checkCollision();

    // 更新分数
    score += 1;
    scoreLabel->setText(QString("分数: %1").arg(score));
}

void MainWindow::spawnObstacle()
{
    // 随机决定生成1个、2个或3个仙人掌
    int numCacti = QRandomGenerator::global()->bounded(1, 4); // 1到3之间

    // 随机决定第一个仙人掌的位置
    int firstX = 800;
    int firstY = 88 - 50; // 假设仙人掌高度为50

    // 存储仙人掌的位置
    QVector<QPoint> positions;
    positions.append(QPoint(firstX, firstY));

    // 生成后续仙人掌的位置
    for(int i = 1; i < numCacti; ++i)
    {
        int x = positions.last().x() + MIN_OBSTACLE_INTERVAL + QRandomGenerator::global()->bounded(0, 40); // 最小间隔加上随机间隔
        int y = 88 - 50;
        positions.append(QPoint(x, y));
    }

    // 创建仙人掌并添加到场景中
    for(const QPoint &pos : positions)
    {
        QGraphicsPixmapItem *cactus = new QGraphicsPixmapItem(QPixmap(":/images/cactus.png"));
        cactus->setPos(pos);
        scene->addItem(cactus);
        obstacles.append(cactus);
    }
}


void MainWindow::moveObstacles()
{
    for(auto &obstacle : obstacles)
    {
        obstacle->moveBy(-obstacleSpeed, 0);
    }

    // 移除已经移出屏幕的障碍物
    for(auto it = obstacles.begin(); it != obstacles.end(); )
    {
        if((*it)->x() < -(*it)->boundingRect().width())
        {
            scene->removeItem(*it);
            it = obstacles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MainWindow::checkCollision()
{
    QList<QGraphicsItem*> collidingItems = player->collidingItems();
    for(auto &item : collidingItems)
    {
        // 检查是否与障碍物碰撞
        if(obstacles.contains(static_cast<QGraphicsPixmapItem*>(item)))
        {
            // 游戏结束
            timer->stop();
            qDebug() << "游戏结束！";
            // 这里可以添加游戏结束逻辑，如弹出对话框等
            QMessageBox::information(this, "游戏结束", "你撞到了障碍物！");
            // 重置玩家位置
            player->setPos(100, 96 - player->boundingRect().height());
            score = 0;
            // 清除所有障碍物
           for(auto &obstacle : obstacles)
           {
              scene->removeItem(obstacle);
           }
            }
    }


}
