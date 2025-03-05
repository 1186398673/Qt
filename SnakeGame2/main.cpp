#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QPushButton>
#include <QGridLayout>

// 定义游戏区域的宽度和高度
const int WIDTH = 480;
const int HEIGHT = 800;
const int BLOCK_SIZE = 20;

// 定义方向
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

class SnakeGame : public QWidget {

public:
    SnakeGame(QWidget *parent = nullptr) : QWidget(parent), direction(STOP) {
        setWindowTitle("贪吃蛇游戏");
        setFixedSize(WIDTH, HEIGHT);

        // 初始化游戏状态
        snake.push_back(QPoint(WIDTH / 2, HEIGHT / 2));
        srand(time(0));
        generateFood();

        // 设置定时器，每100毫秒更新一次游戏状态
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SnakeGame::updateGame);
        timer->start(100);

        // 创建控制按钮
        createControlButtons();
    }

    bool checkCollision(const std::vector<QPoint> &snake, const QPoint &head) {
        for (size_t i = 1; i < snake.size(); ++i) {
            if (snake[i] == head) {
                return true; // 碰撞发生
            }
        }
        return false; // 没有碰撞
    }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override {
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

    // 重写鼠标事件
    void mousePressEvent(QMouseEvent *event) override {
        // 忽略鼠标事件，因为按钮会处理它们
        QWidget::mousePressEvent(event);
    }

private slots:
    // 更新游戏状态
    void updateGame() {
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

    // 生成食物
    void generateFood() {
        int x = rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
        int y = rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;
        food = QPoint(x, y);
    }

    // 控制按钮槽函数
    void moveUp() {
        if (direction != DOWN) direction = UP;
    }

    void moveDown() {
        if (direction != UP) direction = DOWN;
    }

    void moveLeft() {
        if (direction != RIGHT) direction = LEFT;
    }

    void moveRight() {
        if (direction != LEFT) direction = RIGHT;
    }

private:
    void createControlButtons() {
        // 创建按钮
        QPushButton *upButton = new QPushButton("↑");
        QPushButton *downButton = new QPushButton("↓");
        QPushButton *leftButton = new QPushButton("←");
        QPushButton *rightButton = new QPushButton("→");

        // 设置按钮大小
        upButton->setFixedSize(60, 60);
        downButton->setFixedSize(60, 60);
        leftButton->setFixedSize(60, 60);
        rightButton->setFixedSize(60, 60);

        // 连接按钮点击信号到槽函数
        connect(upButton, &QPushButton::clicked, this, &SnakeGame::moveUp);
        connect(downButton, &QPushButton::clicked, this, &SnakeGame::moveDown);
        connect(leftButton, &QPushButton::clicked, this, &SnakeGame::moveLeft);
        connect(rightButton, &QPushButton::clicked, this, &SnakeGame::moveRight);

        // 创建网格布局
        QGridLayout *buttonLayout = new QGridLayout;
        buttonLayout->addWidget(leftButton, 1, 0);
        buttonLayout->addWidget(upButton, 0, 1);
        buttonLayout->addWidget(rightButton, 1, 2);
        buttonLayout->addWidget(downButton, 2, 1);

        // 创建主垂直布局，将按钮放在底部
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addStretch(); // 添加伸缩量，将按钮推到下面
        mainLayout->addLayout(buttonLayout);

        // 设置主布局
        setLayout(mainLayout);
    }

    Direction direction;
    QPoint food;
    std::vector<QPoint> snake;
    QTimer *timer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SnakeGame game;
    game.show();
    return app.exec();
}
