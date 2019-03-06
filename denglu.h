#ifndef DENGLU_H
#define DENGLU_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QLayout>
#include <QValidator>
#include <QFile>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class user
{
public:
    QString zhanghao,mima,shengri,email;
    bool operator>(const user a)
    {
        if (a.shengri.toInt()/100<shengri.toInt()/100)
            return true;
        else if ((a.shengri.toInt()/100==shengri.toInt()/100)&&(a.shengri.toInt()%100>shengri.toInt()%100))
            return true;
        return true;
    }
};


class denglu : public QDialog
{
    Q_OBJECT
private:
    QLabel **m_Labels;
    QLineEdit **m_LineEdits;
    QPushButton *m_OKButton;
    QPushButton *m_CancelButton;
    QString zhanghao;
    QString mima;
    int N;
public:
    denglu(int count,QWidget *parent = 0);
    virtual ~denglu();
    void SetLabelTexts(const QStringList &listText);
    void SetOneLabelText(int index, const QString &text);
    QString GetOneText(int index);
    //为了让多组输入框看起来整齐些，所以我固定了QLabel的宽度
    void SetLabelsWidth(int width);

private slots:
    void accept()
    {
        QDialog::accept();
    }
    void reject()
    { QDialog::reject(); }
};

#endif // DENGLU_H
