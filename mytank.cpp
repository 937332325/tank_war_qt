#include "mytank.h"

mytank::mytank(int i,int j)
{
    this->setPos(i*PixWidth,j*PixHeight);
    this->width=PixWidth;
    this->height=PixHeight;
    this->rectSphere.setRect(4*PixWidth,12*PixHeight,width,height);
    this->dir = UP;
    this->kind = 0;
    this->speedx = 0;
    this->speedy = -SPEED_HIGHT;
    this->blood = BLOOD_INF;
    this->ismove=true;
    this->ID=MYTANK;
}

void mytank::turn(int d)
{
    Tank::turn(d,this->getSpeed());
};

void mytank::move()
{
    if (ismove==true)
    {
        qDebug()<<"true"<<endl;
        if (this->collision(glb.map,glb.tool))
        {
            qDebug()<<"collision."<<endl;
            return;
        }
        else
        {
            Dynamic::move();
        }
    }
}

void mytank::move1()
{
    if(ismove==true)
    {
        Dynamic::move();
    }
}

void mytank::startMove()
{
    this->ismove = true;
}

void mytank::stopMove()
{
    this->ismove = false;
}


bool mytank::collision(Map *map,gametool *&tool)
{
    //新建一个对象来判断有没有碰撞
    mytank tmp = *this;
    tmp.move1();

    //是否与地图块碰撞
    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            if(map->isPenetration1(i*PixWidth,j*PixHeight)
                    )
            {
                qDebug("boom");
                return true;
            }
        }
    }
    if (tmp.pos.x()>tool->x-SegWidth&&tmp.pos.x()<tool->x+SegWidth&&tmp.pos.y()>tool->y-SegWidth&&tmp.pos.y()<tool->y+SegWidth)
    {
        tool->queue1.push(tool->tooltype);
        //qDebug("enqueue");
        tool->flag = false;
    }
    //&&tmp.collision2(tmp,i,j)
    if (tmp.rectSphere.left()<0||
        tmp.rectSphere.right()>Width||
        tmp.rectSphere.top()<0||
        tmp.rectSphere.bottom()>Height)
    {
        qDebug("boom");
        return true;
    }
    return false;
}

bool mytank::collision2(mytank &myTank, int i,int j)
{
    //返回true为碰撞，返回false为不碰撞
    int top = j * PixWidth;
    int bottom = (j+1) * PixWidth - 1;
    int left = i * PixWidth;
    int right = (i+1) * PixWidth - 1;
    if (left>myTank.rectSphere.right()
        ||right<myTank.rectSphere.left()
        ||top>myTank.rectSphere.bottom()
        ||bottom<myTank.rectSphere.top())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void mytank::display(QPainter *paint)
{
    QPixmap pix;
    pix.load(playertank[dir]);

    paint->drawPixmap(this->rectSphere,pix);
}
