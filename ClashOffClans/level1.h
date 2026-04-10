#ifndef LEVEL1_H
#define LEVEL1_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QObject>
#include <QGraphicsTextItem>
#include <vector>
#include <QMouseEvent>
#include <QKeyEvent>
#include "objectstruct.h"
#include "node.h"
#include <QMediaPlayer>
#include<QAudioOutput>


class level1 : public QGraphicsView
{
    Q_OBJECT
private:

    std::vector<std::vector<int>> v;
    std::vector<std::pair<int,int>> vaildPos;
    int rowss, row, colss, col;
    float xCastle;
    float yCastle;
    bool deadCast;
    ObjectStruct* defent;
    ObjectStruct* cast;
    bool endGame;
    bool gameOverr;
    QGraphicsPixmapItem blackk;
    QGraphicsTextItem gameDone;
    int castleV;
    void Timerr();
    QMediaPlayer* shoot;
    QAudioOutput* audioOutputShoot;

    QMediaPlayer* background;
    QAudioOutput* audioOutputBackground;

    QMediaPlayer* lWin;
    QAudioOutput* audioOutputlWin;

    int TroobGeneratingRate;
    float TroobSpeedRate;
    int TroobDamageRate;
public:
    int troopDead;
    int troopRatio;
    int castleR, castleC;
    int sec;
   level1(int TroobDamageRate, int TroobGeneratingRate, int level, float troopSpeed, float Health, float duDamagee, int dead, int troopRatio);
    ~level1();
    float rows, cols;
    float ratioX;
    float ratioY;
    float duDamage;
    float troopHealth;
    void getLevelStruct();
    int miniute;
    int levelNumber;
    QGraphicsTextItem* timeCount;
    QGraphicsTextItem* increasedDamage;
    QGraphicsTextItem* increaseDamage;
    QGraphicsTextItem* levelInfo;
    QGraphicsTextItem* troophealth;
    void setView();
    bool outBoundries(int row, int col);
    void generateTroob();
    void getVaildPos();
    QGraphicsScene* scene1;
    void generateBullet();
    void gameOver();
    void winning();
    std::vector<std::vector<ObjectStruct*>> objects;
    std::vector<node*> dijkstra(node* start, node* end);
    std::vector<std::vector<node*>> nodes;
    std::vector<std::vector<node*>> creatNodes(std::vector<std::vector<ObjectStruct*>>& objects);
    void incrementDead();
public slots:
    void mousePressEvent(QMouseEvent*);
};

#endif // LEVEL1_H
