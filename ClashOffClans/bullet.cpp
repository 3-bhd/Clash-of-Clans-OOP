#include "bullet.h"
#include <QPoint>
#include <QCursor>
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>
#include <iostream>
#include <cmath>
#include "troobe.h"
#include <QMediaPlayer>
#include <QtMultiMedia>
#include<QAudioOutput>

Bullet::Bullet(ObjectStruct* defensee, level1* level)
{

    ah = new QMediaPlayer(this);
    audioOutputAh = new QAudioOutput(this);

    ah->setAudioOutput(audioOutputAh);
    ah->setSource(QUrl("qrc:/new/audio/AH.mp3"));
    audioOutputAh->setVolume(50);

    this->level = level;
    this->defense = defensee;
    originX = defense->x();
    originY = defense->y();
    point = QCursor::pos();
    QPixmap BulletPic(":/new/img/bullet.png");
    BulletPic = BulletPic.scaled(40*level->ratioX,40*level->ratioY);
    setPixmap(BulletPic);

    getHip();
    cos = ((originX - point.x()) / hip) * 10;
    sin = ((originY - point.y()) / hip) * 10;

    timer = new QTimer();
    connect(timer,&QTimer::timeout, this, [=](){shoot();});
    timer->start(15);
}

void delay(int sec)
{
    QTime dieTime=  QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Bullet::shoot(){
    setPos(x()-cos,y()-sin);
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (troobe* troobItem = dynamic_cast<troobe*>(colliding_items[i])) {
            this->hide();
            if(troobItem->dead == false){
                ah->play();
                troobItem->lowerHealth(defense->damage);
            }
            delete this;
            return;
        }
    }
    if(this->x() < 0 || this->y() < 0 || this->x() > 1000 || this->y() > 800){
        delete this;
        return;
    }
}

void Bullet::getHip(){

    float xf = point.x();
    float yf = point.y();

    float xff = std::pow((xf - originX),2);
    float yff = std::pow((yf - originY), 2);

    hip = std::sqrt((xff + yff));
}

Bullet::~Bullet()
{
    delete timer;
}
