#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class AnimatedSprite : public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimatedSprite(const QString &spriteSheetPath, int frameWidth, int frameHeight, int numFrames, QObject *parent = nullptr);
    void startAnimation(int interval);
    void stopAnimation();

private slots:
    void nextFrame();

private:
    QPixmap spriteSheet;
    int frameWidth;
    int frameHeight;
    int numFrames;
    int currentFrame;
    QTimer *timer;
};

#endif // ANIMATEDSPRITE_H
