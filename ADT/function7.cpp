#include "head7.h"
CSTree MakeTree(TElemType e, int n, ...)
{
    //创建根节点e和n棵子树的树
    int i;
    CSTree t, p, pi;
    va_list argptr; //存放变长参数的数组
    t = (CSTree)malloc(sizeof(CSTNode));
    if (t == NULL)
        return NULL;
    t->data = e;
    t->firstChild = t->nextSibling = NULL;
    if (n < 1)
        return t;

    //令argptr指向参数n的第一个实参
    // va_start(argptr, n);
    //取第一个实参并转换为CSTree类型
    // p = va_arg(argptr, CSTree);
    t->firstChild = p;
    pi = p;
    for (i = 1; i < n; i++)
    {
        // p = va_arg(argptr, CSTree);
        pi->nextSibling = p;
        pi = p;
    }
    // va_end(argptr); //结束取实参
    return t;
}
Status InsertChild(CSTree &T, int i, CSTree c)
{
    //插入第i棵子树
    int j;
    CSTree p;
    if (T == NULL || i < 1)
        return ERROR;
    if (i == 1)
    {
        c->nextSibling = T->firstChild;
        T->firstChild = c;
    }
    else
    {
        p = T->firstChild;
        for (j = 2; p != NULL && j < i; j++)
            p = p->nextSibling;
        if (j == i)
        {
            c->nextSibling = p->nextSibling;
            p->nextSibling = c;
        }
        else
            return ERROR;
    }
    return OK;
}
Status PreOrderTraverseForest(CSForest F, Status (*visit)(TElemType))
{
    if (F == NULL)
        return ERROR;
    if (visit(F->data) == ERROR)
        return ERROR;
    return PreOrderTraverseForest(F->firstChild, visit) && PreOrderTraverseForest(F->nextSibling, visit);
}
int ForestDepth(CSForest F)
{
    int dep1, dep2, dep;
    if (F == NULL)
        dep = 0;
    else
    {
        dep1 = ForestDepth(F->firstChild);
        dep2 = ForestDepth(F->nextSibling);
        dep = dep1 + 1 > dep2 ? dep1 + 1 : dep2;
    }
    return dep;
}
CSTNode *Search(CSForest F, TElemType e)
{
    CSTNode *result = NULL;
    if (F == NULL)
        return NULL;
    if (F->data = e)
        return F;
    if ((result = Search(F->firstChild, e)) != NULL)
        return result;
    return Search(F->nextSibling, e);
}
Status InitMFSet(MFSet &S, int n)
{
    int i;
    S.parent = (int *)malloc(sizeof(int) * n);
    if (S.parent == NULL)
        return ERROR;
    for (i = 0; i < n; i++)
        S.parent[i] = -1;
    S.n = n;
    return OK;
}
int FindMFSet(MFSet &S, int i)
{
    if (i < 0 || i >= S.n)
        return -1;
    while (S.parent[i] >= 0)
        i = S.parent[i];
    return i;
}
Status UnionMFSet(MFSet &S, int i, int j)
{
    int ri, rj;
    if (i < 0 || j < 0 || i >= S.n || j >= S.n)
        return FALSE;
    ri = FindMFSet(S, i);
    rj = FindMFSet(S, j);
    if (ri == rj)
        return FALSE;
    S.parent[ri] = rj;
    // S.parent[rj]=ri;
    return TRUE;
}
Status UnionMFSet_WUR(MFSet &S, int i, int j)
{
    int ri, rj;
    if (i < 0 || j < 0 || i > S.n || j > S.n)
        return FALSE;
    ri = FindMFSet(S, i);
    rj = FindMFSet(S, j);
    if (ri == rj)
        return FALSE;
    //注意是取绝对值
    if (S.parent[ri] > S.parent[rj])
    {
        S.parent[rj] += S.parent[ri];
        S.parent[ri] = rj;
    }
    else
    {
        S.parent[ri] += S.parent[rj];
        S.parent[rj] = ri;
    }
    return TRUE;
}
int FindMFSet_PC(MFSet &S, int i)
{
    if (i < 0 || i >= S.n)
        return -1;
    if (S.parent[i] < 0)
        return i;
    S.parent[i] = FindMFSet(S, S.parent[i]);
    return S.parent[i];
}
Status hasRelationship(MFSet &S, int a, int b)
{
    if (a < 0 || b < 0 || a >= S.n || b >= S.n)
        return FALSE;
    if (FindMFSet_PC(S, a) == FindMFSet_PC(S, b))
        return TRUE;
    return FALSE;
}
void SearchBTree(BTree t, int k, result &r)
{
    int i = 0, found = 0;
    BTree p = t, q = NULL;
    while (p != NULL && found == 0)
    {
        i = Search(p, k);
        if (i <= p->keynum && p->key[i] == k)
            found = 1;
        else
        {
            q = p;
            p = p->ptr[i - 1];
        }
    }
    if (found == 1)
    {
        r.pt = p;
        r.i = i;
        r.tag = 1;
    }
    else
    {
        r.pt = q;
        r.i = i;
        r.tag = 0;
    }
}
int Search(BTree p, int k)
{
    int i = 1;
    while (i <= p->keynum && k > p->key[i])
        i++;
    return i;
}