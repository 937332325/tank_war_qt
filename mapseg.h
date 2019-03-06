#ifndef MAPSEG_H
#define MAPSEG_H

#include <QImage>

#include "base.h"
#include "data.h"


class mapSeg:public Base
{
public:

    mapSeg(int=0,int=0);
    void modifyMapSeg(int i,int j);

    virtual void display(QPainter &paint){}//绘图
    virtual void move(){}//移动,无需移动，函数体为空
    //int kind;//地图块种类

protected:
    virtual void calSphere();
};

#endif // MAPSEG_H
