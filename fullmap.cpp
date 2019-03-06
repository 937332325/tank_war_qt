#include "fullmap.h"

fullMap::fullMap()
{
    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            segs[i][j]=NULL;
        }
    }


}

fullMap::~fullMap()
{
    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            if(segs[i][j])
            {
                delete segs[i][j];
                segs[i][j]=NULL;
            }
        }
    }
}

void fullMap::loadMap()
{
    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            segs[i][j]=NULL;
        }
    }

    int tmp=1;
    if (tmp==1){
        int map_1[Col][Row]={
           //1,2,3,4,5,6,7,8,9,0,1,2,3
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,1,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,1,0,0,0,0,0},
        };
        for(int i=0;i<Row;++i)
        {
            for(int j=0;j<Col;++j)
            {
                segs[i][j]=new mapSeg(i,j);
                segs[i][j]->kind=map_1[i][j];
                segs[i][j]->modifyMapSeg(i,j);
            }
        }
    }
}

void fullMap::display(QPainter &paint)
{
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,Width,Height);


    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            if(segs[i][j]!=NULL)
                segs[i][j]->display(paint);
        }
    }

}

mapSeg* fullMap::getSeg(int i, int j) const
{
    return segs[i][j];
}
