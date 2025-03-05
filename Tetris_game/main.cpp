#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <cstdlib>
#include <ctime>

// 定义游戏区域的宽度和高度（以格子为单位）
const int WIDTH = 10;
const int HEIGHT = 20;
const int BLOCK_SIZE = 30;

// 定义方块形状（7种基本形状）
const std::vector<std::vector<QPoint>> SHAPES = {
    // I
    { {0,1}, {1,1}, {2,1}, {3,1} },
    // J
    { {0,0}, {0,1}, {1,1}, {2,1} },
    // L
    { {2,0}, {0,1}, {1,1}, {2,1} },
    // O
    { {0,0}, {1,0}, {0,1}, {1,1} },
    // S
    { {1,0}, {2,0}, {0,1}, {1,1} },
    // T
    { {1,0}, {0,1}, {1,1}, {2,1} },
    // Z
    { {0,0}, {1,0}, {1,1}, {2,1} }
};

// 定义方向
enum Direction { LEFT, RIGHT, DOWN, ROTATE };

class Tetris : public QWidget {
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("俄罗斯方块");
        setFixedSize(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);

        // 初始化游戏状态
        srand(time(0));
        currentShape = getRandomShape();
        currentPosition = QPoint(WIDTH / 2, 0);
        gameOver = false;

        // 设置定时器，每500毫秒更新一次游戏状态
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Tetris::updateGame);
        timer->start(500);
    }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制游戏区域
        painter.setBrush(QBrush(Qt::black));
        painter.drawRect(0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);

        // 绘制当前方块
        painter.setBrush(QBrush(Qt::green));
        for (const QPoint &point : currentShape) {
            painter.drawRect((currentPosition.x() + point.x()) * BLOCK_SIZE, (currentPosition.y() + point.y()) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }

        // 绘制固定方块
        painter.setBrush(QBrush(Qt::blue));
        for (const QPoint &point : fixedBlocks) {
            painter.drawRect(point.x() * BLOCK_SIZE, point.y() * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }

    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                moveLeft();
                break;
            case Qt::Key_Right:
                moveRight();
                break;
            case Qt::Key_Down:
                moveDown();
                break;
            case Qt::Key_Up:
                rotate();
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
        moveDown();
    }

    // 生成随机方块形状
    std::vector<QPoint> getRandomShape() {
        int index = rand() % SHAPES.size();
        return SHAPES[index];
    }

    // 移动方块向左
    void moveLeft() {
        currentPosition.rx() -= 1;
        if (!isValidPosition(currentShape, currentPosition)) {
            currentPosition.rx() += 1;
        }
        update();
    }

    // 移动方块向右
    void moveRight() {
        currentPosition.rx() += 1;
        if (!isValidPosition(currentShape, currentPosition)) {
            currentPosition.rx() -= 1;
        }
        update();
    }

    // 移动方块向下
    void moveDown() {
        currentPosition.ry() += 1;
        if (!isValidPosition(currentShape, currentPosition)) {
            currentPosition.ry() -= 1;
            fixBlock();
            clearLines();
            newShape();
        }
        update();
    }

    // 旋转方块
    void rotate() {
        std::vector<QPoint> rotatedShape;
        for (const QPoint &point : currentShape) {
            rotatedShape.push_back(QPoint(-point.y(), point.x()));
        }
        if (isValidPosition(rotatedShape, currentPosition)) {
            currentShape = rotatedShape;
            update();
        }
    }

    // 检查位置是否有效
    bool isValidPosition(const std::vector<QPoint> &shape, const QPoint &position) {
        for (const QPoint &point : shape) {
            int x = position.x() + point.x();
            int y = position.y() + point.y();
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                return false;
            }
            if (fixedBlocks.contains(QPoint(x, y))) {
                return false;
            }
        }
        return true;
    }

    // 固定当前方块
    void fixBlock() {
        for (const QPoint &point : currentShape) {
            fixedBlocks.push_back(QPoint(currentPosition.x() + point.x(), currentPosition.y() + point.y()));
        }
    }

    // 清除满行
    void clearLines() {
        std::vector<QPoint> newFixedBlocks;
        for (int y = 0; y < HEIGHT; ++y) {
            int count = 0;
            for (int x = 0; x < WIDTH; ++x) {
                if (fixedBlocks.capacity(QPoint(x, y))) {
                    count++;
                }
            }
            if (count < WIDTH) {
                for (const QPoint &point : fixedBlocks) {
                    if (point.y() == y) {
                        newFixedBlocks.push_back(point);
                    }
                }
            }
        }
        fixedBlocks = newFixedBlocks;
    }

    // 生成新方块
    void newShape() {
        currentShape = getRandomShape();
        currentPosition = QPoint(WIDTH / 2, 0);
        if (!isValidPosition(currentShape, currentPosition)) {
            timer->stop();
            gameOver = true;
            QApplication::quit();
        }
    }

private:
    QTimer *timer;
    std::vector<QPoint> currentShape;
    QPoint currentPosition;
    std::vector<QPoint> fixedBlocks;
    bool gameOver;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Tetris game;
    game.show();
    return app.exec();
}

