#ifndef HOME_H
#define HOME_H

#include <QDebug>

#include "data.h"
#include "dynamic.h"
using namespace base;

class home:public Dynamic
{
public:
    home();
    int x;
    int y;
    QImage zhubao;
    virtual void display(QPainter &paint);
    virtual void move() {} //纯虚函数不实现
    virtual void calSphere();
};

#endif // HOME_H
