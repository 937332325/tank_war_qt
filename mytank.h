#ifndef MYTANK_H
#define MYTANK_H

#include <QDebug>
#include <QString>

#include "bullet.h"
#include "data.h"
#include "gametool.h"
#include "map.h"
#include "tank.h"
using namespace base;
using namespace dynamic;
class mytank:public Tank
{
public:
    bool ismove;
    mytank(int i=4, int j=12);
    QString playertank[4]={":/new/icon/pixs/p1tankU.png",
                           ":/new/icon/pixs/p1tankD.png",
                           ":/new/icon/pixs/p1tankL.png",
                           ":/new/icon/pixs/p1tankR.png"};
    void turn(int d);
    void move();
    void move1();
    void startMove();//设置移动状态为开
    void stopMove();//设置移动状态为关 放开按键就停止了
    bool collision(Map *map,gametool *&tool);
    bool collision2(mytank &myTank,int i,int j);
    void display(QPainter *paint);
};

#endif // MYTANK_H
