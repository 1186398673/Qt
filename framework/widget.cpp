#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>
#include <ctime>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateFireworks();

private:
    struct Particle {
        double x;
        double y;
        double vx;
        double vy;
        int life;
        int maxLife;
        QColor color;
    };

    QVector<Particle> particles;
    QTimer *timer;
    double gravity;
};

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("跨年烟花");

    // 初始化重力加速度
    gravity = 0.1;

    // 创建定时器用于更新烟花状态
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateFireworks);

    // 启动定时器，每 20 毫秒更新一次
    timer->start(20);
}

Widget::~Widget()
{
    delete timer;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景（黑色）
    painter.fillRect(rect(), Qt::black);

    // 绘制烟花粒子
    for (const Particle &p : particles) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(p.color);
        painter.drawEllipse(QPointF(p.x, p.y), 2, 2);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 在鼠标点击位置创建烟花粒子
        int numParticles = 100;
        for (int i = 0; i < numParticles; ++i) {
            Particle particle;
            particle.x = event->x();
            particle.y = event->y();
            // 随机生成粒子的速度和方向
            double angle = (double(rand()) / RAND_MAX) * 2 * M_PI;
            double speed = (double(rand()) / RAND_MAX) * 10 + 5;
            particle.vx = speed * cos(angle);
            particle.vy = speed * sin(angle) - 10;
            particle.life = 0;
            particle.maxLife = (double(rand()) / RAND_MAX) * 100 + 50;
            // 随机生成粒子的颜色（彩虹色）
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            particle.color = QColor(r, g, b);

            particles.append(particle);
        }
    }
}

void Widget::updateFireworks()
{
    // 更新烟花粒子的位置和状态
    QMutableVectorIterator<Particle> it(particles);
    while (it.hasNext()) {
        Particle &p = it.next();
        p.x += p.vx;
        p.y += p.vy;
        p.vy += gravity;
        p.life++;

        // 如果粒子寿命超过最大值，则移除粒子
        if (p.life > p.maxLife) {
            it.remove();
        }
    }

    update();
}
