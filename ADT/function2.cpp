#include "head2.h"

Status InitStack_Sq(SqStack &S, int size, int inc)
{
    S.elem = (ElemType *)malloc(size * sizeof(ElemType));
    if (S.elem == NULL)
        return OVERFLOW;
    S.top = 0;
    S.size = size;
    S.inc = inc;
    return OK;
}
Status Push_Sq(SqStack &S, ElemType e)
{
    if (S.top >= S.size)
    {
        ElemType *temp;
        temp = (ElemType *)realloc(S.elem, (S.size + S.inc) * sizeof(ElemType));
        if (temp == NULL)
            return OVERFLOW;
        S.elem = temp;
        S.size += S.inc;
    }
    S.elem[S.top++] = e;
    return OK;
}
Status Pop_Sq(SqStack &S, ElemType &e)
{
    if (S.top == 0)
        return ERROR;
    e = S.elem[--S.top];
}

Status Push_LS(LStack &S, ElemType e)
{
    LSNode *p;
    p = (LSNode *)malloc(sizeof(LSNode));
    if (p == NULL)
        return OVERFLOW;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}
Status Pop_LS(LStack &S, ElemType &e)
{
    if (S == NULL)
        return ERROR;
    LSNode *p;
    p = S;
    S = S->next;
    e = p->data;
    free(p);
    return OK;
}

Status InitQueue_Sq(SqQueue &Q, int size)
{
    Q.elem = (ElemType *)malloc(size * sizeof(ElemType));
    if (Q.elem == NULL)
        return OVERFLOW;
    Q.size = size;
    Q.front = Q.rear = 0;
    return OK;
}
Status DeQueue_Sq(SqQueue &Q, ElemType &e)
{
    if (Q.front == Q.rear)
        return ERROR;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % Q.size;
    return OK;
}
Status EnQueue_Sq(SqQueue &Q, ElemType e)
{
    if (Q.front == (Q.rear + 1) % Q.size)
        return ERROR;
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.size;
    return OK;
}

Status EnQueue_LQ(LQueue &Q, ElemType e)
{
    LQNode *p;
    p = (LQNode *)malloc(sizeof(LQNode));
    if (p == NULL)
        return OVERFLOW;
    p->data = e;
    p->next = NULL;
    if (Q.front == NULL)
        Q.front = p;
    else
        Q.rear->next = p;
    Q.rear = p;
    return OK;
}
Status DeQueue_LQ(LQueue &Q, ElemType &e)
{
    if (Q.front == NULL)
        return ERROR;
    LQNode *p;
    p = Q.front;
    Q.front = Q.front->next;
    if (Q.rear = p)
        Q.rear = NULL;
    e = p->data;
    free(p);
    return OK;
}

Status DeleteLast_Sq(SqList &L, ElemType &e)
{
    if (L.length == 0)
        return ERROR;
    e = L.elem[--L.length];
    return OK;
}
int Search_Sq(SqList L, ElemType e)
{
    int i;
    while (i < L.length && L.elem[i] != e)
        i++;
    if (i == L.length)
        return -1;
    return i;
}
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
    int i = 0, j = 0, size, inc = 10;
    ElemType ai, bj;
    size = La.length + Lb.length;
    InitList_Sq(Lc, size, inc);
    GetElem_Sq(La, i, ai);
    GetElem_Sq(Lb, j, bj);
    while (i < La.length && j < Lb.length)
    {
        if (ai <= bj)
        {
            Append_Sq(Lc, ai);
            GetElem_Sq(La, ++i, ai);
        }
        else
        {
            Append_Sq(Lc, bj);
            GetElem_Sq(Lb, ++j, bj);
        }
    }
    while (i < La.length)
    {
        GetElem_Sq(La, i++, ai);
        Append_Sq(Lc, ai);
    }
    while (j < Lb.length)
    {
        GetElem_Sq(Lb, j++, bj);
        Append_Sq(Lc, bj);
    }
}

