#ifndef OBJECTSTRUCT_H
#define OBJECTSTRUCT_H
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>

class ObjectStruct : public QGraphicsPixmapItem
{
public:
    float healthBar;
    int ID;
    std::string id;
    QString name;
    float damage;
public:
    ObjectStruct();
    ObjectStruct(const ObjectStruct& other); // copy constructor
    ~ObjectStruct();
    int getID();
    virtual void increaseDamage();
};

#endif // OBJECTSTRUCT_H
