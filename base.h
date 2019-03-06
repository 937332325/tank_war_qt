#ifndef BASE_H
#define BASE_H
//大基类，可以派生出各种其他模块

#include <QPoint>
#include <QRect>
#include <QPainter>
#include <data.h>

namespace base
{
    enum size
    {
        Row=13,//13行13列
        Col=13,
        PixWidth=45,//图片尺寸
        PixHeight=45,
        SegWidth=45,//地图分块尺寸
        SegHeight=45,
        Width=PixWidth*Row,//全地图尺寸
        Height=PixHeight*Col
    };
    //类型
    enum Kind
    {
        PATH=0,
        BRICK=1,
        STEEL=2,
        WATER=3,
        JUNGLE=4,
        FLAG=5,
        BULLET_TYPE_NORMAL=1,
        BULLET_TYPE_MID=2,
        BULLET_TYPE_ADVANCE=3,
        ENEMY_TANK_HIGHT_BLOOD=1,
        ENEMY_TANK_HIGHT_ATTACK=2,
        ENEMY_TANK_HIGHT_SPEED=3
    };
}

class Base
{
public:
    Base();
    QPoint getPos() const;//获取左上角点坐标
    QRect getSphere() const;//获取范围
    int getKind() const;//获取类型
    void setPos(int x,int y);
    void setKind(int k);
    bool judge(const Base &base)const;
    static bool penetrate(const QRect rect1,const QRect rect2);//判断是否碰撞
    void display(QPainter &paint);
    QPoint pos;//左上角点坐标
protected:
    int width;
    int height;
    QRect rectSphere;//所及范围
    int kind;
};

#endif // BASE_H
