#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "bullet.h"
#include "data.h"
#include "map.h"
#include "tank.h"
using namespace base;
using namespace dynamic;

class enemyTank:public Tank
{
public:
    enemyTank(int i=0, int j=0);
    void walk();
};

#endif // ENEMYTANK_H
