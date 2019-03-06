#include"collision.h"

Collision::Collision(bool isDouble)
{
    myTanklist=MyTankList(isDouble);
    bulletList=BulletList();
    enemyTanklist=EnemyTankList();
    doublespeed = false;
}

bool Collision::TankToBrick(Tank *&tank)
{
    return true;
}

bool Collision::TankToSteel(Tank *&tank)
{
    return true;
}

bool Collision::TankToWater(Tank *&tank)
{
    return true;
}

bool Collision::TankToJungle(Tank *&tank)
{
    return false;
}

bool Collision::TankToFlag(Tank *&tank)
{
    return false;
}

bool Collision::BulletToBrick(bullet &bul, Base &m)
{
    m.setKind(PATH);
    bul.setBlood(0);
    return false;
}

bool Collision::BulletToSteel(bullet &bul, Base &m)
{
    if(bul.getPower()==LOWPOWER)
    {
        bul.setBlood(0);
        return false;
    }
    else
    {
        bul.setBlood(0);
        m.setKind(PATH);
        return false;
    }
}

bool Collision::BulletToWater(bullet &bul, Base &m)
{
    return true;
}

bool Collision::BulletToJungle(bullet &bul, Base &m)
{
    return true;
}

bool Collision::BulletToFlag(bullet &bul, Base &m)
{
    bul.setBlood(0);
    m.setKind(PATH);
    return false;
}

bool Collision::isOutOfBound(Dynamic &dynamic)
{
    //预测再走一步是否会越界
    return (dynamic.getSphere().top()+dynamic.getSpeedY()<0 ||
            dynamic.getSphere().bottom()+dynamic.getSpeedY()>Height ||
            dynamic.getSphere().left()+dynamic.getSpeedX()<0 ||
            dynamic.getSphere().right()+dynamic.getSpeedX()>Width);
}

bool Collision::TankToObstacle(Tank &tank,Map &m)
{
    //预测再走一步是否会碰撞
    if(isOutOfBound(tank))
    {
        return true;
    }
    else
    {
        QRect rect(tank.getSphere().left()+tank.getSpeedX(),
                   tank.getSphere().top()+tank.getSpeedY(),
                   PixWidth,PixHeight);
        switch(tank.getDir())
        {
        case(LEFT):
            if(rect.top()%SegHeight==0)
            {
                return m.isPenetration1(rect.left(),rect.top());
            }
            else
            {
                return ( m.isPenetration1(rect.left(),rect.top()) ||
                         m.isPenetration1(rect.left(),rect.bottom()) );
            }
            break;
        case(RIGHT):
            if(rect.top()%SegHeight==0)
            {
                return m.isPenetration1(rect.right(),rect.top());
            }
            else
            {
                return ( m.isPenetration1(rect.right(),rect.top()) ||
                         m.isPenetration1(rect.right(),rect.bottom()));
            }
            break;
        case(DOWN):
            if(rect.left()%SegWidth==0)
            {
                return m.isPenetration1(rect.left(),rect.bottom());
            }
            else
            {
                return ( m.isPenetration1(rect.left(),rect.bottom()) ||
                         m.isPenetration1(rect.right(),rect.bottom()));
            }
            break;
        case(UP):
            if(rect.left()%SegWidth==0)
            {
                return m.isPenetration1(rect.left(),rect.top());
            }
            else
            {
                return ( m.isPenetration1(rect.left(),rect.top()) ||
                         m.isPenetration1(rect.right(),rect.top()));
            }
            break;
        }
    }
}

