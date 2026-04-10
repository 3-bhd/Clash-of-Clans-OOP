#include "defenseunit.h"
#include <QTimer>
#include <QPoint>
#include <QCursor>
#include <iostream>

defenseUnit::defenseUnit(int pX, int pY, level1* level, float damage)
{
    this->damage = damage;
    healthBar = 99999;
    this->level = level;
    this->pX = pX;
    this->pY = pY;
    name = "Archer";
    ID = 3;
    QPixmap du(":/new/img/c1.png");
    du = du.scaled(150*level->ratioX,95*level->ratioY);
    setPixmap(du);

    rotating.resize(12);


    for(int i = 0; i < 12; i++) {
        rotating[i].load(":/new/img/c" + QString::number(i+1) + ".png");
    }

    for(int i = 0; i < 12; i++) {
        rotating[i] = rotating[i].scaled(100*level->ratioX, 100*level->ratioY);
    }

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [=](){
        point = QCursor::pos();
        tan = getTan();
        Animate();});
    timer->start(100);
}

float defenseUnit::getTan(){

    float x = point.x() - this->x();
    float y = this->y() - point.y();

//    std::cout << y / x << std::endl;
    return y/x;
}

void defenseUnit::Animate(){
    if (tan <= 0.726 && tan > 0 && point.y() < this->y()) {
        //std::cout << "1 tenth" << std::endl;
        setPixmap(rotating[10]);
    } else if (tan <= 3.077 && tan > 0.726 && point.y() < this->y()){
        setPixmap(rotating[9]);
        //std::cout << "2 tenth" << std::endl;
    } /*else if (tan <= -3.077 && tan > 3.077 && point.y() < this->y()){
        setPixmap(rotating[7]);
        std::cout << "3 tenth" << std::endl;
    }*/ else if (tan <= -0.726 && tan > -3.077 && point.y() < this->y()){
        setPixmap(rotating[6]);
        //std::cout << "4 tenth" << std::endl;
    } else if (tan <=  0 && tan > -0.726 && point.y() < this->y()){
        setPixmap(rotating[5]);
        //std::cout << "5 tenth" << std::endl;
    } else if (tan <= 0.726 && tan > 0 && point.y() > this->y()) {
        setPixmap(rotating[4]);
        //std::cout << "6 tenth" << std::endl;
    } else if (tan <= 3.077 && tan > 0.726 && point.y() > this->y()){
        setPixmap(rotating[4]);
        //std::cout << "7 tenth" << std::endl;
    } /*else if (tan <= -3.077 && tan > 3.077 && point.y() > this->y()){
        setPixmap(rotating[2]);
        std::cout << "8 tenth" << std::endl;
    }*/ else if (tan <= -0.726 && tan > -3.077 && point.y() > this->y()){
        setPixmap(rotating[0]);
        //std::cout << "9 tenth" << std::endl;
    } else if (tan <=  0 && tan > -0.726 && point.y() > this->y()){
        setPixmap(rotating[11]);
        //std::cout << "10 tenth" << std::endl;
    } else{
        if(point.y() < this->y()){
            setPixmap(rotating[7]);
            //std::cout << "3 tenth" << std::endl;
        } else if(point.y() > this->y()){
            setPixmap(rotating[2]);
            //std::cout << "8 tenth" << std::endl;
        }
    }
}

void defenseUnit::increaseDamage(){
    damage+=50;
    level->increaseDamage->setPlainText("Your cannon's damage has upgraded, keep killing more troops to upgrade!");
    level->increasedDamage->setPlainText("Cannon Damage:" + QString::number(damage));
}
