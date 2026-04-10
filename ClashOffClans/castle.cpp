#include "castle.h"
castle::castle(level1 * level)
{
    name = "Castle";
    ID = 2;
    healthBar = 3000;
    this->level = level;
    QPixmap castlep(":/new/img/castle.png");
    castlep = castlep.scaled(200*level->ratioX,200*level->ratioY);
    setPixmap(castlep);
}

void castle::lowerhealth(int rate){
    healthBar-=rate;
    if(healthBar <= 0){
        level->gameOver();
        this->hide();
    }
}

