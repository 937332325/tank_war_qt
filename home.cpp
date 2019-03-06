#include "home.h"

home::home()
{
    this->x = 6*SegWidth;
    this->y = 12*SegHeight;
    this->calSphere();
    this->blood = 10;
    zhubao.load(":/new/icon/pixs/home.png");
}

void home::calSphere()
{
    this->rectSphere.setRect(this->x,this->y,SegWidth,SegHeight);
}

void home::display(QPainter &paint)
{
    paint.drawImage(this->rectSphere,zhubao);
    //qDebug("draw home");
}
