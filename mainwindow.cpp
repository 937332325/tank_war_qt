#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Sleep(1000);
    showInformationMsg1();
    showInformationMsg2();

    //设置窗口名称
    setWindowTitle("Tank War");
    //设置窗口图标
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    //设置窗口大小
    setFixedSize(Width+160,Height);

    BPlusTree *pTree = new BPlusTree;
    int v;
    int i=0;
    vector<int> btreecode(1000);
    ifstream infile;   //输入流
    infile.open("C:/Users/hp/Desktop/shujujiegou/TankWar_V1.0/Tank30/btree.txt", ios::in);
    if (!infile.is_open())
        qDebug("Open file failure");
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> v;
        pTree->Insert(v);
        btreecode[v] = 807;
    }
    infile.close();   //关闭文件
    /*
    bool OK = true;
    QString text = QInputDialog::getText(NULL, "登陆界面(默认账户123）",
                                                       "你能想出密码算我输",
                                                       QLineEdit::Normal,
                                                       "",
                                                       &OK);
    if(OK) {
           QMessageBox::information(NULL, "Information",
                                               "Your comment is: <b>" + text + "</b>",
                                               QMessageBox::Yes | QMessageBox::No,
                                               QMessageBox::Yes);
    }*/
    //账号（数字）存进数组 新txt（账号+密码） 若冲突 用二次哈希 看与读取的密码是否匹配
    dlg = new inputdlg(this);
    dlg->exec();
    //dlg->close();
    /*qDebug("get it");
    //int code = text.toInt();
    int code = 123;
    RSA rsa;
    rsa.m = code;
    rsa.encrypt();
    int answer = rsa.c;
    answer = answer % 1000;
    int test = 123;
    bool success = pTree->Search(123);
    if (success) qDebug("find your account!");
    if (answer!=btreecode[test])
        showInformationMsg5();
    vector<int> b(1000);
    QFile file("../Tank30/mima.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    in.setCodec("GBK");
    i=0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        int dec = line.toInt();
        b[i++] = dec;
    }
    //qDebug()<<b[999];
    file.close();
    //int stage = b[answer];
    //qDebug()<<stage;*/
    label1=new QLabel(this);
    label2=new QLabel(this);
    label3=new QLabel(this);
    label4=new QLabel(this);
    label5=new QLabel(this);
    label6=new QLabel(this);
    label7=new QLabel(this);
    label8=new QLabel(this);
    label9=new QLabel(this);
    //初始化全局结构体glb的成员
    initGame();
    player = new QMediaPlayer(this);
   // player->setAudioRole(QAudio::GameRole);
    player->setVolume(50);
    player->setMedia(QUrl::fromLocalFile(SOURCEPATH+tr("start.wav")));
    player->play();
    player1 = new QMediaPlayer(this);
    player1->setMedia(QUrl::fromLocalFile(SOURCEPATH+tr("hit.wav")));
   // player1->setAudioRole(QAudio::GameRole);
    player1->setVolume(50);
    player2 = new QMediaPlayer(this);
    player2->setMedia(QUrl::fromLocalFile(SOURCEPATH+tr("lose.mp3")));
   // player2->setAudioRole(QAudio::GameRole);
    player2->setVolume(50);
    player3 = new QMediaPlayer(this);
    player3->setMedia(QUrl::fromLocalFile(SOURCEPATH+tr("add.wav")));
    //player3->setAudioRole(QAudio::GameRole);
    player3->setVolume(50);
    time.start();
}

MainWindow::~MainWindow()
{
    stopClock();
    delete painter_timer;
    delete checkBullet_timer;
    delete checkEnemyTank_timer;
}

void MainWindow::initGame()
{
    score=0;
    stage=1;
    //初始化全局结构体
    glb.map = new Map();
    glb.map->loadMap(stage);
    glb.tool = new gametool();

    collision = new Collision();
    qDebug()<<collision;

    QWidget *center=new QWidget(this);
    this->setCentralWidget(center); //设置画布为主界面

    //定义定时器
    painter_timer = new QTimer(this);
    checkBullet_timer = new QTimer(this);
    checkEnemyTank_timer = new QTimer(this);
    checkMyTank_timer = new QTimer(this);
    gameTool = new QTimer(this);
    gameTool1 = new QTimer(this);
    //设置定时器的时间间隔
    gameTool->setInterval(3000);
    gameTool1->setInterval(3000);
    painter_timer->setInterval(30);
    checkBullet_timer->setInterval(30);
    checkEnemyTank_timer->setInterval(30);
    checkMyTank_timer->setInterval(30);

    //设置每个定时器对应的超时函数
    connect(painter_timer, SIGNAL(timeout()), this, SLOT(updatefunction()));
    connect(checkBullet_timer,SIGNAL(timeout()),this,SLOT(CheckBullet()));
    connect(checkEnemyTank_timer,SIGNAL(timeout()),this,SLOT(CheckEnemyTank()));
    connect(checkMyTank_timer,SIGNAL(timeout()),this,SLOT(CheckMyTank()));

    //启动定时器
    isPause=false;
    startClock();
    time.start();
}

