#ifndef DEFENSEUNIT_H
#define DEFENSEUNIT_H
#include "objectstruct.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>
#include <QKeyEvent>
#include <QPoint>
#include <QCursor>
#include "level1.h"

class defenseUnit : public QObject, public ObjectStruct
{
public:
    level1* level;
    int pX;
    int pY;
    int frame;
    QPoint point;
    std::vector <QPixmap> rotating;
    void increaseDamage();
    void Animate();
    float getTan();
    float tan;
    defenseUnit(int pX, int pY, level1* level, float damage);
};

#endif // DEFENSEUNIT_H
