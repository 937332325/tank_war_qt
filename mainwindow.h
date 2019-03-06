#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>
#include <algorithm>
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QTime>
#include <QTimer>
#include <map>
#include <vector>
#include <windows.h>

#include"bplustree.h"
#include "collision.h"
#include "data.h"
#include"gametool.h"
#include "home.h"
#include "map.h"
#include "rsa.h"
#include "inputdlg.h"

#define ENEMY_TANK_SUM 2
#define MAP_SUM 2
using namespace base;
using namespace dynamic;
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initGame();
    //void loadMapSeg();
    //窗口右侧显示玩家信息
    void showPlayerInfo();

    QTime time;//通关时间计时
    vector<int> ranking;
    inputdlg *dlg;
private slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void CheckBullet(); //检查更新子弹
    void CheckEnemyTank();  //检查更新敌方坦克
    void CheckMyTank(); //检查更新我方坦克
    void updatefunction();
    void isGameOver();
    void testgameover();
    void speedcontrol();
    //定时器控制
    void startClock();
    void stopClock();
    void gametoolstop();
    //信息一：启动界面，版本信息
    void showInformationMsg1();
    //信息二：操作提示
    void showInformationMsg2();
    void showInformationMsg4();
    void showInformationMsg5();
    void showInformationMsg6();


private:

    bool isPause;

    QPainter paint;
    QTimer *painter_timer;  //画图刷新定时器
    QTimer *checkBullet_timer;  //检查更新子弹定时器
    QTimer *checkEnemyTank_timer;  //检查更新敌方坦克定时器
    QTimer *checkMyTank_timer;    //检查更新我方坦克定时器
    QTimer *gameTool;
    QTimer *gameTool1;
    Map m;  //地图
    Collision *collision;    //碰撞检测与控制移动
    //背景音效
    QMediaPlayer *player;
    QMediaPlayer *player1;
    QMediaPlayer *player2;
    QMediaPlayer *player3;

    int aa;
    int stage; //当前关卡数
    int score; //分数
    Finder f;
    //窗口右侧显示信息控件
    //得分
    QLabel *label1,*label2;
    //剩余坦克数
    QLabel *label3,*label4;
    //关卡数
    QLabel *label5,*label6;
    //剩下生命数
    QLabel *label7,*label8;
    //暂停pause
    QLabel *label9;

};

#endif // MAINWINDOW_H
