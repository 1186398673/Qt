#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
// 定义游戏区域大小
const int WIDTH = 400;
const int HEIGHT = 400;

// 定义地鼠状态
enum MoleState { HIDDEN, VISIBLE };

class WhackAMole : public QWidget {


public:
    WhackAMole(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("打地鼠");
        setFixedSize(WIDTH, HEIGHT);

        // 初始化游戏状态
        score = 0;
        gameTime = 300; // 游戏时间30秒
        currentMole = -1;

        // 初始化地鼠位置（3x3网格）
        for (int i = 0; i < 9; ++i) {
            moles.append(QPoint((i % 3) * (WIDTH / 3) + WIDTH / 6, (i / 3) * (HEIGHT / 3) + HEIGHT / 6));
        }

        // 设置定时器
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &WhackAMole::updateGame);
        timer->start(1000); // 每秒更新一次

        moleTimer = new QTimer(this);
        connect(moleTimer, &QTimer::timeout, this, &WhackAMole::showMole);
        moleTimer->start(1000); // 每秒生成一个地鼠

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
        painter.setBrush(QBrush(Qt::lightGray));
        painter.drawRect(0, 0, WIDTH, HEIGHT);

        // 绘制地鼠
        painter.setBrush(QBrush(Qt::black));
        for (int i = 0; i < moles.size(); ++i) {
            if (i == currentMole) {
                painter.drawEllipse(moles[i].x() - 20, moles[i].y() - 20, 40, 40);
            }
        }

        // 绘制得分和剩余时间
        painter.setPen(Qt::black);
        painter.drawText(10, 20, QString("得分: %1").arg(score));
        painter.drawText(WIDTH - 100, 20, QString("时间: %1").arg(gameTime));
    }

    // 重写鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override {
        if (currentMole != -1) {
            QPoint clickPos = event->pos();
            QPoint molePos = moles[currentMole];
            if ((clickPos.x() > molePos.x() - 20) && (clickPos.x() < molePos.x() + 20) &&
                (clickPos.y() > molePos.y() - 20) && (clickPos.y() < molePos.y() + 20)) {
                score += 10;
                currentMole = -1;
                update();
            }
        }
    }

private slots:
    // 更新游戏状态
    void updateGame() {
        if (gameTime > 0) {
            gameTime--;
            if (gameTime == 0) {
                timer->stop();
                moleTimer->stop();
                QMessageBox::information(this, "游戏结束", QString("游戏结束！你的得分: %1").arg(score));
                QApplication::quit();
            }
        }
    }

    // 生成地鼠
    void showMole() {
        currentMole = rand() % moles.size();
        update();
        // 隐藏地鼠
        QTimer::singleShot(1000, this, [=]() {
            currentMole = -1;
            update();
        });
    }

private:
    QVector<QPoint> moles;
    int score;
    int gameTime;
    int currentMole;
    QTimer *timer;
    QTimer *moleTimer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WhackAMole game;
    game.show();
    return app.exec();
}

