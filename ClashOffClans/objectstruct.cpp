#include "objectstruct.h"

ObjectStruct::ObjectStruct()
{

}

ObjectStruct::~ObjectStruct(){
}


int ObjectStruct::getID(){
    return ID;
}

ObjectStruct::ObjectStruct(const ObjectStruct& other) {
    setPos(other.pos());
    healthBar = other.healthBar;
    ID = other.ID;
    id = other.id;
    name = other.name;
    setPixmap(other.pixmap());
}

void ObjectStruct::increaseDamage(){

}
