// SnakeGame.h
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QPoint>

class SnakeGame : public QWidget {
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;

    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // 更新游戏状态
    void updateGame();

    // 生成食物
    void generateFood();

private:
    bool checkCollision(const std::vector<QPoint> &snake, const QPoint &head);

    // 游戏方向
    enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
    Direction direction;

    // 食物位置
    QPoint food;

    // 蛇的身体
    std::vector<QPoint> snake;

    // 定时器
    QTimer *timer;

    // 游戏区域的宽度和高度
    const int WIDTH = 600;
    const int HEIGHT = 400;
    const int BLOCK_SIZE = 20;
};

#endif // SNAKEGAME_H
