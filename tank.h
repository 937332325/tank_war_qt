#ifndef TANK_H
#define TANK_H

#include "base.h"
#include "bullet.h"
#include "dynamic.h"
using namespace base;
using namespace dynamic;

class Tank:public Dynamic
{
public:
    Tank();
    void turn(int d);
    void turn(int d, int speed);
    void turnback();
    bullet attack();
};

#endif // TANK_H