void MainWindow::speedcontrol()
{
    collision->doublespeed = false;
}

void MainWindow::startClock()
{
    painter_timer->start();
    checkBullet_timer->start();
    checkEnemyTank_timer->start();
    checkMyTank_timer->start();
}

void MainWindow::stopClock()
{
    painter_timer->stop();
    checkBullet_timer->stop();
    checkEnemyTank_timer->stop();
    checkMyTank_timer->stop();
}

void MainWindow::gametoolstop()
{
    checkEnemyTank_timer->stop();
}

void MainWindow::CheckBullet()
{
    collision->CheckBulletList(*glb.map);
}

void MainWindow::CheckEnemyTank()
{
    collision->CheckEnemyTankList(*glb.map);
}

void MainWindow::CheckMyTank()
{
    collision->CheckMyTankList();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //设置背景
    QPainter painter(this); //设置画笔

    painter.setBrush(Qt::black);    //设置地图为黑色
    QRect rectangel(0,0,Width,Height);
    painter.drawRect(rectangel);
    QRect rectangel2(Width,0,160,Height);
    painter.setBrush(Qt::gray);     //设置数据显示台为灰色

    glb.map->display(painter);       //画地图
    collision->paint(&painter);     //画子弹、敌方坦克和我方坦克
    glb.tool->paint(glb.tool,&painter);
    //重画丛林
    QPixmap pix;
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Col;j++)
        {
            if(glb.map->map[i][j].getKind()==JUNGLE)
            {
                pix.load(":/new/icon/pixs/5.png");
                painter.drawPixmap(i*PixWidth,j*PixHeight,PixWidth,PixHeight,pix);
            }
        }
    }
    painter.drawRect(rectangel2);       //画数据显示栏
    this->showPlayerInfo();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //游戏的暂停与开始
    if(event->key()==Qt::Key_P)
    {
        //暂停
        stopClock();
        isPause=true;
    }
    else if (event->key()==Qt::Key_K)
    {
        if (!glb.tool->queue1.empty())
        {
            player3->play();
            if (glb.tool->queue1.front()==gametool::Timer)
            {
                gametoolstop();
                gameTool->start();
                connect(gameTool, SIGNAL(timeout()), this, SLOT(startClock()));
                glb.tool->queue1.pop();
            }
            else if (glb.tool->queue1.front()==gametool::Bomb)
            {
                gameTool1->start();
                collision->doublespeed = true;
                connect(gameTool1, SIGNAL(timeout()), this, SLOT(speedcontrol()));
                glb.tool->queue1.pop();
            }
        }
    }
    else if(event->key()==Qt::Key_G)
    {
        //继续
        startClock();
        isPause=false;
    }
    else if(!isPause)
    {
        collision->controlMyTank(event,*glb.map);
        if(event->key()==Qt::Key_J)
        {
            player1->play();
        }
        else if(collision->getIsDouble() && event->key()==Qt::Key_0)
        {
            player1->play();//音效
        }
        repaint();//qt中用来更新画图的状态
    }
}

void MainWindow::updatefunction()
{
    repaint();
    if (glb.tool->flag == false&&glb.tool->tooltest1==true)
    {
        glb.tool->flag = true;
    }
    //判断游戏是否结束
    this->isGameOver();
    //qDebug("time out");
}

void MainWindow::isGameOver()
{
    if(glb.map->map[6][12].getKind()== PATH )  //结束
    {
        stopClock();
        showInformationMsg6();
    }
    else if(collision->getEnemyDeathSum()== ENEMY_TANK_SUM) //进入下一关
    {
        stopClock();
        QMessageBox::StandardButton rb =
                QMessageBox::question(this, "Win!", "Congratulation!\nNext Stage?",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb==QMessageBox::Yes)
        {
            //testgameover();
            if((stage+1)<=MAP_SUM)
            {
                stage++;
                score+=collision->getEnemyDeathSum()*100;
                delete collision;
                collision=new Collision();
                qDebug()<<collision;
                glb.map->loadMap(stage);
                startClock();
                repaint();
            }
            else
            {
                QMessageBox::information(this, "Win!", "All maps have been conquered!\nThanks for your playing!",
                                         QMessageBox::Yes ,QMessageBox::Yes);
                testgameover();
                exit(0);
            }
        }
        else
        {
            testgameover();
            exit(0);
        }

    }
}