Status CreatPoly(Poly &P, Term e[], int n)
{
    int i;
    P.elem = (Term *)malloc(n * sizeof(Term));
    if (P.elem == NULL)
        return OVERFLOW;
    for (i = 0; i < n; i++)
        P.elem[i] = e[i];
    P.length = n;
    return OK;
}
Status AddPoly(Poly pa, Poly pb, Poly &pc)
{
    int i, j, k;
    i = j = k = 0;
    float c;
    pc.elem = (Term *)malloc((pa.length + pb.length) * sizeof(Term));
    if (pc.elem == NULL)
        return OVERFLOW;
    while (i < pa.length && j < pa.length)
    {
        if (pa.elem[i].expn < pb.elem[j].expn)
            pc.elem[k++] = pa.elem[i++];
        else if (pa.elem[i].expn > pb.elem[j].expn)
            pc.elem[k++] = pb.elem[j++];
        else
        {
            c = pa.elem[i].coef + pb.elem[j].coef;
            if (c != 0)
            {
                pc.elem[k].expn = pa.elem[i].expn;
                pc.elem[k++].coef = c;
            }
            i++;
            j++;
        }
    }
    while (i < pa.length)
        pc.elem[k++] = pa.elem[i++];
    while (j < pb.length)
        pc.elem[k++] = pb.elem[j++];
    if (k < pa.length + pb.length)
        if ((pc.elem = (Term *)realloc(pc.elem, k * sizeof(Term))) == NULL)
            return OVERFLOW;
    pc.length = k;
    return OK;
}

Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int i, p;
    int *num, *cpos;
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu != 0)
    {
        T.data = (Triple *)malloc((T.tu + 1) * sizeof(Triple));
        num = (int *)malloc((M.nu + 1) * sizeof(int));
        cpos = (int *)malloc((M.nu + 1) * sizeof(int));
        if (num == NULL || cpos == NULL || T.data == NULL)
            return OVERFLOW;
        for (i = 1; i <= M.nu; i++)
            num[i] = 0;
        for (i = 1; i <= M.tu; i++)
            num[M.data[i].j]++;
        cpos[1] = 1;
        for (i = 2; i <= M.nu; i++)
            cpos[i] = num[i - 1] + cpos[i - 1];
        for (p - 1; p <= M.tu; p++)
        {
            i = M.data[p].j;
            T.data[cpos[i]].i = M.data[p].j;
            T.data[cpos[i]].j = M.data[p].i;
            T.data[cpos[i]].e = M.data[p].e;
            cpos[i]++;
        }
    }
    free(num);
    free(cpos);
    return OK;
}

Status InitList_L(LinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        return OVERFLOW;
    L->next = NULL;
    return OK;
}
LNode *Search_L(LinkList L, ElemType e)
{
    if (L == NULL)
        return NULL;
    LNode *p = L->next;
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}
LNode *NextElem_L(LNode *p)
{
    if (p == NULL)
        return NULL;
    return p->next;
}
LNode *MakeNode_L(ElemType e)
{
    LNode *p = (LNode *)malloc(sizeof(LNode));
    if (p == NULL)
        return NULL; //注意这里可以改，应该怎么改？思考一下逻辑
    p->data = e;
    p->next = NULL;
    return p;
}
Status InsertAfter_L(LNode *p, LNode *q)
{
    if (p == NULL || q == NULL)
        return ERROR;
    q->next = p->next;
    p->next = q;
    return OK;
}
Status DeleteAfter_L(LNode *p, ElemType &e)
{
    if (p == NULL || p->next == NULL)
        return ERROR; //空指针或者没有后继
    LNode *q;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}
Status CreatList_L(LinkList &L, int n, ElemType *A)
{
    LNode *p, *q;
    int i;
    InitList_L(L);
    for (i = 0, p = L; i < n; i++)
    {
        q = MakeNode_L(A[i]);
        p->next = q;
        p = q; //指向下一个结点
    }
    return OK;
}
void InverseList(LinkList &L)
{
    LNode *p, *q;
    //这里的逻辑可以改
    if (L != NULL || L->next != NULL)
    {
        p = L->next;
        L->next = NULL;
        while (p != NULL)
        {
            q = p->next;
            InsertAfter_L(L, p);
            p = q;
        }
    }
}
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
    LinkList pa, pb, pc, temp;
    pa = La->next;
    pb = Lb->next;
    Lc = pa = La;
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            temp = pa->next;
            InsertAfter_L(pc, pa);
            pc = pa;
            pa = temp;
        }
        else
        {
            temp = pb->next;
            InsertAfter_L(pc, pb);
            pc = pb;
            pb = temp;
        }
    }
    pc->next = (pa ? pa : pb);
    free(Lb);
}

Status InsertBefore_DuL(DuLinkList *p, DuLinkList *q)
{
    //在p之前插入q
    if (p == NULL || q == NULL || p->prior == NULL)
        return ERROR; //不能插入到头结点前
    q->prior = p->prior;
    q->next = p;
    q->prior->next = q;
    q->next->prior = q;
    return OK;
}
Status Delete_DuL(DuLNode *p, ElemType &e)
{
    if (p == NULL || p->prior == NULL)
        return ERROR;    //不能删除头结点
    if (p->next != NULL) //删除尾结点
        p->next->prior = p->prior;
    p->prior->next = p->next;
    e = p->data;
    free(p);
    return OK;
}

Status InitList_CL(CirLinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        return OVERFLOW;
    L->next = L; //注意循环链表的初始化
    return OK;
}
Status DeleteAfter_CL(CirLinkList L, LNode *p, ElemType &e)
{
    if (L->next == L)
        return ERROR; //注意空表的条件
    LNode *q;
    if (p->next == L)
        p = L; //循环的体现，指向头结点，删除首元结点
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}
void Split(CirLinkList &LO, CirLinkList &LC, CirLinkList &LL)
{
    char ch;
    CirLinkList po, pc, pl;
    po = LO->next;
    LC = LO; //借用头结点
    InitList_CL(LL);
    pc = LC;
    pl = LL;
    while (po != LO)
    {
        ch = po->data;
        if (ch >= 'A' && ch <= 'Z')
        {
            pc->next = po;
            pc = po;
        }
        else
        {
            pl->next = po;
            pl = po;
        }
        po = po->next;
    }
    pc->next = LC;
    pl->next = LL;
}
