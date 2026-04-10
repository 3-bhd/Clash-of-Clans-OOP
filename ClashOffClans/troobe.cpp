#include "troobe.h"
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QList>
#include "fence.h"
#include "castle.h"
#include <iostream>


troobe::troobe(float xCastle, float yCastle, level1* level, int row, int col, int Damage, float Speed, float health, ObjectStruct* defent)
{
    defense = defent;
    this->healthBar = health;
    this->troopSpeed = Speed;
    TroobDamageRate = Damage;
    crack = new QMediaPlayer(this);
    audioOutputCrack = new QAudioOutput(this);

    crack->setAudioOutput(audioOutputCrack);
    crack->setSource(QUrl("qrc:/new/audio/Cracking.mp3"));
    audioOutputCrack->setVolume(50);

    this->xCastle = xCastle + (300*level->ratioX) / 2;
    this->yCastle = yCastle + (300*level->ratioY) / 2;
    this->level = level;

    frame = 0;
    frameR = 0;
    dead = false;
    direction = true;

    std::cout << "troop position:" << row << ", " << col << std::endl;

    nodes = creatNodes(level->objects);
    node* start = nodes[row][col];
    node* end = nodes[level->castleR][level->castleC];

    std::vector<node*> path = dijkstra(start, end);

//    for (auto it = path.rbegin(); it != path.rend(); it++) {
//        std::cout << (*it)->object.id << ": ";
//        std::cout << "(" << (*it)->object.x() << ", " << (*it)->object.y() << ")" << std::endl;
//    }
//    std::cout << std::endl;

    path[0]->object.setPos(this->xCastle,this->yCastle);

    itr = path.size()-2;
    currNode = path[itr];


    walkingAnimation.resize(5);
    walkingAnimationR.resize(5);
    distance = sqrt(pow(this->x() - currNode->object.x(), 2) + pow(this->y() - currNode->object.y(), 2));

    dX = 0;
    dY = 0;

    walkingAnimation[0].load(":/new/img/TrobsW-standing.png");
    walkingAnimation[1].load(":/new/img/TrobsW-V1.png");
    walkingAnimation[2].load(":/new/img/TrobsW-V2.png");
    walkingAnimation[3].load(":/new/img/TrobsW-V3.png");
    walkingAnimation[4].load(":/new/img/TrobsW-V4.png");

    walkingAnimationR[0].load(":/new/img/TrobsW-standing-R.png");
    walkingAnimationR[1].load(":/new/img/TrobsW-V1-R.png");
    walkingAnimationR[2].load(":/new/img/TrobsW-V2-R.png");
    walkingAnimationR[3].load(":/new/img/TrobsW-V3-R.png");
    walkingAnimationR[4].load(":/new/img/TrobsW-V4-R.png");

    attackimg[0].load(":/new/img/troope-a-1.png");
    attackimg[1].load(":/new/img/troope-a-2.png");
    attackimg[2].load(":/new/img/troope-a-1-r.png");
    attackimg[3].load(":/new/img/troope-a-2-r.png");

    dying[0].load(":/new/img/troope-d1.png");
    dying[1].load(":/new/img/troope-d1-r.png");
    dying[2].load(":/new/img/troope-d2.png");
    dying[3].load(":/new/img/troope-d2-r.png");

    for(int i = 0; i<4; i++){
        dying[i] = dying[i].scaled(60*level->ratioX, 60* level->ratioY);
    }

    for(int i = 0; i < 4; i++){
        attackimg[i] = attackimg[i].scaled(60*level->ratioX, 60* level->ratioY);
    }

    for(int i = 0; i < 5; i++){
        walkingAnimation[i] = walkingAnimation[i].scaled(60*level->ratioX, 60* level->ratioY);
        walkingAnimationR[i] = walkingAnimationR[i].scaled(60*level->ratioX, 60*level->ratioY);
    }

    setPos((col*130) * level->ratioX,(row*80)* level->ratioY);
    setPixmap(walkingAnimation[0]);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [=](){

        distance = sqrt(pow(this->x() - currNode->object.x(), 2) + pow(this->y() - currNode->object.y(), 2));
        if(distance < 30)
        {
            if(itr != 0){
                itr--;
                currNode = path[itr];
            }
        }
        if(dead != true){
            move();
        }
    });
    timer->start(troopSpeed);
}

void troobe::move(){
    dX = (currNode->object.x() - this->x()) / distance;
    dY = (currNode->object.y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;


    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (fence* fenceItem = dynamic_cast<fence*>(colliding_items[i])) {
            if(newX > this->x()){
                attack(1);
            }
            else{
                attack(3);
            }
            stepBack();
            fenceItem->lowerhealth(TroobDamageRate);
            crack->play();
            return;
        }
        else if(castle* castleItem = dynamic_cast<castle*>(colliding_items[i])){
            if(newX > this->x()){
                attack(1);
            }
            else{
                attack(3);
            }
            stepBack();
            castleItem->lowerhealth(TroobDamageRate);
            crack->play();
            return;
        }
    }


//    std::cout<< currNode->object.x() - this->x() << std::endl;
//    std::cout<< currNode->object.y() - this->y() << std::endl;

//    std::cout<< currNode->object.x() << std::endl;
//    std::cout<< currNode->object.y() << std::endl;



    if(newX > this->x()){
    setPos(newX, newY);
    animate();
    }
    else if (newX < this->x()){
    setPos(newX, newY);
    animateR();
    } else{
        if(this->x() < 500){
            setPos(newX, newY);
            animate();
        } else if(this->x() > 500){
            setPos(newX, newY);
            animateR();
        }
    }
}

