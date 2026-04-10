#ifndef NODE_H
#define NODE_H
#include "objectstruct.h"
#include <map>


class node
{
public:
    node(ObjectStruct* _object);
    ObjectStruct object;
    float gCost, hCost;
    node* parent;
    std::map<std::string, std::pair<node*, int>> connections; // Store both the node and the weight
    float fCost() const;
    void addConnection(node* node1);
    std::pair<node*, int> getNeighbor(std::string);
};

#endif // NODE_H
