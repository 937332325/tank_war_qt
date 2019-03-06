#include "mapseg.h"

mapSeg::mapSeg(int i,int j)
{
    this->pos.setX(SegWidth*j);
    this->pos.setY(SegHeight*i);
    this->calSphere();
    this->kind=0;
}

void mapSeg::modifyMapSeg(int i, int j)
{
    this->pos.setX(SegWidth*j);
    this->pos.setY(SegHeight*i);
    this->calSphere();
}

/*void mapSeg::display(QPainter &paint)
{
    switch(this->kind)
    {
    case 0:
        break;
    case 1:
        paint.drawImage(rectSphere,glb.images[0]);
        break;
    case 2:
        paint.drawImage(rectSphere,glb.images[1]);
        break;
    case 3:
        paint.drawImage(rectSphere,glb.images[2]);
        break;
    case 4:
        paint.drawImage(rectSphere,glb.images[3]);
        break;
    case 5:
        paint.drawImage(rectSphere,glb.images[4]);
        break;
    default:
        break;
    }

}*/

void mapSeg::calSphere()
{
    this->rectSphere.setRect(pos.x(),pos.y(),
                             SegWidth,SegHeight);
}
