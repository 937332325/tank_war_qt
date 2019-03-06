#ifndef DATA_H
#define DATA_H

class Map;
class gametool;
#include<QImage>
#include<QMediaPlayer>
#include <vector>
#include <algorithm>
using namespace std;

static const QString SOURCEPATH = QObject::tr("../Tank30/music/");

struct Glb
{
    Map *map;
    gametool *tool;
};
extern Glb glb;

class Finder
{
public:
    double quick_sort_select_kmin(vector<double> A,int first,int last,int k){// k从下标0开始算起
        if(k<first || k>last){
            return 0;
        }
        if(first>=last){
            if(first==last && k==last) //只有一个元素时
                return A[k];
        }
        int i=first,j=last+1;
        int index=rand()%(last-first+1)+first;
        swap(A[first],A[index]); // 取随机数中的一个作为随机轴点
        double x=A[i];
        while(i<j){
            do{
                j--;
            } while (i<j && A[j]>x);
            do{
                i++;
            }while(i<j && A[i]<x);

            if(i>=j)
                break;
            swap(A[i],A[j]);
        }
        swap(A[first],A[j]);
        if(j==k){
            return A[k];
        }
        else if(j>k)
            return quick_sort_select_kmin(A,first,j-1,k);
        else
            return quick_sort_select_kmin(A,j+1,last,k);
    }
};
#endif // DATA_H
