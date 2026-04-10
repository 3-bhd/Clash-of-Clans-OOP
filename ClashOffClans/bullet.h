#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QCursor>
#include "objectstruct.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QTime>
#include <QObject>
#include "level1.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class Bullet : public QGraphicsPixmapItem, public QObject
{
private:
    int originX;
    int originY;
    float hip;
    float cos;
    float sin;
    level1* level;
    ObjectStruct* defense;
    QTimer *timer;

    QMediaPlayer* ah;
    QAudioOutput* audioOutputAh;
public:
    QPoint point;
    Bullet(ObjectStruct* defense, level1* level);
    void getMousePosition();
    void shoot();
    void getHip();
    ~Bullet();
};

#endif // BULLET_H
