#include "base.h"

Base::Base()
{
    width=0;
    height=0;
    pos.setX(0);
    pos.setY(0);
    rectSphere.setRect(0,0,0,0);
    kind=0;
}

int Base::getKind() const
{
    return kind;
}

QPoint Base::getPos() const
{
    return pos;
}

QRect Base::getSphere() const
{
    return rectSphere;
}

void Base::setPos(int x, int y)
{
    pos.setX(x);
    pos.setY(y);
    rectSphere.setRect(x,y,width,height);
}

void Base::setKind(int k)
{
    kind=k;
}

bool Base::penetrate(const QRect rect1, const QRect rect2)
{
    //返回true为碰撞，返回false为不碰撞
    if(rect1.left()>rect2.right()
       ||rect1.right()<rect2.left()
       ||rect1.top()>rect2.bottom()
       ||rect1.bottom()<rect2.top())
    {
        return false;
    }
    else
        return true;
}

bool Base::judge(const Base &base)const
{
    if (base.kind==1)
        return false;
    return true;
}

void Base::display(QPainter &paint)
{

};
