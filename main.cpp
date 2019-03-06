#include <QApplication>
#include<QPoint>
#include<QDebug>

#include "mainwindow.h"

Glb glb;//全局结构体

int main(int argc, char *argv[])
{
    QPoint *p1;
    p1=new QPoint(400,30);
    QApplication a(argc, argv);
    //字体
    QFont font("Microsoft YaHei UI",10);
    a.setFont(font);
    a.processEvents();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    MainWindow w;
    w.move(*p1);
    //qDebug()<<w.x();
    //qDebug()<<w.y();
    //qDebug() << w.width();
    //qDebug() << w.height();
    w.show();

    return a.exec();
}
