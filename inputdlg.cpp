#include "inputdlg.h"
#include <QPoint>
#include <QDebug>

inputdlg::inputdlg(QWidget *parent):QDialog(parent)
{
    setWindowTitle(tr("账户管理系统"));
    this->setFixedSize(600,450);
    QPoint p1;
    p1.setX(400);
    p1.setY(200);
    this->move(p1);
    /*nameLabel1 = new QLabel;
    nameLabel1->setText(tr("姓名:"));
    nameLabel2 = new QLabel;
    nameLabel2->setText(tr("海斌"));
    nameLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    namebtn = new QPushButton;
    namebtn->setText(tr("修改姓名"));*/

    denglubtn = new QPushButton;
    denglubtn->setText(tr("点这里登录"));
    denglubtn->setFixedSize(150,50);

    xiugaibtn = new QPushButton;
    xiugaibtn->setText(tr("点这里修改个人信息"));
    xiugaibtn->setFixedSize(150,50);

    shanchubtn = new QPushButton;
    shanchubtn->setText(tr("点这里删除用户"));
    shanchubtn->setFixedSize(150,50);

    tianjiabtn = new QPushButton;
    tianjiabtn->setText(tr("点这里添加用户"));
    tianjiabtn->setFixedSize(150,50);

    shengribtn = new QPushButton;
    shengribtn->setText(tr("查一下谁快要过生日了吧"));
    shengribtn->setFixedSize(150,50);

    sortbtn = new QPushButton;
    sortbtn->setText(tr("按生日排个序"));
    sortbtn->setFixedSize(150,50);

    mainLayout = new QGridLayout(this);
    /*mainLayout->addWidget(nameLabel1,1,0);
    mainLayout->addWidget(nameLabel2,1,10);
    mainLayout->addWidget(namebtn,1,20);*/
    mainLayout->addWidget(denglubtn,0,0);
    mainLayout->addWidget(xiugaibtn,0,10);
    mainLayout->addWidget(shanchubtn,10,0);
    mainLayout->addWidget(tianjiabtn,10,10);
    mainLayout->addWidget(shengribtn,20,0);
    mainLayout->addWidget(sortbtn,20,10);

    mainLayout->setMargin(15);
    mainLayout->setSpacing(15);
    //connect(namebtn,SIGNAL(clicked()),this,SLOT(changename()));
    connect(denglubtn,SIGNAL(clicked()),this,SLOT(denglufunc()));
    connect(xiugaibtn,SIGNAL(clicked()),this,SLOT(xiugaifunc()));
    connect(shanchubtn,SIGNAL(clicked()),this,SLOT(shanchufunc()));
    connect(tianjiabtn,SIGNAL(clicked()),this,SLOT(tianjiafunc()));
    connect(shengribtn,SIGNAL(clicked()),this,SLOT(shengrifunc()));
    connect(sortbtn,SIGNAL(clicked()),this,SLOT(sortfunc()));

    QFile data("C://Users/hp/Desktop/qtcode/guanlixitong/user.txt");
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        while ( !in.atEnd() )
        {
            QString e,b,c,d;
            user User;
            in >> e >> b >>c >>d;
            User.zhanghao = e;
            User.mima = b;
            User.shengri = c;
            User.email = d;
            a.push_back(User);
            //qDebug("ok");
        }
    }
    data.close();
}

inputdlg::~inputdlg()
{

}



//登陆 修改 查找
void inputdlg::changename()
{
    qDebug("change name");
}

void inputdlg::denglufunc()
{
    denglu dialog(2);
    QStringList list;
    list << "账号: " << "密码: ";
    dialog.SetLabelTexts(list);
    dialog.SetLabelsWidth(30);
    dialog.exec();
    for (unsigned int i=0;i<a.size();i++)
    {
        if (dialog.GetOneText(0)==a[i].zhanghao&&dialog.GetOneText(1)==a[i].mima)
        {
            QMessageBox::information(this,tr("通知"),tr("登陆成功"));
            break;
        }
    }
}