void MainWindow::testgameover()
{
    player2->play();
    int a = time.elapsed()/1000;
    //qDebug()<<a<<"s";
    QFile file("../Tank30/rank.txt");
    //file.open( QIODevice::ReadWrite | QIODevice::Append);

    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out(&file);
    out.seek(file.size());//将当前读取文件指针移动到文件末尾
    out << '\n';
    out << a;
    file.close();

    vector<double> b;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    in.setCodec("GBK");
    while (!in.atEnd())
    {
        QString line = in.readLine();
        double dec = line.toDouble();
        b.push_back(dec);
        //qDebug()<<b[i];
    }
    file.close();
    QFile file1("../Tank30/rankaccount.txt");
    file1.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out1(&file);
    out1.seek(file1.size());//将当前读取文件指针移动到文件末尾
    out1 << '\n';
    out1 << "123";
    file1.close();
    vector<double> c;
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&file);
    in1.setCodec("GBK");
    while (!in1.atEnd())
    {
        QString line = in1.readLine();
        double dec = line.toDouble();
        c.push_back(dec);
    }
    file1.close();
    a = 5;
    ranking.resize(10);
    while (a--)
    {
        aa = f.quick_sort_select_kmin(b,0,b.size()-1,4-a);
        if (ranking[aa%10]==0) ranking[aa%10] = aa;
        else
        {
            int i = 1;
            while (ranking[aa%10]!=0)
            {
                aa = aa + i * i;
            }
            ranking[aa%10] = aa;
        }
    }
    sort(ranking.begin(),ranking.end());
    showInformationMsg4();
    stopClock();
}

void MainWindow::showInformationMsg1()
{
    setGeometry(550,300,30,20);
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    QMessageBox::information(this,tr("Tank War v1.0"),
                             tr("by 斌斌 老江"));
    return;
}
void MainWindow::showInformationMsg5()
{
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    QMessageBox::information(this,tr("game test"),
                             tr("你密码输错了还是让你玩一下"));
    return;
}

void MainWindow::showInformationMsg2()
{
    setGeometry(550,300,30,20);
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    QMessageBox::information(this,tr("操作说明"),
                             tr(
                              "    WASD  Control directions and move"
                              "\n\n    J    Fire"
                              "\n\n    P    Pause"
                              "\n\n    G    Resume"
                              "\n\n    K    UseGametool"
                              ));
    return;
}

void MainWindow::showInformationMsg4()
{
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    QMessageBox::information(this,tr("游戏排名"),
                              " no.1   "+
                                 QString::number(ranking[5], 10)+"s"+
                              "\n no.2   "+
                                 QString::number(ranking[6], 10)+"s"+
                             "\n no.3   "+
                             QString::number(ranking[7], 10)+"s"+
                             "\n no.4   "+
                             QString::number(ranking[8], 10)+"s"+
                             "\n no.5   "+
                             QString::number(ranking[9], 10)+"s"
    );
}

//游戏失败对话框
void MainWindow::showInformationMsg6()
{
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankU.png"));
    QMessageBox::StandardButton rb =
            QMessageBox::question(this, "GameOver", "Replay?",
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb==QMessageBox::Yes)
    {
        qDebug()<<"Yes"<<endl;
        delete collision;
        collision=new Collision();
        glb.map->loadMap(stage);
        startClock();
    }
    else
    {
        testgameover();
        exit(0);
    }
}

void MainWindow::showPlayerInfo()
{
    //1、得分score的信息
    label2->setText(tr("Scores:"));
    QRect r1(620,70,60,30);
    label2->setGeometry(r1);

    QString tempStr1;
    label1->setText(tempStr1.setNum(score+collision->getEnemyDeathSum()*100));
    QRect r2(620,110,80,30);
    label1->setGeometry(r2);

    //2、剩下敌方坦克的信息
    label3->setText(tr("Tanks Left:"));
    QRect r3(620,170,60,30);
    label3->setGeometry(r3);

    QString tempStr2;
    label4->setText(tempStr2.setNum(ENEMY_TANK_SUM-collision->getEnemyDeathSum()));
    QRect r4(640,210,60,30);
    label4->setGeometry(r4);

    //3、关卡数信息
    label5->setText(tr("Stages:"));
    QRect r5(620,270,60,30);
    label5->setGeometry(r5);

    QString tempStr3;
    label6->setText(tempStr3.setNum(stage));
    QRect r6(640,310,60,30);
    label6->setGeometry(r6);

    //4、玩家死亡次数
    label7->setText(tr("Death times:"));
    QRect r7(620,370,90,30);
    label7->setGeometry(r7);

    QString tempStr4;
    label8->setText(tempStr4.setNum(collision->getRebirthSum(0)));
    QRect r8(650,410,60,30);
    label8->setGeometry(r8);
}
