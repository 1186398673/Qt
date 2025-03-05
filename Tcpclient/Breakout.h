// Breakout.h
#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <QMessageBox>

class Breakout : public QWidget {


public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;

    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // 更新游戏状态
    void updateGame();

private:
    // 初始化砖块
    void initializeBricks();

    // 定义游戏区域大小
const int WIDTH = 600;
const int HEIGHT = 400;

// 定义挡板参数
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 20;
const int PADDLE_SPEED = 10;

// 定义球参数
const int BALL_SIZE = 10;
int ballX = WIDTH / 2;
int ballY = HEIGHT / 2;
int ballSpeedX = 3;
int ballSpeedY = -3;

// 定义砖块参数
const int BRICK_ROWS = 5;
const int BRICK_COLS = 10;
const int BRICK_WIDTH = 50;
const int BRICK_HEIGHT = 20;
const int BRICK_PADDING = 10;
const int BRICK_OFFSET_X = (WIDTH - (BRICK_COLS * (BRICK_WIDTH + BRICK_PADDING))) / 2;
const int BRICK_OFFSET_Y = 50;

    // 砖块结构
    struct Brick {
        QPoint position;
        bool destroyed;
    };



    // 挡板位置
    int paddleX;
    int paddleY;

    // 砖块列表
    QVector<Brick> bricks;

    // 定时器
    QTimer *timer;

    // 分数
    int score;
};

#endif // BREAKOUT_H
