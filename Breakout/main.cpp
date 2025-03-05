#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <cstdlib>
#include <ctime>
#include<QMessageBox>
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
int ballSpeedX = 5;
int ballSpeedY = -5;

// 定义砖块参数
const int BRICK_ROWS = 5;
const int BRICK_COLS = 10;
const int BRICK_WIDTH = 50;
const int BRICK_HEIGHT = 20;
const int BRICK_PADDING = 10;
const int BRICK_OFFSET_X = (WIDTH - (BRICK_COLS * (BRICK_WIDTH + BRICK_PADDING))) / 2;
const int BRICK_OFFSET_Y = 50;

// 定义砖块结构
struct Brick {
    QPoint position;
    bool destroyed;
};

class Breakout : public QWidget {


public:
    Breakout(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("打砖块");
        setFixedSize(WIDTH, HEIGHT);

        // 初始化挡板位置
        paddleX = (WIDTH - PADDLE_WIDTH) / 2;
        paddleY = HEIGHT - PADDLE_HEIGHT - 10;

        // 初始化砖块
        bricks.clear();
        for (int row = 0; row < BRICK_ROWS; ++row) {
            for (int col = 0; col < BRICK_COLS; ++col) {
                Brick brick;
                brick.position = QPoint(BRICK_OFFSET_X + col * (BRICK_WIDTH + BRICK_PADDING),
                                        BRICK_OFFSET_Y + row * (BRICK_HEIGHT + BRICK_PADDING));
                brick.destroyed = false;
                bricks.append(brick);
            }
        }

        // 设置定时器
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Breakout::updateGame);
        timer->start(30); // 每30毫秒更新一次

        // 初始化随机数种子
        srand(time(0));
    }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制背景
        painter.setBrush(QBrush(Qt::black));
        painter.drawRect(0, 0, WIDTH, HEIGHT);

        // 绘制砖块
        painter.setBrush(QBrush(Qt::red));
        for (const Brick &brick : bricks) {
            if (!brick.destroyed) {
                painter.drawRect(brick.position.x(), brick.position.y(), BRICK_WIDTH, BRICK_HEIGHT);
            }
        }

        // 绘制挡板
        painter.setBrush(QBrush(Qt::blue));
        painter.drawRect(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT);

        // 绘制球
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(ballX - BALL_SIZE / 2, ballY - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE);
    }

    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                paddleX -= PADDLE_SPEED;
                if (paddleX < 0) paddleX = 0;
                break;
            case Qt::Key_Right:
                paddleX += PADDLE_SPEED;
                if (paddleX + PADDLE_WIDTH > WIDTH) paddleX = WIDTH - PADDLE_WIDTH;
                break;
            case Qt::Key_Escape:
                QApplication::quit();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }

private slots:
    // 更新游戏状态
    void updateGame() {
        // 更新球的位置
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // 碰撞检测与边界处理
        if (ballX <= BALL_SIZE / 2 || ballX >= WIDTH - BALL_SIZE / 2) {
            ballSpeedX = -ballSpeedX;
        }
        if (ballY <= BALL_SIZE / 2) {
            ballSpeedY = -ballSpeedY;
        }
        if (ballY >= HEIGHT - BALL_SIZE / 2) {
            // 球落到底部，游戏结束
            timer->stop();
            QMessageBox::information(this, "游戏结束", "游戏结束！");
            QApplication::quit();
        }

        // 碰撞检测与挡板
        if (ballY + BALL_SIZE / 2 >= paddleY && ballX >= paddleX && ballX <= paddleX + PADDLE_WIDTH) {
            ballSpeedY = -ballSpeedY;
        }

        // 碰撞检测与砖块
        for (int i = 0; i < bricks.size(); ++i) {
            Brick &brick = bricks[i];
            if (!brick.destroyed) {
                if (ballX >= brick.position.x() && ballX <= brick.position.x() + BRICK_WIDTH &&
                    ballY - BALL_SIZE / 2 <= brick.position.y() + BRICK_HEIGHT) {
                    brick.destroyed = true;
                    ballSpeedY = -ballSpeedY;
                    score += 10;
                    update();
                    break;
                }
            }
        }

        update();
    }

private:
    int paddleX, paddleY;
    QVector<Brick> bricks;
    QTimer *timer;
    int score = 0;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Breakout game;
    game.show();
    return app.exec();
}


