#include "fence.h"
#include <QList>

fence::fence(level1* level)
{
    this->level = level;
    name = "fence";
    ID = 1;
    healthBar = 1500;
    QPixmap fencep(":/new/img/fenceUnit.png");
    fencep = fencep.scaled(100*level->ratioX,80*level->ratioY);
    setPixmap(fencep);
}

void fence::lowerhealth(int rate){
    healthBar-=rate;
    if(healthBar <= 0){
        this->hide();
    }
}
