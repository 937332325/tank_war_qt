#include"linklist.h"

BulletList::BulletList()
{
    head=new BulletNode();
    tail=head;
    length=0;
}

void BulletList::addBullet(bullet bul)
{
    BulletNode *bulletnode=new BulletNode;
    bulletnode->bul=bul;
    bulletnode->next=NULL;
    tail->next=bulletnode;
    tail=bulletnode;
    length++;
    //qDebug()<<"add:length="<<length<<endl;
    return;
}

void BulletList::deleteBullet(BulletNode *p)
{
    /*删除了该节点后直接指向下一个节点，或者说是新的节点*/
    if(length==0) return;
    if(p==NULL)
    {
        return;
    }
    else if(p->next==NULL)
    {
        head->next=NULL;
        tail=head;
        delete p;
        p=NULL;
        length--;
    }
    else
    {
        //数据交换
        BulletNode* temp=new BulletNode;
        temp->bul=p->bul;
        p->bul=p->next->bul;
        p->next->bul=temp->bul;

        temp=p->next;
        p->next=p->next->next;
        if(p->next==tail)
        {
            tail=p;
        }
        delete temp;
        length--;
    }
    return;
}

bool BulletList::isEmpty()
{
    if(length==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

BulletNode* BulletList::getHead()
{
    return head;
}

void BulletList::paint(QPainter *pa)
{
    QPixmap pix;
    pix.load(":/new/icon/pixs/tankMissile.png");
    for(BulletNode *p=head->next;p;p=p->next)
    {
        if(p->bul.isAlive())
        {
            pa->drawPixmap(p->bul.getSphere(),pix);

        }
    }
}

EnemyTankList::EnemyTankList()
{
    death_sum=0;
    for(int i=0;i<ENEMY_TANK_NUMBER;i++)
    {
        enemyArmy[i]=enemyTank(i*6%13,0);
    }
    length=ENEMY_TANK_NUMBER;
}

void EnemyTankList::addEnemyTank()
{

    if(length==ENEMY_TANK_NUMBER)
    {
        return;
    }
    else
    {
        for(int i=0;i<ENEMY_TANK_NUMBER;i++)
        {
            if(!enemyArmy[i].isAlive())
            {
                enemyArmy[i]=enemyTank(i*6%13,0);
                break;
            }
        }
        length++;
    }
    return;
}

void EnemyTankList::deleteEnemyTank(int i)
{
    if(length==0) return;
    if(i>=0 && i<ENEMY_TANK_NUMBER)
    {
        enemyArmy[i].setBlood(0);
        death_sum++;
        length--;
    }
}

bool EnemyTankList::isEmpty()
{
    if(length==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int EnemyTankList::getSize()
{
    return length;
}

int EnemyTankList::getDeathSum()
{
    return death_sum;
}

void EnemyTankList::paint(QPainter *p)
{
    QPixmap pix;
    pix.load(":/new/icon/pixs/tankMissile.png");
    for(int i=0;i<ENEMY_TANK_NUMBER;i++)
    {
        if(enemyArmy[i].isAlive())
        {
            switch(enemyArmy[i].getDir())
            {
            case(LEFT):
                switch(enemyArmy[i].getKind())
                {
                case(ENEMY_TANK_HIGHT_BLOOD):
                    pix.load(":/new/icon/pixs/enemy1L.png");
                    break;
                case(ENEMY_TANK_HIGHT_SPEED):
                    pix.load(":/new/icon/pixs/enemy2L.png");
                    break;
                case(ENEMY_TANK_HIGHT_ATTACK):
                    pix.load(":/new/icon/pixs/enemy3L.png");
                    break;
                }
                break;
            case(RIGHT):
                switch(enemyArmy[i].getKind())
                {
                case(ENEMY_TANK_HIGHT_BLOOD):
                    pix.load(":/new/icon/pixs/enemy1R.png");
                    break;
                case(ENEMY_TANK_HIGHT_SPEED):
                    pix.load(":/new/icon/pixs/enemy2R.png");
                    break;
                case(ENEMY_TANK_HIGHT_ATTACK):
                    pix.load(":/new/icon/pixs/enemy3R.png");
                    break;
                }
                break;
            case(UP):
                switch(enemyArmy[i].getKind())
                {
                case(ENEMY_TANK_HIGHT_BLOOD):
                    pix.load(":/new/icon/pixs/enemy1U.png");
                    break;
                case(ENEMY_TANK_HIGHT_SPEED):
                    pix.load(":/new/icon/pixs/enemy2U.png");
                    break;
                case(ENEMY_TANK_HIGHT_ATTACK):
                    pix.load(":/new/icon/pixs/enemy3U.png");
                    break;
                }
                break;
            case(DOWN):
                switch(enemyArmy[i].getKind())
                {
                case(ENEMY_TANK_HIGHT_BLOOD):
                    pix.load(":/new/icon/pixs/enemy1D.png");
                    break;
                case(ENEMY_TANK_HIGHT_SPEED):
                    pix.load(":/new/icon/pixs/enemy2D.png");
                    break;
                case(ENEMY_TANK_HIGHT_ATTACK):
                    pix.load(":/new/icon/pixs/enemy3D.png");
                    break;
                }
                break;
            }
            p->drawPixmap(enemyArmy[i].getSphere(),pix);
        }
    }
}

MyTankList::MyTankList(bool isDouble)
{
    isdouble=isDouble;
    for(int i=0;i<2;i++)
    {
        rebirth_times[i]=0;
        myArmy[i]=mytank((i+1)*4,12);
    }
}

bool MyTankList::getIsDouble()
{
    return isdouble;
}

void MyTankList::Rebirth(int i)
{
    myArmy[i].setBlood(BLOOD_MID);
    myArmy[i].setPos((i+1)*4*PixWidth,12*PixHeight);
    myArmy[i].setDir(UP);
    rebirth_times[i]++;
}

int MyTankList::getRebirthTimes(int i)
{
    return rebirth_times[i];
}

void MyTankList::paint(QPainter *p)
{
    if(isdouble)
    {
        for(int i=0;i<2;i++)
        {
            myArmy[i].display(p);
        }
    }
    else
    {
        myArmy[0].display(p);
    }
}
