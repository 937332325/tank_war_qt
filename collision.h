#ifndef COLLISION_H
#define COLLISION_H

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

#include "data.h"
#include "base.h"
#include "bullet.h"
#include "enemytank.h"
#include "linklist.h"
#include "map.h"
#include "mytank.h"

using namespace base;
using namespace dynamic;

class Collision
{
private:
    BulletList bulletList;
    EnemyTankList enemyTanklist;
    MyTankList myTanklist;

    //分开写有利于坦克得到道具后对障碍的行为不同而修改函数
    bool TankToBrick(Tank *&tank);
    bool TankToSteel(Tank *&tank);
    bool TankToWater(Tank *&tank);
    bool TankToJungle(Tank *&tank);
    bool TankToFlag(Tank *&tank);

    bool BulletToBrick(bullet &bul, Base &m);
    bool BulletToSteel(bullet &bul,Base &m);
    bool BulletToJungle(bullet &bul, Base &m);
    bool BulletToWater(bullet &bul, Base &m);
    bool BulletToFlag(bullet &bul, Base &m);
    bool BulletToObstacleHelp(bullet &bul, Base &m);

public:
    Collision(bool isDouble=false);//参数默认为单人游戏，true即为双人游戏
    void addBullet(bullet bul);
    void addEnemyTank();
    bool isOutOfBound(Dynamic &dynamic);//判断是否越界
    bool TankToObstacle(Tank &tank, Map &m);
    bool TankToTankList(Tank &tank,EnemyTankList &e,int i=-1);
    bool BulletToTank(bullet &bul,Tank &tank);
    bool BulletToObstacle(bullet &bul, Map &m);
    void CheckBulletList(Map &m);
    void CheckEnemyTankList(Map &m);
    void CheckMyTankList();
    void paint(QPainter *p);
    int getEnemyDeathSum(); //得到敌方坦克的死亡数
    int getRebirthSum(int i=0);//得到我方坦克的生存数，i=0是P1玩家，i=1是P2玩家。
    bool getIsDouble();//是否为双人游戏
    void controlMyTank(QKeyEvent *event,Map &m);
    bool doublespeed;
};

#endif // COLLISION

