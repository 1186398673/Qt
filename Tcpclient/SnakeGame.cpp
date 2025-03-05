// SnakeGame.cpp
#include "SnakeGame.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame(QWidget *parent) : QWidget(parent), direction(STOP) {
    setWindowTitle("贪吃蛇游戏");
    setFixedSize(WIDTH, HEIGHT);

    // 初始化蛇的位置
    snake.push_back(QPoint(WIDTH / 2, HEIGHT / 2));

    // 初始化随机数种子
    srand(time(0));
    generateFood();

    // 设置定时器，每100毫秒更新一次游戏状态
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeGame::updateGame);
    timer->start(100);
}

SnakeGame::~SnakeGame() {
    delete timer;
}

bool SnakeGame::checkCollision(const std::vector<QPoint> &snake, const QPoint &head) {
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i] == head) {
            return true; // 碰撞发生
        }
    }
    return false; // 没有碰撞
}

void SnakeGame::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制食物
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(food.x(), food.y(), BLOCK_SIZE, BLOCK_SIZE);

    // 绘制蛇
    painter.setBrush(QBrush(Qt::green));
    for (const QPoint &point : snake) {
        painter.drawRect(point.x(), point.y(), BLOCK_SIZE, BLOCK_SIZE);
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (direction != DOWN) direction = UP;
            break;
        case Qt::Key_Down:
            if (direction != UP) direction = DOWN;
            break;
        case Qt::Key_Left:
            if (direction != RIGHT) direction = LEFT;
            break;
        case Qt::Key_Right:
            if (direction != LEFT) direction = RIGHT;
            break;
        case Qt::Key_Escape:
            QApplication::quit();
            this->show();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void SnakeGame::updateGame() {
    QPoint head = snake[0];
    switch (direction) {
        case LEFT:
            head.rx() -= BLOCK_SIZE;
            break;
        case RIGHT:
            head.rx() += BLOCK_SIZE;
            break;
        case UP:
            head.ry() -= BLOCK_SIZE;
            break;
        case DOWN:
            head.ry() += BLOCK_SIZE;
            break;
        default:
            break;
    }

    // 检查碰撞
    if (head.x() < 0 || head.x() >= WIDTH || head.y() < 0 || head.y() >= HEIGHT || checkCollision(snake, head)) {
        timer->stop();
        QApplication::quit();
        this->show();
    }

    // 添加新的头部
    snake.insert(snake.begin(), head);

    // 检查是否吃到食物
    if (head == food) {
        generateFood();
    } else {
        // 移除尾部
        snake.pop_back();
    }

    // 触发重绘
    update();
}

void SnakeGame::generateFood() {
    int x = rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
    int y = rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;
    food = QPoint(x, y);
}
