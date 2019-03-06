#ifndef MAP
#define MAP

#include <math.h>
#include <QFile>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QtGlobal>
#include <QTime>
#include <QTimer>

#include "base.h"
#include "data.h"
using namespace base;

//map的Row对应的是画出来地图的列，Col对应的是画出来地图的行

class Map:public Base
{
public:
    QString path[6]={":/new/icon/pixs/path.png",
                  ":/new/icon/pixs/1_1.png",
                  ":/new/icon/pixs/2_1.png",
                  ":/new/icon/pixs/4.png",
                  ":/new/icon/pixs/5.png",
                  ":/new/icon/pixs/home.png"};
    bool penetration_1[6];
    Base map[base::Row][base::Col];
    Map();  //初始化地图
    void mapInit(); //生成地图
    void loadMap(int stage);
    bool isPenetration1(int pix_x, int pix_y);
    QRect getMapSeg(int pix_x,int pix_y); 
    void display(QPainter &paint);
};

#endif // MAP

