#include "enemytank.h"

enemyTank::enemyTank(int i,int j)
{
    kind=qrand()%3+1;
    setPos(i*PixWidth,j*PixHeight);
    ID=ENEMYTANK;
    dir=DOWN;
    width=PixWidth;
    height=PixHeight;
    rectSphere.setRect(i*PixWidth,j*PixHeight,width,height);
    switch (kind)
    {
    case (ENEMY_TANK_HIGHT_ATTACK):
        blood=BLOOD_LOW;
        power=HIGHTPOWER;
        turn(DOWN,SPEED_MID);
        break;
    case (ENEMY_TANK_HIGHT_BLOOD):
        blood=BLOOD_HIGHT;
        power=LOWPOWER;
        turn(DOWN,SPEED_MID);
        break;
    case (ENEMY_TANK_HIGHT_SPEED):
        blood=BLOOD_MID;
        power=LOWPOWER;
        turn(DOWN,SPEED_HIGHT);
        break;
    }
}

void enemyTank::walk()
{
    if(blood==0)
    {
        return ;
    }
    else
    {
        move();
    }
}
