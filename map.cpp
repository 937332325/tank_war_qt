#include"map.h"

Map::Map()
{
    width=PixWidth;
    height=PixHeight;
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
        {
            map[i][j].setPos(i*PixWidth,j*PixHeight);
            map[i][j].setKind(PATH);
        }
    }
    penetration_1[PATH]=false;
    for (int i=1;i<6;i++)
    {
        penetration_1[i] = true;
    };
    penetration_1[JUNGLE] = false;
}

void Map::mapInit()
{
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int map_1[13][13]={
        //1,2,3,4,5,6,7,8,9,0,1,2,3
         {0,0,0,0,0,0,0,2,2,2,2,2,0},//1行
         {0,0,0,1,1,1,0,1,1,1,0,0,0},//2
         {0,0,0,1,0,1,0,1,0,1,0,0,0},//3
         {0,0,0,1,1,1,0,1,0,1,0,0,0},//4
         {0,0,0,0,0,1,0,1,0,1,0,0,0},//5
         {0,0,0,1,1,1,0,1,1,1,0,0,0},//6
         {0,0,0,0,0,0,0,0,0,0,0,0,0},//7
         {2,0,0,0,0,0,2,0,0,0,0,0,2},//8
         {0,0,0,1,0,1,1,1,0,1,0,0,0},//9
         {0,0,0,0,2,0,0,1,2,1,2,0,0},//10
         {0,0,0,1,0,0,0,0,0,1,0,0,0},//11
         {0,0,0,1,0,2,2,2,0,1,0,0,0},//12
         {0,0,0,0,0,2,0,2,0,0,0,0,0},//13
    };
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
        {
            int kind=map_1[i][j];
            if(i==6&&j==12)
            {
                kind=FLAG;
            }
            else if(i==4&&j==12)
            {
                kind=PATH;
            }

            else if( (i==5&&j==12) || (i==5&&j==11) || (i==7&&j==11) || (i==6&&j==11))
            {
                kind = STEEL;
            }
            map[i][j].setKind(kind);
            map[6][11].setKind(BRICK);
        }
    }
}

void Map::loadMap(int stage)
{
    QString path("C:/Users/hp/Desktop/shujujiegou/TankWar_V1.0/Tank30/map/map"+QString::number(stage)+".txt");
    qDebug()<<path;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        exit(0);
    }
    else
    {
        qDebug()<<"打开成功";
        int i=0;
        int j=0;
        while(!file.atEnd())
        {
            char numchar;
            //读取一行数据
            bool con=file.getChar(&numchar);
            if(con)
            {
                if(numchar=='\r')
                {
                    i++;
                    j=0;
                }
                else if(numchar==',')
                {
                    j++;
                }
                else if(numchar>=48 && numchar<=57)
                {
                    map[i][j].setKind(numchar-48);
                }
            }
        }
    }
    //关闭文件
    file.close();
}

bool Map::isPenetration1(int pix_x,int pix_y)
{
    if(pix_x>=Width || pix_x<0 || pix_y>=Height || pix_y<0)
    {
        return false;
    }
    else
    {
        return penetration_1[ map[ pix_x/SegWidth ][ pix_y/SegHeight ].getKind() ];
    }
}

QRect Map::getMapSeg(int pix_x, int pix_y)
{
    if(pix_x<0 || pix_x>Width || pix_y<0 || pix_y>Height)
    {
        return QRect(0,0,0,0);
    }
    else
    {
        return map[ pix_x/SegWidth ][ pix_y/SegHeight ].getSphere();
    }
}

void Map::display(QPainter &paint)
{
    QPixmap pix;
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
        {
            pix.load(path[ map[i][j].getKind() ]);
            paint.drawPixmap(i*SegWidth,j*SegHeight,SegWidth,SegHeight,pix);
        }
    }
}
