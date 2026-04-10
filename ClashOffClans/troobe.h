#ifndef TROOBE_H
#define TROOBE_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <vector>
#include "level1.h"
#include <QTimer>
#include "objectstruct.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class troobe: public QGraphicsPixmapItem, public QObject
{
public:
    troobe(float xCastle, float yCastle, level1* level, int row, int col, int damage, float Speed, float health, ObjectStruct* defent);
//    bool die();
    void move();
    void stepBack();
    void animate();
    void animateR();
    void attack(int frame);
    void die();
    void delay(int sec);
    void lowerHealth(float damage);
    bool dead;
    ~troobe();
private:
    ObjectStruct* defense;
    float healthBar;
    std::vector<node*> path;
    node* currNode;
    int itr;
    std::vector<std::vector<node*>> nodes;
    int TroobDamageRate;
    int xCastle;
    int yCastle;
    int frame;
    int frameR;
    float dX, dY, Delta;
    float distance;
    bool direction;
    level1* level;
    std::vector<node*> dijkstra(node* start, node* end);
    std::vector<std::vector<node*>> creatNodes(std::vector<std::vector<ObjectStruct*>>& objects);
    std::vector<QPixmap> walkingAnimation;
    std::vector<QPixmap> walkingAnimationR;
    QPixmap attackimg[4];
    QPixmap dying[4];
    QTimer *timer;
    float troopSpeed;

    QMediaPlayer* crack;
    QAudioOutput* audioOutputCrack;
};

#endif // TROOBE_H
