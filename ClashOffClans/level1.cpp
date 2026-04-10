#include "level1.h"
#include "castle.h"
#include "fence.h"
#include "defenseunit.h"
#include "empty.h"
#include "bullet.h"
#include <QTextStream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include "troobe.h"
#include <ctime>
#include <cstdlib>
#include <QTimer>
#include<QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QtMultiMedia>
#include<QAudioOutput>
#include "levelup.h"
#include "loosing.h"



level1::level1(int TroobDamageRate, int TroobGeneratingRate, int level, float troopSpeed, float Health, float duDamagee, int dead, int troopRatio)
{
    this->troopRatio = troopRatio;
    this->troopDead = dead;
    this->duDamage = duDamagee;
    this->troopHealth = Health;
    this->TroobSpeedRate = troopSpeed;
    levelNumber = level;
    this->TroobDamageRate = TroobDamageRate;
    this->TroobGeneratingRate = TroobGeneratingRate;

    shoot = new QMediaPlayer(this);
    audioOutputShoot = new QAudioOutput(this);

    this->miniute = 1;

    shoot->setAudioOutput(audioOutputShoot);
    shoot->setSource(QUrl("qrc:/new/audio/shoot.mp3"));
    audioOutputShoot->setVolume(50);


    lWin = new QMediaPlayer(this);
    audioOutputlWin = new QAudioOutput(this);

    lWin->setAudioOutput(audioOutputlWin);
    lWin->setSource(QUrl("qrc:/new/audio/LastWin.mp3"));
    audioOutputlWin->setVolume(100);

    background = new QMediaPlayer(this);
    audioOutputBackground = new QAudioOutput(this);
    background->setAudioOutput(audioOutputBackground);

    background->setSource(QUrl("qrc:/new/audio/Background.mp3"));
    audioOutputBackground->setVolume(40);
    rows = 0;
    cols = 0;
    rowss = 0;
    colss = 0;
    row = 0;
    col = 0;
    getLevelStruct();
    deadCast = false;
    endGame = false;
    gameOverr =  false;
    rowss = rows;
    colss = cols;
    sec = 0;

    scene1 = new QGraphicsScene;
    setFixedSize(1000, 800);
    scene1->setSceneRect(0,0,1000,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap grass(":/new/img/grass.jpg");
    grass = grass.scaled(1000, 800);
    QGraphicsPixmapItem* grasss = new QGraphicsPixmapItem;
    grasss->setPixmap(grass);
    grasss->setPos(0,0);
    scene1->addItem(grasss);

    gameDone.setFont(QFont("times", 30));
    gameDone.setOpacity(100);

    timeCount = new QGraphicsTextItem;
    timeCount->setFont(QFont("times", 12));
    timeCount->setPos(800, 10);
    timeCount->setPlainText("Timer:" + QString::number(miniute) + ":" + QString::number(sec));
    timeCount->setDefaultTextColor(Qt::red);
    scene1->addItem(timeCount);

    levelInfo = new QGraphicsTextItem;
    levelInfo->setFont(QFont("times", 12));
    levelInfo->setPos(30, 10);
    levelInfo->setPlainText("Level:" + QString::number(levelNumber));
    levelInfo->setDefaultTextColor(Qt::red);
    scene1->addItem(levelInfo);

    increasedDamage = new QGraphicsTextItem;
    increasedDamage->setFont(QFont("times", 12));
    increasedDamage->setPos(30, 25);
    increasedDamage->setPlainText("Cannon Damage:" + QString::number(duDamage));
    increasedDamage->setDefaultTextColor(Qt::red);
    scene1->addItem(increasedDamage);

    increaseDamage= new QGraphicsTextItem;
    increaseDamage->setFont(QFont("times", 12));
    increaseDamage->setPos(30, 40);
    increaseDamage->setPlainText("Kill 20 troops to upgrade your cannon!");
    increaseDamage->setDefaultTextColor(Qt::red);
    scene1->addItem(increaseDamage);

    troophealth = new QGraphicsTextItem;
    troophealth->setFont(QFont("times", 12));
    troophealth->setPos(400, 10);
    troophealth->setPlainText("Troops' health:" + QString::number(troopHealth));
    troophealth->setDefaultTextColor(Qt::red);
    scene1->addItem(troophealth);

    ratioX = 10 / cols;
    ratioY =  10 / rows;
    objects.resize(rows);
    for(int i = 0; i < rows; i++){
        objects[i].resize(cols);
    }

    setView();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            objects[i][j]->id =  "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
        }
    }

    getVaildPos();

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [=](){generateTroob();});
    timer->start(TroobGeneratingRate);

    QTimer *timerr = new QTimer(this);
    connect(timerr,&QTimer::timeout, this, [=](){
        winning();
    });
    timerr->start(miniute * 60 * 1000);

    QTimer *timerrr = new QTimer(this);
    connect(timerrr,&QTimer::timeout, this, [=](){Timerr();});
    timerrr->start(1000);

    setScene(scene1);

     background->play();
}

