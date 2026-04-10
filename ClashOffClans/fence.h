#ifndef FENCE_H
#define FENCE_H
#include "objectstruct.h"
#include "level1.h"

class fence : public ObjectStruct
{
    level1* level;
public:
    fence(level1* level);
     void lowerhealth(int rate);
};

#endif // FENCE_H
