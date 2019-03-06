#include "gametool.h"

gametool::gametool()
{
    flag = true;
    tooltest = true;
    tooltest1 = true;

    int a = qrand()%12;
    int b = qrand()%12;
    this->setPos(a *SegWidth,b*SegHeight);
}

void gametool::createTool(gametool *&tool)
{
    tool->setPos((qrand()%12) *SegWidth,(qrand()%12)*SegHeight);
    tool->setPos(6 *SegWidth,11*SegHeight);

    if (tooltest)
    {
        tool->tooltype = gametool::Timer;
        //qDebug("create timer");
    }
    else
    {
        tool->tooltype = gametool::Bomb;
        //qDebug("create bomb");
    }
    //QTimer::singleShot(10000,tool,SLOT(deleteLater()));
}

void gametool::paint(gametool *&tool, QPainter *p)
{
    if (flag==true&&tooltest1==true)
{
    createTool(tool);
    if (tooltype==gametool::Timer)
    {
        this->setPos(5 *SegWidth,10*SegHeight);
        x = 5 *SegWidth;
        y = 10*SegHeight;
    }
    else if (tooltype==gametool::Bomb)
    {
        this->setPos(2 *SegWidth,10*SegHeight);
        x = 2 *SegWidth;
        y = 10*SegHeight;
    }
    QPixmap pix;
    switch(tool->tooltype)
    {
        case Timer :
            pix.load(":/new/icon/pixs/timer.gif");
            p->drawPixmap(x,y,PixWidth,PixHeight,pix);
            break;
        case Bomb:
            pix.load(":/new/icon/pixs/bomb.gif");
            p->drawPixmap(x,y,PixWidth,PixHeight,pix);
            break;
    }
    }

}

void gametool::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

