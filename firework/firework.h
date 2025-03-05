#ifndef FIREWORK_H
#define FIREWORK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QTimer>

class Firework : public QGraphicsItem
{
public:
    Firework(int x, int y, QGraphicsScene *scene);
    ~Firework();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void explode();

protected:
    void advance(int phase) override;

private:
    int xPos;
    int yPos;
    bool exploded;
    QVector<QPointF> particles;
    QVector<QPointF> velocities;
    QTimer *timer;
};

#endif // FIREWORK_H
