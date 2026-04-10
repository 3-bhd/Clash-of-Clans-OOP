#ifndef CASTLE_H
#define CASTLE_H
#include "objectstruct.h"
#include "level1.h"

class castle : public ObjectStruct
{
    level1* level;
public:
    castle(level1 * level);
  void lowerhealth(int rate);
    bool deadCastle;
};

#endif // CASTLE_H
