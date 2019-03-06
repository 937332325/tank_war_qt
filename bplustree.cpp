#include "bplustree.h"

CNode::CNode()
{
    m_Type = NODE_TYPE_LEAF;
    m_Count = 0;
    m_pFather = NULL;
}
CNode::~CNode()
{
    DeleteChildren();
}
void CNode::DeleteChildren()
{
    for (int i = 1; i <= m_Count; i++)
    {
        CNode *pnode = GetPointer(i);
        if (pnode != NULL) pnode->DeleteChildren();
        delete pnode;
    }
}

CInternalNode::CInternalNode()
{
    m_Type = NODE_TYPE_INTERNAL;
    for (int i = 0; i < MAXNUM_POINTER; i++)
        m_Pointers[i] = NULL;
    for (int i = 0; i < MAXNUM_DATA; i++)
        m_Keys[i] = INVALID;
}
CInternalNode::~CInternalNode()
{
    for (int i = 0; i < MAXNUM_POINTER; i++)
        m_Pointers[i] = NULL;
}
bool CInternalNode::Insert(KEY_TYPE value, CNode* pNode)
{
    if (GetCount() > MAXNUM_KEY) return false;
    int i = 0, j = 0;
    for (i = 0; (i < m_Count) && (value > m_Keys[i]); i++);
    for (j = m_Count; j > i; j--)
        m_Keys[j - 1] = m_Keys[j];
    for (j = m_Count + 1; j > i + 1; j--)
        m_Pointers[j] = m_Pointers[j - 1];//为什么要+1
    m_Keys[i] = value;
    m_Pointers[i + 1] = pNode;
    pNode->SetFather(this);
    m_Count++;
    return true;
}
bool CInternalNode::Delete(KEY_TYPE key)
{
    int i = 0;
    for (i = 0; (i > 0) && (key != m_Keys[i]); i--);
    int j = i - 1;
    for (j = i - 1; j < m_Count - 1; j++)
    {
        m_Keys[j] = m_Keys[j + 1];
    }
    m_Keys[j] = INVALID;
    int k = i;
    for (k = i; k < m_Count; k++)
    {
        m_Pointers[k] = m_Pointers[k + 1];
    }
    m_Pointers[k] = NULL;
    m_Count--;
    return true;
}
KEY_TYPE CInternalNode::Split(CInternalNode* pNode, KEY_TYPE key)
{
    int i = 0, j = 0;

    // 如果要插入的键值在第V和V+1个键值中间，需要翻转一下，因此先处理此情况
    if ((key > this->GetElement(ORDER_V)) && (key < this->GetElement(ORDER_V + 1)))
    {
        // 把第V+1 -- 2V个键移到指定的结点中 ????????

        for (i = ORDER_V + 1; i <= MAXNUM_KEY; i++)
        {
            j++;
            pNode->SetElement(j, this->GetElement(i));
            this->SetElement(i, INVALID);
        }

        // 把第V+2 -- 2V+1个指针移到指定的结点中
        j = 0;
        for (i = ORDER_V + 2; i <= MAXNUM_POINTER; i++)
        {
            j++;
            this->GetPointer(i)->SetFather(pNode);    // 重新设置子结点的父亲
            pNode->SetPointer(j, this->GetPointer(i));
            this->SetPointer(i, INVALID);
        }

        // 设置好Count个数
        this->SetCount(ORDER_V);
        pNode->SetCount(ORDER_V);

        // 把原键值返回
        return key;
    }
    // 以下处理key小于第V个键值或key大于第V+1个键值的情况
    // 判断是提取第V还是V+1个键
    int position = 0;
    if (key < this->GetElement(ORDER_V))
    {
        position = ORDER_V;
    }
    else
    {
        position = ORDER_V + 1;
    }
    // 把第position个键提出来，作为新的键值返回
    KEY_TYPE RetKey = this->GetElement(position);

    // 把第position+1 -- 2V个键移到指定的结点中
    j = 0;
    for (i = position + 1; i <= MAXNUM_KEY; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i));
        this->SetElement(i, INVALID);
    }
    // 把第position+1 -- 2V+1个指针移到指定的结点中(注意指针比键多一个)
    j = 0;
    for (i = position + 1; i <= MAXNUM_POINTER; i++)
    {
        j++;
        this->GetPointer(i)->SetFather(pNode);    // 重新设置子结点的父亲
        pNode->SetPointer(j, this->GetPointer(i));
        this->SetPointer(i, INVALID);
    }
    // 清除提取出的位置
    this->SetElement(position, INVALID);
    // 设置好Count个数
    this->SetCount(position - 1);
    pNode->SetCount(MAXNUM_KEY - position);
    return RetKey;
}