level1::~level1()
{
    delete timeCount;
    delete levelInfo;
    delete increaseDamage;
    delete increasedDamage;
    delete troophealth;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            delete objects[i][j];
        }
    }
}

void level1::getLevelStruct(){
    QFile file(":/new/text/level1Struct.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(',');
        std::vector<int> temp;
        for (const QString& value : values) {
            temp.push_back(value.toInt());
        }
        v.push_back(temp);
        rows++;
        cols = temp.size();
    }
    file.close();
}

void level1::setView(){
    int x = 0;
    int y = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(v[i][j] == 0){
                objects[i][j] = new empty();
                objects[i][j]->setPos(x,y);
            }
            if(v[i][j] == 1){
                objects[i][j] = new fence(this);
                objects[i][j]->setPos(x,y);
                scene1->addItem(objects[i][j]);
            }
            if(v[i][j] == 2){
                objects[i][j] = new castle(this);
                objects[i][j]->setPos(x,y);
                xCastle = x;
                yCastle = y;
                scene1->addItem(objects[i][j]);
                castleR = i;
                castleC = j;
                castleV = j;
                cast = objects[i][j];
            }
            if(v[i][j] == 3){
                objects[i][j] = new defenseUnit(x, y, this, duDamage);
                objects[i][j]->setPos(x,y);
                scene1->addItem(objects[i][j]);
                defent = objects[i][j];
            }
            if(v[i][j] == 4){
                objects[i][j] = new empty();
                objects[i][j]->setPos(x,y);
            }
            x = x + (100*ratioX);
        }
        x=0;
        y = y + (80*ratioY);
    }
}

bool level1::outBoundries(int row, int col){
    if(v[row][col] == 4) return true;
    return false;
}

void level1::getVaildPos(){

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(v[i][j] == 4){
                vaildPos.push_back({i,j});
//                std::cout << "this i: " << i << " this j:" << j << std::endl;

            }
        }
    }
}


void level1::generateTroob(){
    if(gameOverr == true){
        return;
    }
    srand(time(0));
    int pos = rand() % (vaildPos.size() - 1);
    row = vaildPos[pos].first;
    col = vaildPos[pos].second;

    troobe* troob = new troobe(xCastle, yCastle, this, row, col,TroobDamageRate, TroobSpeedRate, troopHealth, defent);
    scene1->addItem(troob);
}

void level1::generateBullet(){
    Bullet* bull = new Bullet(defent, this);
    //std::cout << bull->point.x() << "  " << bull->point.y() << std::endl;
    bull->setPos(defent->x(), defent->y());
    scene1->addItem(bull);
}

void level1::gameOver()
{
    if(gameOverr == true) return;
    if(gameOverr == true) return;
    Loosing* lost = new Loosing(TroobDamageRate, TroobGeneratingRate,levelNumber, TroobSpeedRate, troopHealth, duDamage, troopDead, troopRatio);

    gameOverr = true;
    hide();

    lost->show();
    delete this;
}

void level1::winning(){
    if(gameOverr == true) return;

    if(levelNumber >= 5){
         background->stop();
         lWin->play();
        QPixmap black(":/new/img/black.jpg");
        black = black.scaled(1000, 800);
        blackk.setPixmap(black);
        blackk.setPos(0,0);
        blackk.setOpacity(0.8);
        scene1->addItem(&blackk);
        QGraphicsTextItem* gameDone = new QGraphicsTextItem;
        gameDone->setFont(QFont("times", 30));
        gameDone->setPos(400, 350);
        gameDone->setPlainText("YOU WON THE GAME!");
        gameDone->setDefaultTextColor(Qt::green);
        scene1->addItem(gameDone);
        gameOverr = true;

    }
    else{
        gameOverr = true;
        hide();
        LevelUp* NextLevel = new LevelUp(duDamage, troopDead, troopRatio);
        NextLevel->show();
        delete this;
    }
}

void level1::incrementDead()
{
    troopDead++;
    if(troopDead == 21){
        troopDead = 1;
        troopRatio += 1;
    }
    std::cout << troopRatio *20 + troopDead << std::endl;
}

void level1::mousePressEvent(QMouseEvent*)
{
     shoot->play();
    generateBullet();
}

void level1::Timerr()
{
    if(sec == 0){
        miniute--;
        sec = 60;
    }
    sec--;
    timeCount->setPlainText("Timer:" + QString::number(miniute) + ":" + QString::number(sec));
}

