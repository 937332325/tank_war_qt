#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "base.h"

namespace dynamic
{
    //方向
    enum Direction
    {
        UP=0,
        DOWN=1,
        LEFT=2,
        RIGHT=3,
        STATIC=4
    };
    //血量
    enum Blood
    {
        BLOOD_LOW=1,
        BLOOD_MID=2,
        BLOOD_HIGHT=3,
        BLOOD_INF=20
    };
    //攻击力
    enum Power
    {
        LOWPOWER=1,
        MIDPOWER=1,
        HIGHTPOWER=1
    };
    //速度
    enum Speed
    {
        SPEED_LOW=1,
        SPEED_MID=3,
        SPEED_HIGHT=5,
    };
    //类型
    enum Type
    {
        MYTANK=0,
        ENEMYTANK=1
    };
}

class Dynamic:public Base
{
protected:
    int blood;//血量
    int power;//攻击力
    int speedx;
    int speedy;//移动速度
    int dir;//移动方向
    int ID;
public:
    Dynamic();
    int getBlood();
    int getPower();
    int getSpeedX();
    int getSpeedY();
    int getSpeed();
    int getDir();
    int getID();

    void setBlood(int b);
    void setPower(int p);
    void setDir(int d);
    void setSpeed(int x,int y);
    void setID(int id);

    bool isAlive();

    void move();//用于移动
    int num;
};

#endif // DYNAMIC_H