void troobe::stepBack(){

    dX = (currNode->object.x() - this->x()) / distance;
    dY = (currNode->object.y() - this->y()) / distance;

    float newX = this->x() - 5*dX;
    float newY = this->y() - 5*dY;
    setPos(newX, newY);
}

void troobe::animate(){
    int curr = frame % 5;
    setPixmap(walkingAnimation[curr]);
    frame++;
    direction = true;
}

void troobe::animateR(){
    int curr = frameR % 5;
    setPixmap(walkingAnimationR[curr]);
    frameR++;
    direction = false;
}

std::vector<node *> troobe::dijkstra(node *start, node *end)
{
    if (start == nullptr || end == nullptr) {
        std::cout << "Error: start and end nodes must not be null" << std::endl;
        return std::vector<node*>();
    }

    std::vector<node*> openSet, closedSet;
    openSet.push_back(start);
    while (!openSet.empty()) {
        node* currentNode = *min_element(openSet.begin(), openSet.end(), [](node* lhs, node* rhs) {
            return lhs->gCost < rhs->gCost;
        });

        if (currentNode->object.id == end->object.id) {
            std::vector<node*> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            return path;
        }

        openSet.erase(remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
        closedSet.push_back(currentNode);

        for (auto& connection : currentNode->connections) {
            node* neighbor = connection.second.first;
            if (neighbor == nullptr) {
                std::cout << "Error: Connection contains null node" << std::endl;
                continue;
            }
            if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) continue;

            auto neighborPair = currentNode->getNeighbor(neighbor->object.id);
            if (neighborPair.first == nullptr) {
                std::cout << "Error: Neighbor not found in getNeighbor" << std::endl;
                continue;
            }
            float newMovementCostToNeighbor = currentNode->gCost + neighborPair.second;
            if (newMovementCostToNeighbor < neighbor->gCost || std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                neighbor->gCost = newMovementCostToNeighbor;
                neighbor->parent = currentNode;

                if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                    openSet.push_back(neighbor);
                }
            }
        }
    }

    std::cout << "No path to end node found" << std::endl;
    return std::vector<node*>();  // return an empty path if there's no path to the end
}

std::vector<std::vector<node *> > troobe::creatNodes(std::vector<std::vector<ObjectStruct *> > &objects)
{
    int rows = objects.size();
    int cols = objects[0].size();

    std::vector<std::vector<node*>> nodes(rows, std::vector<node*>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            nodes[i][j] = new node(objects[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0) nodes[i][j]->addConnection(nodes[i-1][j]); // Up
            if (i < rows - 1) nodes[i][j]->addConnection(nodes[i+1][j]); // Down
            if (j > 0) nodes[i][j]->addConnection(nodes[i][j-1]); // Left
            if (j < cols - 1) nodes[i][j]->addConnection(nodes[i][j+1]); // Right

            // Diagonal connections
            // if (i > 0 && j > 0) nodes[i][j]->addConnection(nodes[i-1][j-1]); // Top-left
            // if (i > 0 && j < cols - 1) nodes[i][j]->addConnection(nodes[i-1][j+1]); // Top-right
            // if (i < rows - 1 && j > 0) nodes[i][j]->addConnection(nodes[i+1][j-1]); // Bottom-left
            // if (i < rows - 1 && j < cols - 1) nodes[i][j]->addConnection(nodes[i+1][j+1]); // Bottom-right
        }
    }

    return nodes;
}

void troobe::attack(int frame){

     setPixmap(attackimg[frame]);
}

void troobe::delay(int sec)
{
      QTime dieTime=  QTime::currentTime().addMSecs(sec);
      while (QTime::currentTime() < dieTime)
      {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
      }
}

void troobe::lowerHealth(float damage)
{
    healthBar-=damage;
    if(healthBar <= 0){
        dead = true;
        delay(500);
        level->incrementDead();
        if(level->troopDead == 20){
            defense->increaseDamage();
        }
        die();
    }
}

void troobe::die(){

      if(direction == true){
        setPixmap(dying[0]);
        delay(300);
        setPixmap(dying[2]);
        delay(300);
      }
      else{
        setPixmap(dying[1]);
        delay(300);
        setPixmap(dying[3]);
        delay(300);

      }
      delete this;
}

troobe::~troobe()
{
    for (auto& row : nodes) {
        for (auto& node : row) {
            delete node;
        }
    }
    delete timer;
}
