#include <dynamic.h>
#include <qDebug>
Dynamic::Dynamic()
{
    blood=0;
    power=dynamic::LOWPOWER;
    dir=dynamic::UP;
    speedx=0;
    speedy=0;
    num = 1;
}

int Dynamic::getBlood()
{
    return blood;
}

int Dynamic::getPower()
{
    return power;
}

int Dynamic::getSpeedX()
{
    return speedx*num;
}

int Dynamic::getSpeedY()
{
    return speedy*num;
}

int Dynamic::getSpeed()
{
    return abs(speedx+speedy);
}

int Dynamic::getDir()
{
    return dir;
}

int Dynamic::getID()
{
    return ID;
}

void Dynamic::setBlood(int b)
{
    blood=b;
}

void Dynamic::setPower(int p)
{
    power=p;
}

void Dynamic::setDir(int d)
{
    dir=d;
}

void Dynamic::setSpeed(int x, int y)
{
    speedx=x;
    speedy=y;
}

void Dynamic::setID(int id)
{
    ID=id;
}

bool Dynamic::isAlive()
{
   return (blood<=0?false:true);
}

void Dynamic::move()
{
    pos.setX(pos.x()+speedx*num);
    pos.setY(pos.y()+speedy*num);
    rectSphere.setRect(pos.x(),pos.y(),width,height);
}
