#include "firework.h"
#include <QRandomGenerator>
#include "mainwindow.h"
Firework::Firework(int x, int y, QGraphicsScene *scene)
    : xPos(x), yPos(y), exploded(false)
{
    // 随机生成上升速度
    int vx = QRandomGenerator::global()->bounded(-2, 2);
    int vy = QRandomGenerator::global()->bounded(-10, -5);
    velocities.append(QPointF(vx, vy));

    // 添加到场景
    scene->addItem(this);
}

Firework::~Firework()
{
    // 清理粒子
    for (const QPointF &particle : particles) {
        this->scene()->removeItem(new QGraphicsEllipseItem(xPos, yPos, 5, 5));
    }
}

QRectF Firework::boundingRect() const
{
    return QRectF(xPos - 2.5, yPos - 2.5, 5, 5);
}

void Firework::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(QPointF(xPos, yPos), 2.5, 2.5);
}

void Firework::advance(int phase)
{
    if (!phase) return;

    if (!exploded) {
        // 更新位置
        xPos += velocities[0].x();
        yPos += velocities[0].y();

        // 应用重力
        velocities[0].setY(velocities[0].y() + 0.5);

        // 检查是否达到最高点
        if (velocities[0].y() >= 0) {
            explode();
        }
    } else {
        // 更新粒子位置
        for (int i = 0; i < particles.size(); ++i) {
            particles[i] += velocities[i];
            velocities[i].setY(velocities[i].y() + 0.2); // 重力
        }

        // 移除消失的粒子
        for (int i = particles.size() - 1; i >= 0; --i) {
            if (particles[i].y() > yPos + 200 || particles[i].x() < xPos - 200 || particles[i].x() > xPos + 200) {
                scene()->removeItem(scene()->itemAt(particles[i], QTransform()));
                particles.remove(i);
                velocities.remove(i);
            }
        }

        // 如果所有粒子消失，则从场景中移除自身
        if (particles.isEmpty()) {
            scene()->removeItem(this);
            delete this;
        }
    }
}

void Firework::explode()
{
    exploded = true;
    int numParticles = QRandomGenerator::global()->bounded(20, 50);
    for (int i = 0; i < numParticles; ++i) {
        // 随机方向
        float angle = QRandomGenerator::global()->bounded(0, 360) * M_PI / 180;
        float speed = QRandomGenerator::global()->bounded(2, 6);
        float vx = cos(angle) * speed;
        float vy = sin(angle) * speed;
        velocities.append(QPointF(vx, vy));
        particles.append(QPointF(xPos, yPos));
    }

    // 绘制粒子
    for (const QPointF &particle : particles) {
        QGraphicsEllipseItem *item = new QGraphicsEllipseItem(particle.x() - 2.5, particle.y() - 2.5, 5, 5);
        item->setBrush(Qt::red);
        scene()->addItem(item);
    }
}
