#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
// 定义游戏区域大小
const int WIDTH = 400;
const int HEIGHT = 600;

// 定义敌机类型
struct Enemy {
    QPoint position;
    int speed;
};

// 定义子弹类型
struct Bullet {
    QPoint position;
    int speed;
};

class ShootEmUp : public QWidget {


public:
    ShootEmUp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("飞行射击游戏");
        setFixedSize(WIDTH, HEIGHT);

        // 初始化游戏状态
        playerPosition = QPoint(WIDTH / 2, HEIGHT - 50);
        enemies.clear();
        bullets.clear();
        gameOver = false;
        score = 0;

        // 设置定时器
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &ShootEmUp::updateGame);
        timer->start(30); // 每30毫秒更新一次

        // 设置敌机生成定时器
        enemyTimer = new QTimer(this);
        connect(enemyTimer, &QTimer::timeout, this, &ShootEmUp::spawnEnemy);
        enemyTimer->start(1000); // 每秒生成一个敌机

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

        // 绘制玩家
        painter.setBrush(QBrush(Qt::green));
        painter.drawRect(playerPosition.x() - 20, playerPosition.y() - 20, 40, 40);

        // 绘制敌机
        painter.setBrush(QBrush(Qt::red));
        for (const Enemy &enemy : enemies) {
            painter.drawRect(enemy.position.x() - 20, enemy.position.y() - 20, 40, 40);
        }

        // 绘制子弹
        painter.setBrush(QBrush(Qt::yellow));
        for (const Bullet &bullet : bullets) {
            painter.drawRect(bullet.position.x() - 5, bullet.position.y() - 5, 10, 10);
        }

        // 绘制得分
        painter.setPen(Qt::white);
        painter.drawText(10, 20, QString("得分: %1").arg(score));
    }

    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                playerPosition.rx() -= 10;
                if (playerPosition.x() < 20) playerPosition.rx() = 20;
                break;
            case Qt::Key_Right:
                playerPosition.rx() += 10;
                if (playerPosition.x() > WIDTH - 20) playerPosition.rx() = WIDTH - 20;
                break;
            case Qt::Key_Space:
                shoot();
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
        // 更新敌机位置
        for (Enemy &enemy : enemies) {
            enemy.position.ry() += enemy.speed;
        }

        // 更新子弹位置
        for (Bullet &bullet : bullets) {
            bullet.position.ry() -= bullet.speed;
        }

        // 移除越界的敌机和子弹
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](const Enemy &enemy) {
            return enemy.position.y() > HEIGHT;
        }), enemies.end());

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet &bullet) {
            return bullet.position.y() < 0;
        }), bullets.end());

        // 检测碰撞
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            // 检测敌机是否碰到玩家
            if (it->position.x() > playerPosition.x() - 20 &&
                it->position.x() < playerPosition.x() + 20 &&
                it->position.y() > playerPosition.y() - 20 &&
                it->position.y() < playerPosition.y() + 20) {
                gameOver = true;
                timer->stop();
                QMessageBox::information(this, "游戏结束", "你被击中了！");
                QApplication::quit();
            }

            // 检测敌机是否被子弹击中
            for (auto jt = bullets.begin(); jt != bullets.end(); ++jt) {
                if (it->position.x() > jt->position.x() - 5 &&
                    it->position.x() < jt->position.x() + 5 &&
                    it->position.y() > jt->position.y() - 5 &&
                    it->position.y() < jt->position.y() + 5) {
                    enemies.erase(it);
                    bullets.erase(jt);
                    score += 10;
                    return;
                }
            }
        }

        update();
    }

    // 生成敌机
    void spawnEnemy() {
        Enemy enemy;
        enemy.position = QPoint(rand() % (WIDTH - 40) + 20, 0);
        enemy.speed = 5 + rand() % 5;
        enemies.push_back(enemy);
    }

    // 发射子弹
    void shoot() {
        Bullet bullet;
        bullet.position = playerPosition;
        bullet.speed = 10;
        bullets.push_back(bullet);
    }

private:
    QPoint playerPosition;
    QVector<Enemy> enemies;
    QVector<Bullet> bullets;
    QTimer *timer;
    QTimer *enemyTimer;
    bool gameOver;
    int score;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ShootEmUp game;
    game.show();
    return app.exec();
}

