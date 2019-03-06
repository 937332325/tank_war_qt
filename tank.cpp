#include "tank.h"

Tank::Tank()
{
    //
}

void Tank::turn(int d,int speed)
{
    dir=d;
    switch(dir)
    {
    case(UP):
        speedx=0;
        speedy=-speed;
        break;
    case(DOWN):
        speedx=0;
        speedy=speed;
        break;
    case(LEFT):
        speedx=-speed;
        speedy=0;
        break;
    case(RIGHT):
        speedx=speed;
        speedy=0;
        break;
    }
}

void Tank::turn(int d)
{
    turn(d,this->getSpeed());
}


void Tank::turnback()
{
    switch(dir)
    {
    case(UP):
        turn(DOWN,this->getSpeed());
        break;
    case(DOWN):
        turn(UP,this->getSpeed());
        break;
    case(LEFT):
        turn(RIGHT,this->getSpeed());
        break;
    case(RIGHT):
        turn(LEFT,this->getSpeed());
        break;
    }
}

bullet Tank::attack()
{
    bullet *bul = new bullet();
    bul->setKind(this->power);
    bul->setDir(this->dir);
    bul->setID(this->ID);
    switch(this->dir)
    {
    case(LEFT):
        bul->setSpeed(-15,0);
        bul->setPos(this->pos.x()-16,this->pos.y()+15);
        break;
    case(RIGHT):
        bul->setSpeed(15,0);
        bul->setPos(this->pos.x()+46,this->pos.y()+15);
        break;
    case(UP):
        bul->setSpeed(0,-15);
        bul->setPos(this->pos.x()+15,this->pos.y()-16);
        break;
    case(DOWN):
        bul->setSpeed(0,15);
        bul->setPos(this->pos.x()+15,this->pos.y()+46);
        break;
    }

    if( bul->getSphere().x()<0 || bul->getSphere().x()>=Width || bul->getSphere().y()<0 || bul->getSphere().y()>=Width)
    {
        bul->setBlood(0);
    }
    else
    {
        bul->setBlood(1);
    }
    return *bul;
}
