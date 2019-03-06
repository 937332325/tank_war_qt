#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QInputDialog>
#include <denglu.h>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>

class inputdlg : public QDialog
{
    Q_OBJECT
public:
    inputdlg(QWidget* parent=0);
    ~inputdlg();
    vector<user> a;
    //denglu dialog;
private slots:
    void changename();
    void denglufunc();
    void xiugaifunc();
    void shanchufunc();
    void tianjiafunc();
    void shengrifunc();
    void sortfunc();
    void write();
private:
    //QLabel *nameLabel1,*nameLabel2;
    QPushButton *denglubtn,*xiugaibtn,*shanchubtn,*tianjiabtn,*shengribtn,*sortbtn;
    QGridLayout *mainLayout;
    QDateTime dt;
    QDate date;
    QTime t1,t2;
};

#endif // INPUTDLG_H
