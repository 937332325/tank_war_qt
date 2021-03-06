#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

#define ORDER_V 2    /* 为简单起见，把v固定为2，实际的B+树v值应该是可配的 */

#define MAXNUM_KEY (ORDER_V * 2)   /* 内部结点中最多键个数，为2v */
#define MAXNUM_POINTER (MAXNUM_KEY+1)    /* 内部结点中最多指向子树的指针个数，为2v */
#define MAXNUM_DATA (ORDER_V * 2)   /* 叶子结点中最多数据个数，为2v */

/* 键值的类型*/
typedef int KEY_TYPE;    /* 为简单起见，定义为int类型，实际的B+树键值类型应该是可配的 */
                         /*备注： 为简单起见，叶子结点的数据也只存储键值*/

enum NODE_TYPE
{
    NODE_TYPE_ROOT = 1,    // 根结点
    NODE_TYPE_INTERNAL = 2,    // 内部结点
    NODE_TYPE_LEAF = 3,    // 叶子结点
};

#define INVALID 0

#define FLAG_LEFT 1
#define FLAG_RIGHT 2

/* 结点数据结构，为内部结点和叶子结点的父类 */
class CNode
{
public:
    CNode();
    virtual ~CNode();
    // 获取和设置有效数据个数
    int GetCount() { return m_Count; }
    void SetCount(int i) { m_Count = i; }
    NODE_TYPE GetType()
    {
        return m_Type;
    }
    // 获取和设置某个元素，对中间结点指键，对叶子结点指数据
    virtual KEY_TYPE GetElement(int i) { return 0; }
    virtual void SetElement(int i, KEY_TYPE value) { }
    // 获取和设置某个指针，对中间结点指指针，对叶子结点无意义
    virtual CNode* GetPointer(int i) { return NULL; }
    virtual void SetPointer(int i, CNode* pointer) { }
    void SetFather(CNode* father) { m_pFather = father; }
    CNode* GetFather() { return m_pFather; }
    // 删除结点
    void DeleteChildren();
protected:
    NODE_TYPE m_Type;    // 结点类型，取值为NODE_TYPE类型
    int m_Count;    // 有效数据个数，对中间结点指键个数，对叶子结点指数据个数
    CNode* m_pFather;     // 指向父结点的指针，标准B+树中并没有该指针，加上是为了更快地实现结点分裂和旋转等操作
};

class CInternalNode : public CNode
{
public:

    CInternalNode();
    virtual ~CInternalNode();

    // 获取和设置键值，对用户来说，数字从1开始
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_KEY))
        {
            return m_Keys[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE key)
    {
        if ((i > 0) && (i <= MAXNUM_KEY))
        {
            m_Keys[i - 1] = key;
        }
    }

    // 获取和设置指针，对用户来说，数字从1开始
    CNode* GetPointer(int i)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            return m_Pointers[i - 1];
        }
        else
        {
            return NULL;
        }
    }

    void SetPointer(int i, CNode* pointer)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            m_Pointers[i - 1] = pointer;
        }
    }

    // 插入键
    bool Insert(KEY_TYPE value, CNode* pNode);
    // 删除键
    bool Delete(KEY_TYPE value);

    // 分裂结点
    KEY_TYPE Split(CInternalNode* pNode, KEY_TYPE key);

protected:

    KEY_TYPE m_Keys[MAXNUM_KEY];           // 键数组
    CNode* m_Pointers[MAXNUM_POINTER];     // 指针数组

};

/* 叶子结点数据结构 */
class CLeafNode : public CNode
{
public:
    CLeafNode();
    virtual ~CLeafNode();
    // 获取和设置数据
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            return m_Datas[i - 1];
        }
        else
        {
            return INVALID;
        }
    }
    void SetElement(int i, KEY_TYPE data)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            m_Datas[i - 1] = data;
        }
    }
    // 获取和设置指针，对叶子结点无意义，只是实行父类的虚函数
    CNode* GetPointer()
    {
        return NULL;
    }
    // 插入数据
    bool Insert(KEY_TYPE value);
    // 分裂结点
    KEY_TYPE Split(CNode* pNode);
public:
    // 以下两个变量用于实现双向链表
    CLeafNode* m_pPrevNode;                 // 前一个结点
    CLeafNode* m_pNextNode;                 // 后一个结点
protected:
    KEY_TYPE m_Datas[MAXNUM_DATA];    // 数据数组
};
class BPlusTree
{
public:
    BPlusTree();
    virtual ~BPlusTree();
    bool Search(KEY_TYPE data);
    bool Insert(KEY_TYPE data);
    void ClearTree();
    void PrintTree();
    void PrintNode(CNode* pNode);
    void SetRoot(CNode* root)
    {
        m_Root = root;
    }
    CNode* GetRoot()
    {
        return m_Root;
    }
    CLeafNode* m_pLeafHead;                 // 头结点
    CLeafNode* m_pLeafTail;                   // 尾结点
protected:
    // 为插入而查找叶子结点
    CLeafNode* SearchLeafNode(KEY_TYPE data);
    //插入键到中间结点
    bool InsertInternalNode(CInternalNode* pNode, KEY_TYPE key, CNode* pRightSon);
    CNode* m_Root;    // 根结点
    int m_Depth;      // 树的深度
};

#endif // BPLUSTREE_H