CLeafNode::CLeafNode()
{
    m_Type = NODE_TYPE_LEAF;
    for (int i = 0; i < MAXNUM_DATA; i++)
        m_Datas[i] = INVALID;
    m_pPrevNode = NULL;
    m_pNextNode = NULL;
}
CLeafNode::~CLeafNode()
{
}
bool CLeafNode::Insert(KEY_TYPE value)
{
    // 如果叶子结点已满，直接返回失败
    if (GetCount() >= MAXNUM_DATA)
    {
        return false;
    }

    // 找到要插入数据的位置
    int i = 0;
    for (i = 0; (value > m_Datas[i]) && (i < m_Count); i++)
    {
    }

    // 当前位置及其后面的数据依次后移，空出当前位置
    for (int j = m_Count; j > i; j--)
    {
        m_Datas[j] = m_Datas[j - 1];
    }

    // 把数据存入当前位置
    m_Datas[i] = value;

    m_Count++;

    // 返回成功
    return true;
}
// 查找对应的叶子结点
CLeafNode* BPlusTree::SearchLeafNode(KEY_TYPE data)
{
    int i = 0;

    CNode * pNode = GetRoot();
    // 循环查找对应的叶子结点
    while (NULL != pNode)
    {
        // 结点为叶子结点，循环结束
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        // 找到第一个键值大于等于key的位置
        for (i = 1; i <= pNode->GetCount(); i++)
        {
            if (data < pNode->GetElement(i))
            {
                break;
            }
        }

        pNode = pNode->GetPointer(i);
    }

    return (CLeafNode*)pNode;
}