void inputdlg::xiugaifunc()
{
    denglu dialog(4);
    QStringList list;
    list << "账号:  " << "密码:  "<<"生日:  "<<"email地址:";
    dialog.SetLabelTexts(list);
    dialog.SetLabelsWidth(30);
    dialog.exec();
    for (unsigned int i=0;i<a.size();i++)
    {
        if (dialog.GetOneText(0)==a[i].zhanghao)
        {
            a[i].mima = dialog.GetOneText(1);
            a[i].shengri = dialog.GetOneText(2);
            a[i].email = dialog.GetOneText(3);
            QMessageBox::information(this,tr("通知"),tr("账号匹配成功,修改完毕"));
            break;
        }
    }
    write();
}

void inputdlg::shanchufunc()
{
    denglu dialog(4);
    QStringList list;
    list << "账号:  " << "密码:  "<<"生日:  "<<"email地址:";
    dialog.SetLabelTexts(list);
    dialog.SetLabelsWidth(30);
    dialog.exec();
    for (unsigned int i=0;i<a.size();i++)
    {
        if (dialog.GetOneText(0)==a[i].zhanghao&&a[i].mima==dialog.GetOneText(1)&&
                a[i].shengri == dialog.GetOneText(2)&&a[i].email == dialog.GetOneText(3))
        {
            a.erase(a.begin()+i);
            QMessageBox::information(this,tr("通知"),tr("账号匹配成功,删除完成"));
            break;
        }
    }
    write();
}

void inputdlg::tianjiafunc()
{
    denglu dialog(4);
    QStringList list;
    list << "账号:  " << "密码:  "<<"生日:  "<<"email地址:";
    dialog.SetLabelTexts(list);
    dialog.SetLabelsWidth(30);
    dialog.exec();
    user Use;
    Use.zhanghao = dialog.GetOneText(0);
    Use.mima = dialog.GetOneText(1);
    Use.shengri = dialog.GetOneText(2);
    Use.email = dialog.GetOneText(3);
    a.push_back(Use);
    QMessageBox::information(this,tr("通知"),tr("已添加新用户"));
    write();
}

void inputdlg::shengrifunc()
{
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("MMdd");
    int today = currentDate.toInt();
    for (unsigned int i=0;i<a.size();i++)
    {
        int shengri = a[i].shengri.toInt();
        if (shengri%100-today%100<7&&shengri-today>0)
        {
            QMessageBox::information(this,tr("通知"),tr("7天内生日的有")+a[i].zhanghao);
        }
    }
    //qDebug()<<currentDate;
}

void inputdlg::sortfunc()
{
    unsigned work;
    user temp;
    for (unsigned int pass=1;pass<a.size();pass++)
    {
        work = 1;
        for (unsigned i=0;i<a.size()-pass;i++)
        {
            if (a[i]>a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                work = 0;
            }
        }
        if (work) break;
    }
    QMessageBox::information(this,tr("仅显示前5个"),
                              " no.1   "+
                                 a[5].zhanghao+" "+a[5].shengri+
                              "\n no.2   "+
                                 a[4].zhanghao+" "+a[4].shengri+
                             "\n no.3   "+
                                 a[3].zhanghao+" "+a[3].shengri+
                             "\n no.4   "+
                             a[2].zhanghao+" "+a[2].shengri+
                             "\n no.5   "+
                             a[1].zhanghao+" "+a[1].shengri
    );
}

void inputdlg::write()
{
    QFile file("C://Users/hp/Desktop/qtcode/guanlixitong/user.txt");
    if (file.open(QFile::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&file);
        for (unsigned int i=0;i<a.size();i++)
        {
            //怎么过行
            out << a[i].zhanghao << " "<<a[i].mima << " "<<a[i].shengri << " "<<a[i].email << " ";
            //out << "\n";
        }
    }
    file.close();
}