bool Collision::TankToTankList(Tank &tank, EnemyTankList &e,int i)
{
    if(i==-1)
    {
        for(int j=0;j<e.getSize();j++)
        {
            if(Base::penetrate(tank.getSphere(),e.enemyArmy[j].getSphere()))
            {
                return true;
            }
        }
    }
    else
    {
        for(int j=0;j<e.getSize();j++)
        {
            if(j==i)
            {
                continue;
            }
            else
            {
                if(Base::penetrate(tank.getSphere(),e.enemyArmy[j].getSphere()))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Collision::BulletToObstacleHelp(bullet &bul, Base &m)
{
    bool ismove=true;
    switch(m.getKind())
    {
    case(PATH):
        ismove=true;
        break;
    case(BRICK):
        ismove=BulletToBrick(bul,m);
        break;
    case(JUNGLE):
        ismove=BulletToJungle(bul,m);
        break;
    case(WATER):
        ismove=BulletToWater(bul,m);
        break;
    case(FLAG):
        ismove=BulletToFlag(bul,m);
        break;
    case(STEEL):
        ismove=BulletToSteel(bul,m);
        break;
    }
    return ismove;
}

bool Collision::BulletToObstacle(bullet &bul,Map &m)
{
    //预测再走一步是否会碰撞
    if(isOutOfBound(bul))
    {
        return true;
    }
    else
    {
        QRect rect(bul.getSphere().left()+bul.getSpeedX(),
                   bul.getSphere().top()+bul.getSpeedY(),
                   15,15);
        bool ismove1=true;
        bool ismove2=true;
        switch(bul.getDir())
        {
        case(LEFT):
            if(rect.top()%SegHeight==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.bottom()/SegHeight]);
            }
            else if(rect.bottom()%SegHeight==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.top()/SegHeight]);
            }
            else
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.bottom()/SegHeight]);
                ismove2=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.top()/SegHeight]);
            }
            break;
        case(RIGHT):
            if(rect.top()%SegHeight==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.bottom()/SegHeight]);
            }
            else if(rect.bottom()%SegHeight==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.top()/SegHeight]);
            }
            else
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.bottom()/SegHeight]);
                ismove2=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.top()/SegHeight]);
            }
            break;
        case(DOWN):
            if(rect.left()%SegWidth==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.bottom()/SegHeight]);
            }
            else if(rect.right()%SegWidth==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.bottom()/SegHeight]);
            }
            else
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.bottom()/SegHeight]);
                ismove2=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.bottom()/SegHeight]);
            }
            break;
        case(UP):
            if(rect.left()%SegWidth==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.top()/SegHeight]);
            }
            else if(rect.right()%SegWidth==0)
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.top()/SegHeight]);
            }
            else
            {
                ismove1=BulletToObstacleHelp(bul,m.map[rect.right()/SegWidth][rect.top()/SegHeight]);
                ismove2=BulletToObstacleHelp(bul,m.map[rect.left()/SegWidth][rect.top()/SegHeight]);
            }
            break;
        }
        if(ismove1 && ismove2)
        {
            bul.move();
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool Collision::BulletToTank(bullet &bul, Tank &tank)
{
   if( Base::penetrate(bul.getSphere(),tank.getSphere()) )
   {
       bul.setBlood(0);
       tank.setBlood(tank.getBlood()-bul.getPower());

       return true;
   }
   else
   {
       return false;
   }
}

void Collision::CheckBulletList(Map &m)
{
    BulletNode* p=bulletList.getHead();
    BulletNode* q=bulletList.getHead()->next;
    for(p=bulletList.getHead(),q=p->next;q!=NULL;p=q,q=q->next)
    {
        if((q->bul.getID()==ENEMYTANK) && (BulletToTank(q->bul,myTanklist.myArmy[0])
                || (getIsDouble()?BulletToTank(q->bul,myTanklist.myArmy[1]):false)))
        {
            bulletList.deleteBullet(q);
        }
        else if(BulletToObstacle(q->bul,m))
        {
            bulletList.deleteBullet(q);
        }
        else if(q->bul.getID()==MYTANK)
        {
            for(int i=0;i<ENEMY_TANK_NUMBER;i++)
            {
                if(BulletToTank(q->bul,enemyTanklist.enemyArmy[i]))
                {
                    bulletList.deleteBullet(q);
                    break;
                }
            }
        }
    }
}

void Collision::CheckEnemyTankList(Map &m)
{
    static int step[3]={0,0,0};

    for(int i=0;i<ENEMY_TANK_NUMBER;i++)
    {
        if(enemyTanklist.enemyArmy[i].isAlive()==false)
        {
            enemyTanklist.deleteEnemyTank(i);
            step[i]=0;

            enemyTank etemp(i*6%13,0);
            bool isFree=(!TankToTankList(etemp,enemyTanklist,i))
                    && (!Base::penetrate(myTanklist.myArmy[0].getSphere(),QRect(i*6%13*PixWidth,0,PixWidth,PixHeight)));
            if(isFree)
            {
                enemyTanklist.addEnemyTank();
            }
        }
        else
        {
            //是否遇到障碍
            int dir=enemyTanklist.enemyArmy[i].getDir();
            if(TankToObstacle(enemyTanklist.enemyArmy[i],m))
            {
                //是：转向
                int p;
                do
                {
                    p=qrand()%4;
                }while(p==dir);
                enemyTanklist.enemyArmy[i].turn(p);
                step[i]=0;
            }
            else
            {
                //否：是否遇到敌方坦克
                if(TankToTankList(enemyTanklist.enemyArmy[i],enemyTanklist,i))
                {
                    //是：转向
                    enemyTanklist.enemyArmy[i].turnback();
                    enemyTanklist.enemyArmy[i].walk();
                    step[i]++;
                }
                else
                {
                    //否：是否遇到我方坦克？
                    QRect rect1(enemyTanklist.enemyArmy[i].getSphere().x()+2*enemyTanklist.enemyArmy[i].getSpeedX(),
                                enemyTanklist.enemyArmy[i].getSphere().y()+2*enemyTanklist.enemyArmy[i].getSpeedY(),
                                PixWidth,PixHeight);
                    QRect rect2=myTanklist.myArmy[0].getSphere();
                    if(Base::penetrate(rect1,rect2))
                    {
                        //是：转向并攻击
                        if(rect1.right()<rect2.left())
                        {
                            enemyTanklist.enemyArmy[i].turn(RIGHT);
                        }
                        else if(rect1.left()>rect2.right())
                        {
                            enemyTanklist.enemyArmy[i].turn(LEFT);
                        }
                        else if(rect1.top()<rect2.bottom())
                        {
                            enemyTanklist.enemyArmy[i].turn(UP);
                        }
                        else
                        {
                            enemyTanklist.enemyArmy[i].turn(DOWN);
                        }
                        step[i]=0;
                        addBullet(enemyTanklist.enemyArmy[i].attack());
                    }
                    else
                    {
                        //否：前方是否有主堡
                        if((enemyTanklist.enemyArmy[i].getDir()==DOWN && enemyTanklist.enemyArmy[i].getPos().x()/PixWidth==6)
                            || (enemyTanklist.enemyArmy[i].getDir()==LEFT && enemyTanklist.enemyArmy[i].getPos().y()/PixHeight==12 && abs(enemyTanklist.enemyArmy[i].getPos().x()-PixWidth*6)<100)
                            || (enemyTanklist.enemyArmy[i].getDir()==RIGHT && enemyTanklist.enemyArmy[i].getPos().y()/PixHeight==12 && abs(enemyTanklist.enemyArmy[i].getPos().x()-PixWidth*6)<100))
                        {
                            //是：判断距离，距离越近，转向的概率越小，行走和攻击的概率越大
                            int h=abs(enemyTanklist.enemyArmy[i].getPos().x()-PixWidth*6)+abs(enemyTanklist.enemyArmy[i].getPos().y()-PixHeight*12);
                            int p=-0.056*h+75;
                            if((qrand()%101)<p)
                            {
                                addBullet(enemyTanklist.enemyArmy[i].attack());
                            }
                            else
                            {
                                //随机行为
                                int q=qrand()%101;
                                if(q<10)
                                {
                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                }
                                else if(q<(0.025*step[i]*step[i]+12))
                                {

                                    int p;
                                    do
                                    {
                                        p=qrand()%4;
                                    }while(p==dir);
                                    enemyTanklist.enemyArmy[i].turn(p);
                                    step[i]=0;
                                }
                                else
                                {
                                    enemyTanklist.enemyArmy[i].walk();
                                    step[i]++;
                                }
                            }
                        }
                        else
                        {
                            //否：前方是否有我方坦克
                            QPoint point1=enemyTanklist.enemyArmy[i].getPos();
                            QPoint point2=myTanklist.myArmy[0].getPos();
                            bool myTankIsAhead=false;
                            switch(enemyTanklist.enemyArmy[i].getDir())
                            {
                            case(UP):
                                if(point1.y()>point2.y() && point1.x()==point2.x())
                                {
                                    myTankIsAhead=true;
                                }
                                break;
                            case(DOWN):
                                if(point1.y()<point2.y() && point1.x()==point2.x())
                                {
                                    myTankIsAhead=true;
                                }
                                break;
                            case(LEFT):
                                if(point1.x()<point2.x() && point1.y()==point2.y())
                                {
                                    myTankIsAhead=true;
                                }
                                break;
                            case(RIGHT):
                                if(point1.x()>point2.x() && point1.y()==point2.y())
                                {
                                    myTankIsAhead=true;
                                }
                                break;
                            }
                            if(myTankIsAhead)
                            {
                                //是：判断距离，距离越近，转向的概率越小，行走和攻击的概率越大
                                int h=abs(point1.x()-point2.x())+abs(point1.y()-point2.y());
                                int p=-0.056*h+75;
                                if((qrand()%101)<p)
                                {
                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                }
                                else
                                {
                                    //随机行为
                                    int q=qrand()%101;
                                    if(q<10)
                                    {
                                        addBullet(enemyTanklist.enemyArmy[i].attack());
                                    }
                                    else if(q<(0.025*step[i]*step[i]+12))
                                    {
                                        int p;
                                        do
                                        {
                                            p=qrand()%4;
                                        }while(p==dir);
                                        enemyTanklist.enemyArmy[i].turn(p);
                                        step[i]=0;
                                    }
                                    else
                                    {
                                        enemyTanklist.enemyArmy[i].walk();
                                        step[i]++;
                                    }
                                }
                            }
                            else
                            {
                                //否：另外两边是否有我方坦克
                                bool myTankIsAside=false;
                                int h=abs(point1.x()-point2.x())+abs(point1.y()-point2.y());
                                int p=-0.056*h+100;
                                switch(enemyTanklist.enemyArmy[i].getDir())
                                {
                                case(UP):
                                case(DOWN):
                                    if(point1.y()==point2.y())
                                    {
                                        myTankIsAside=true;
                                        if(point1.x()<point2.x())
                                        {
                                            if((qrand()%100)<p)
                                            {
                                                if((qrand()%100)<(p/4))
                                                {
                                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                                }
                                                else
                                                {
                                                    enemyTanklist.enemyArmy[i].walk();
                                                    step[i]++;
                                                }
                                            }
                                            else
                                            {
                                                enemyTanklist.enemyArmy[i].turn(RIGHT);
                                                step[i]=0;
                                            }
                                        }
                                        else
                                        {
                                            if((qrand()%100)<p)
                                            {
                                                if((qrand()%100)<(p/4))
                                                {
                                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                                }
                                                else
                                                {
                                                    enemyTanklist.enemyArmy[i].walk();
                                                    step[i]++;
                                                }
                                            }
                                            else
                                            {
                                                enemyTanklist.enemyArmy[i].turn(LEFT);
                                                step[i]=0;
                                            }
                                        }
                                    }
                                    break;
                                case(LEFT):
                                case(RIGHT):
                                    if(point1.x()==point2.x())
                                    {
                                        myTankIsAside=true;
                                        if(point1.y()<point2.y())
                                        {
                                            if((qrand()%100)<p)
                                            {
                                                if((qrand()%100)<(p/4))
                                                {
                                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                                }
                                                else
                                                {
                                                    enemyTanklist.enemyArmy[i].walk();
                                                    step[i]++;
                                                }
                                            }
                                            else
                                            {
                                                enemyTanklist.enemyArmy[i].turn(UP);
                                                step[i]=0;
                                            }
                                        }
                                        else
                                        {
                                            if((qrand()%100)<p)
                                            {
                                                if((qrand()%100)<(p/4))
                                                {
                                                    addBullet(enemyTanklist.enemyArmy[i].attack());
                                                }
                                                else
                                                {
                                                    enemyTanklist.enemyArmy[i].walk();
                                                    step[i]++;
                                                }
                                            }
                                            else
                                            {
                                                enemyTanklist.enemyArmy[i].turn(DOWN);
                                                step[i]=0;
                                            }
                                        }
                                    }
                                    break;
                                }

                                if(!myTankIsAside)
                                {
                                    //否:随机行为
                                    int q=qrand()%100;
                                    if(q<10)
                                    {
                                        addBullet(enemyTanklist.enemyArmy[i].attack());
                                    }
                                    else if(q<(0.025*step[i]*step[i]+12))
                                    {
                                        int p;
                                        do
                                        {
                                            p=qrand()%4;
                                        }while(p==dir);
                                        enemyTanklist.enemyArmy[i].turn(p);
                                        step[i]=0;
                                    }
                                    else
                                    {
                                        enemyTanklist.enemyArmy[i].walk();
                                        step[i]++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //for(int i=0;i<ENEMY_TANK_NUMBER;i++)
}

void Collision::CheckMyTankList()
{
    if(myTanklist.getIsDouble())
    {
        for(int i=0;i<2;i++)
        {
            if(!myTanklist.myArmy[i].isAlive())
            {
                myTanklist.Rebirth(i);
            }
        }
    }
    else
    {
        if(!myTanklist.myArmy[0].isAlive())
        {
            myTanklist.Rebirth(0);
        }
    }
}

void Collision::addBullet(bullet bul)
{
    bulletList.addBullet(bul);
    return;
}

void Collision::addEnemyTank()
{
    enemyTanklist.addEnemyTank();
    return;
}

int Collision::getEnemyDeathSum()
{
    return enemyTanklist.getDeathSum();
}

int Collision::getRebirthSum(int i)
{
    return myTanklist.getRebirthTimes(i);
}

bool Collision::getIsDouble()
{
    return myTanklist.getIsDouble();
}

void Collision::controlMyTank(QKeyEvent *event, Map &m)
{
    mytank tank;
    tank.setBlood(1);
    tank.setPos(myTanklist.myArmy[0].getPos().x(),myTanklist.myArmy[0].getPos().y());
    if (doublespeed==true)
    {
        myTanklist.myArmy[0].num = 10;
        myTanklist.myArmy[0].Dynamic::num = 10;
    }
    else
    {
        myTanklist.myArmy[0].num = 1;
        myTanklist.myArmy[0].Dynamic::num = 1;
    }
    tank.setSpeed(myTanklist.myArmy[0].getSpeedX(),myTanklist.myArmy[0].getSpeedY());
    tank.setDir(myTanklist.myArmy[0].getDir());
    tank.Dynamic::move();
    if (tank.pos.x()>glb.tool->x-SegWidth&&tank.pos.x()<glb.tool->x+SegWidth&&tank.pos.y()>glb.tool->y-SegWidth&&tank.pos.y()<glb.tool->y+SegWidth)
    {
        if (glb.tool->tooltest == true)
        {
        if (!glb.tool->queue1.empty()&&!glb.tool->tooltest)
            glb.tool->queue1.push(glb.tool->tooltype);
        else if (glb.tool->queue1.empty())
            glb.tool->queue1.push(glb.tool->tooltype);
        //qDebug("enqueue");
        glb.tool->flag = false;
        glb.tool->tooltest = false;
        }
        else if (glb.tool->tooltest == false)
        {
            if (!glb.tool->queue1.empty()&&glb.tool->tooltest)
                glb.tool->queue1.push(glb.tool->tooltype);
            else if (glb.tool->queue1.empty())
                glb.tool->queue1.push(glb.tool->tooltype);
            glb.tool->flag = false;
            glb.tool->tooltest = true;
        }
    }
    if (event->key()==Qt::Key_W )
    {
        if(myTanklist.myArmy[0].getDir()==UP
                && !TankToTankList(tank,enemyTanklist))
        {
            if(!TankToObstacle(myTanklist.myArmy[0],m))
            {
                myTanklist.myArmy[0].Dynamic::move();
            }
        }
        else
        {
            myTanklist.myArmy[0].turn(UP);
        }
    }
    else if (event->key()==Qt::Key_S )
    {
        if(myTanklist.myArmy[0].getDir()==DOWN
                && !TankToTankList(tank,enemyTanklist))
        {
            if(!TankToObstacle(myTanklist.myArmy[0],m))
            {
                myTanklist.myArmy[0].Dynamic::move();
            }
        }
        else
        {
            myTanklist.myArmy[0].turn(DOWN);
        }
    }
    else if (event->key()==Qt::Key_A )
    {
        if(myTanklist.myArmy[0].getDir()==LEFT
                && !TankToTankList(tank,enemyTanklist))
        {
            if(!TankToObstacle(myTanklist.myArmy[0],m))
            {
                myTanklist.myArmy[0].Dynamic::move();
            }
        }
        else
        {
            myTanklist.myArmy[0].turn(LEFT);
        }
    }
    else if (event->key()==Qt::Key_D )
    {
        if(myTanklist.myArmy[0].getDir()==RIGHT
                && !TankToTankList(tank,enemyTanklist))
        {
            if(!TankToObstacle(myTanklist.myArmy[0],m))
            {
                myTanklist.myArmy[0].Dynamic::move();
            }
        }
        else
        {
            myTanklist.myArmy[0].turn(RIGHT);
        }
    }
    else if (event->key()==Qt::Key_J )
    {
        //开火
        addBullet(myTanklist.myArmy[0].attack());
    }
    else if(myTanklist.getIsDouble())
    {
        mytank tank;
        tank.setBlood(1);
        tank.setPos(myTanklist.myArmy[1].getPos().x(),myTanklist.myArmy[1].getPos().y());
        tank.setSpeed(myTanklist.myArmy[1].getSpeedX(),myTanklist.myArmy[1].getSpeedY());
        tank.setDir(myTanklist.myArmy[1].getDir());
        tank.Dynamic::move();
        if (event->key()==Qt::Key_Up )
        {
            if(myTanklist.myArmy[1].getDir()==UP
                    && !TankToTankList(tank,enemyTanklist))
            {
                if(!TankToObstacle(myTanklist.myArmy[1],m))
                {
                    myTanklist.myArmy[1].Dynamic::move();
                }
            }
            else
            {
                myTanklist.myArmy[1].turn(UP);
            }
        }
        else if (event->key()==Qt::Key_Down )
        {
            if(myTanklist.myArmy[1].getDir()==DOWN
                    && !TankToTankList(tank,enemyTanklist))
            {
                if(!TankToObstacle(myTanklist.myArmy[1],m))
                {
                    myTanklist.myArmy[1].Dynamic::move();
                }
            }
            else
            {
                myTanklist.myArmy[1].turn(DOWN);
            }
        }
        else if (event->key()==Qt::Key_Left )
        {
            if(myTanklist.myArmy[1].getDir()==LEFT
                    && !TankToTankList(tank,enemyTanklist))
            {
                if(!TankToObstacle(myTanklist.myArmy[1],m))
                {
                    myTanklist.myArmy[1].Dynamic::move();
                }
            }
            else
            {
                myTanklist.myArmy[1].turn(LEFT);
            }
        }
        else if (event->key()==Qt::Key_Right )
        {
            if(myTanklist.myArmy[1].getDir()==RIGHT
                    && !TankToTankList(tank,enemyTanklist))
            {
                if(!TankToObstacle(myTanklist.myArmy[1],m))
                {
                    myTanklist.myArmy[1].Dynamic::move();
                }
            }
            else
            {
                myTanklist.myArmy[1].turn(RIGHT);
            }
        }
        else if (event->key()==Qt::Key_0 )
        {
            //开火
            addBullet(myTanklist.myArmy[1].attack());
        }
    }
}


void Collision::paint(QPainter *p)
{
    bulletList.paint(p);
    myTanklist.paint(p);
    enemyTanklist.paint(p);
}

