#ifndef LINKLIST_H
#define LINKLIST_H

#include "bullet.h"
#include "enemytank.h"
#include "mytank.h"

//敌方坦克数量
#define ENEMY_TANK_NUMBER 3
using namespace base;
using namespace dynamic;

struct BulletNode
{
    bullet bul;
    BulletNode* next;
};

class BulletList
{
private:
    BulletNode *head;
    BulletNode *tail;
    int length;
public:
    BulletList();
    void addBullet(bullet bul);
    void deleteBullet(BulletNode *p);   //删除p
    bool isEmpty();
    BulletNode* getHead();
    void paint(QPainter *p);
};

class EnemyTankList
{
private:
    int length;
    int death_sum;
public:
    enemyTank enemyArmy[ENEMY_TANK_NUMBER];
    EnemyTankList();
    void addEnemyTank();
    void deleteEnemyTank(int i);
    bool isEmpty();
    int getSize();
    int getDeathSum();
    void paint(QPainter *pa);
};

class MyTankList
{
private:
    bool isdouble;
    int rebirth_times[2];
public:
    mytank myArmy[2];
    MyTankList(bool isDouble=false);
    bool getIsDouble();
    void Rebirth(int i);
    int getRebirthTimes(int i);
    void paint(QPainter *p);
};

#endif // LINKLIST

