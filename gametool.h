#ifndef GAMETOOL_H
#define GAMETOOL_H

#include "base.h"
#include "data.h"
#include <queue>
using namespace std;
using namespace base;

class gametool
{
public:
    gametool();
    int x;
    int y;
    QImage daoju[2];
    enum    ToolType{Timer,  Bomb};
    ToolType tooltype;
    void paint(gametool *&tool,QPainter *p);
    //virtual void calSphere();
    void setPos(int x,int y);
    void createTool(gametool *&tool);
    queue<ToolType> queue1;//存储道具
    bool flag;
    bool tooltest;
    bool tooltest1;
};

#endif // GAMETOOL_H