// 分裂叶子结点，把本叶子结点的后一半数据剪切到指定的叶子结点中
KEY_TYPE CLeafNode::Split(CNode* pNode)
{
    // 把本叶子结点的后一半数据移到指定的结点中
    int j = 0;
    for (int i = ORDER_V + 1; i <= MAXNUM_DATA; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i));
        this->SetElement(i, INVALID);
    }
    // 设置好Count个数
    this->SetCount(this->GetCount() - j);
    pNode->SetCount(pNode->GetCount() + j);
    // 返回新结点的第一个元素作为键
    return pNode->GetElement(1);
}
BPlusTree::BPlusTree()
{
    m_Depth = 0;
    m_Root = NULL;
    m_pLeafHead = NULL;
    m_pLeafTail = NULL;
}
BPlusTree::~BPlusTree()
{
    ClearTree();
}
bool BPlusTree::Search(KEY_TYPE data)
{
    int i = 0;
    CNode *pNode = m_Root;
    // 循环查找对应的叶子结点
    while (pNode != NULL)
    {
        if (NODE_TYPE_LEAF == pNode->GetType()) break;
        for (i = 1; (data >= pNode->GetElement(i)) && (i <= pNode->GetCount()); i++);
        pNode = pNode->GetPointer(i);
    }
    // 没找到
    if (NULL == pNode)
    {
        return false;
    }
    bool found = false;
    for (i = 1; (i <= pNode->GetCount()); i++)
    {
        if (data == pNode->GetElement(i))
        {
            found = true;
        }
    }
    return found;
}
// 清除整个树，删除所有结点
void BPlusTree::ClearTree()
{
    CNode* pNode = m_Root;
    if (NULL != pNode)
    {
        pNode->DeleteChildren();

        delete pNode;
    }

    m_pLeafHead = NULL;
    m_pLeafTail = NULL;
    SetRoot(NULL);
}
bool BPlusTree::Insert(KEY_TYPE data)
{
    CLeafNode *pOldNode = SearchLeafNode(data);
    if (pOldNode == NULL)
    {
        pOldNode = new CLeafNode;
        m_pLeafHead = pOldNode;
        m_pLeafTail = pOldNode;
        SetRoot(pOldNode);
    }
    // 叶子结点未满，对应情况1，直接插入
    if (pOldNode->GetCount() < MAXNUM_DATA)
    {
        return pOldNode->Insert(data);
    }
    // 原叶子结点已满，新建叶子结点，并把原结点后一半数据剪切到新结点
    CLeafNode* pNewNode = new CLeafNode;
    KEY_TYPE key = INVALID;
    key = pOldNode->Split(pNewNode);
    // 在双向链表中插入结点
    CLeafNode*pOldNext = pOldNode->m_pNextNode;
    pOldNode->m_pNextNode = pNewNode;
    pNewNode->m_pNextNode = pOldNext;
    pNewNode->m_pPrevNode = pOldNode;
    if (NULL == pOldNext)
    {
        m_pLeafTail = pNewNode;
    }
    else
    {
        pOldNext->m_pPrevNode = pNewNode;
    }
    // 判断是插入到原结点还是新结点中，确保是按数据值排序的
    if (data < key)
    {
        pOldNode->Insert(data);    // 插入原结点
    }
    else
    {
        pNewNode->Insert(data);    // 插入新结点
    }
    // 父结点
    CInternalNode* pFather = (CInternalNode*)(pOldNode->GetFather());
    // 如果原结点是根节点，对应情况2
    if (NULL == pFather)
    {
        CNode* pNode1 = new CInternalNode;
        pNode1->SetPointer(1, pOldNode);                           // 指针1指向原结点
        pNode1->SetElement(1, key);                                // 设置键
        pNode1->SetPointer(2, pNewNode);                           // 指针2指向新结点
        pOldNode->SetFather(pNode1);                               // 指定父结点
        pNewNode->SetFather(pNode1);                               // 指定父结点
        pNode1->SetCount(1);
        SetRoot(pNode1);                                           // 指定新的根结点
        return true;
    }
    // 情况3和情况4在这里实现
    bool ret = InsertInternalNode(pFather, key, pNewNode);
    return ret;
}
bool BPlusTree::InsertInternalNode(CInternalNode* pNode, KEY_TYPE key, CNode* pRightSon)
{
    if (NULL == pNode || NODE_TYPE_LEAF == pNode->GetType())
    {
        return false;
    }

    // 结点未满，直接插入
    if (pNode->GetCount() < MAXNUM_KEY)
    {
        return pNode->Insert(key, pRightSon);
    }

    CInternalNode* pBrother = new CInternalNode;
    KEY_TYPE NewKey = INVALID;
    // 分裂本结点
    NewKey = pNode->Split(pBrother, key);

    if (pNode->GetCount() < pBrother->GetCount())
    {
        pNode->Insert(key, pRightSon);
    }
    else if (pNode->GetCount() > pBrother->GetCount())
    {
        pBrother->Insert(key, pRightSon);
    }
    else    // 两者相等，即键值在第V和V+1个键值中间的情况，把字节点挂到新结点的第一个指针上
    {
        pBrother->SetPointer(1, pRightSon);
        pRightSon->SetFather(pBrother);
    }

    CInternalNode* pFather = (CInternalNode*)(pNode->GetFather());
    // 直到根结点都满了，新生成根结点
    if (NULL == pFather)
    {
        pFather = new CInternalNode;
        pFather->SetPointer(1, pNode);                           // 指针1指向原结点
        pFather->SetElement(1, NewKey);                          // 设置键
        pFather->SetPointer(2, pBrother);                        // 指针2指向新结点
        pNode->SetFather(pFather);                               // 指定父结点
        pBrother->SetFather(pFather);                            // 指定父结点
        pFather->SetCount(1);

        SetRoot(pFather);                                        // 指定新的根结点
        return true;
    }

    // 递归
    return InsertInternalNode(pFather, NewKey, pBrother);
}
