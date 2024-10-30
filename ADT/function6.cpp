#include "head6.h"

Status is_DesenDant(SqBiTree T, int u, int v)
{
    //判断v是不是u的子孙
    if (u < 1 || u > T.lastIndex || v < 1 || v > T.lastIndex || v <= u)
        return FALSE;
    while (v > u && v != u)
        v /= 2;
    if (v == u)
        return TRUE;
    return FALSE;
}

BiTree MakeBiTree(TElemType e, BiTree L, BiTree R)
{
    //根结点值e，左右子树L和R
    BiTree t;
    t = (BiTree)malloc(sizeof(BiTNode));
    if (t == NULL)
        return NULL;
    t->data = e;
    t->lchild = L;
    t->rchild = R;
    return t;
}
Status ReplaceLeft(BiTree &T, BiTree &LT)
{
    //用LT替换左子树，并用LT返回原左子树
    BiTree temp;
    if (T == NULL)
        return ERROR;
    temp = T->lchild;
    T->lchild = LT;
    LT = temp;
    return OK;
}

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T == NULL)
        return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T->data);
    InOrderTraverse(T->rchild, visit);
    //按逻辑来说应该可以
    if (T == NULL)
        return OK;
    if (InOrderTraverse(T->lchild, visit) == ERROR)
        return ERROR;
    if (visit(T->data) == ERROR)
        return ERROR;
    return InOrderTraverse(T->rchild, visit);
}
BiTNode *GoFarLeft(BiTree T, LStack &S)
{
    if (T == NULL)
        return NULL;
    while (T->lchild != NULL)
    {
        //Push_LS(S, T);
        T = T->lchild;
    }
    return T;
}
void InOrderTraverse_I(BiTree T, Status (*visit)(TElemType e))
{
    LStack S;
    //InitStack_LS(S);
    BiTree p;
    p = GoFarLeft(T, S);
    while (p != NULL)
    {
        visit(p->data);
        if (p->rchild != NULL)
            p = GoFarLeft(p->rchild, S);
        else if (StackEmpty_LS(S) != TRUE);
            //Pop_LS(S, p);
        else
            p = NULL;
    }
}
Status PreOrderTraverse(TriTree T, Status (*visit)(TElemType e))
{
    TriTree p, pr;
    if (T != NULL)
    {
        p = T;
        while (p != NULL)
        {
            visit(p->data);
            if (p->lchild != NULL)
                p = p->lchild;
        }
    }
}
void LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T != NULL)
    {
        LQueue Q;
        InitQueue_LQ(Q);
        BiTree p = T;
        visit(p->data);
        EnQueue_LQ(Q, p);
        while (DeQueue_LQ(Q, p) == 1)
        {
            if (p->lchild != NULL)
            {
                visit(p->lchild->data);
                EnQueue_LQ(Q, p->lchild);
            }
            if (p->rchild != NULL)
            {
                visit(p->rchild->data);
                EnQueue_LQ(Q, p->rchild);
            }
        }
    }
}

void DestroyBiTree(BiTree &T)
{
    //后序遍历
    if (T != NULL)
    {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
    }
}
int BiTreeDepth(BiTree T)
{
    //后序
    int depthLeft, depthRight;
    if (T == NULL)
        return 0;
    else
    {
        depthLeft = BiTreeDepth(T->lchild);
        depthRight = BiTreeDepth(T->rchild);
        return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
}
void CountLeaf(BiTree T, int &count)
{
    //先序
    if (T != NULL)
    {
        if (T->lchild == NULL && T->rchild == NULL)
            count++;
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}
BiTree CreatBiTree(char *defBT, int &i)
{
    //先序
    BiTree T;
    TElemType ch;
    ch = defBT[i++];
    if (ch == '#')
        InitBiTree(T);
    else
    {
        T = MakeBiTree(ch, NULL, NULL);
        T->lchild = CreateBiTree(defBT, i);
        T->rchild = CreateBiTree(defBT, i);
    }
    return T;
}

Status SwapHeapElem(Heap &H, int i, int j)
{
    //交换i和j结点
    RcdType t;
    if (i < 0 || i > H.n || j < 0 || j > H.n)
        return ERROR;
    t = H.rcd[i];
    H.rcd[i] = H.rcd[j];
    H.rcd[j] = t;
    return OK;
}
void shiftDown(Heap &H, int pos)
{
    //自上而下调整
    int c, rc;
    while (pos <= H.n / 2)
    {
        //求出左右结点
        c = pos * 2;
        rc = c + 1;

        //找出两结点中的优势结点
        if (rc <= H.n && H.prior(H.rcd[rc].key, H.rcd[c].key))
            c = rc;

        //和父母比较是否符合优势规则符合就退出
        if (H.prior(H.rcd[pos].key, H.rcd[c].key))
            return;

        SwapHeapElem(H, pos, c);

        //向下循环
        pos = c;
    }
}
Status InsertHeap(Heap &H, RcdType e)
{
    int curr;
    if (H.n >= H.size - 1) //size包含了0号元素
        return ERROR;
    curr = ++H.n;
    H.rcd[curr] = e;

    //以根为界，并且要不满足父母优势
    while (curr != 1 && H.prior(H.rcd[curr].key, H.rcd[curr / 2].key))
    {
        SwapHeapElem(H, curr, curr / 2);
        curr /= 2;
    }
}
Status RemoveFirstHeap(Heap &H, RcdType &e)
{
    //删除堆顶元素
    if (H.n <= 0)
        return ERROR;
    //用e返回
    e = H.rcd[1];
    SwapHeapElem(H, 1, H.n);
    H.n--;
    //自减应该要在筛选之前，还可以加一个判断
    if (H.n > 1)
        ShiftDown(H, 1);
    return OK;
}
void MakeHeap(Heap &H, RcdType *E, int n, int size, int tag, int (*prior)(KeyType, KeyType))
{
    //对n/2,n/2-1...1为子树根依次筛选建堆
    //用已有E建堆
    int i;
    H.rcd = E;
    H.n = n;
    H.size = size;
    H.tag = tag;
    H.prior = prior;
    for (i = n / 2; i >= 1; i--)
        ShiftDown(H, i);
}
void HeapSort(RcdSqList &L)
{
    Heap H;
    int i;
    RcdType e;
    MakeHeap(H, L.rcd, L.length, L.size, 1, greatPrior);

    for (i = H.n; i > 0; i--)
    {
        RemoveFirstHeap(H, e);
        printf("%d  ", e.key);
    }

    //这个应该也行
    while (H.n > 0)
    {
        RemoveFirstHeap(H, e);
        printf("%d  ", e.key);
    }
}

BSTree SearchBST(BSTree T, KeyType key)
{
    if (T == NULL)
        return NULL;
    if (T->data.key == key)
        return T;
    if (T->data.key > key)
        return SearchBST(T->lchild, key);
    return SearchBST(T->rchild, key);
}
BSTree SearchBST_I(BSTree T, KeyType key)
{
    while (T != NULL)
    {
        if (T->data.key == key)
            return T;
        else if (T->data.key > key)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return NULL;
}
Status InsertBST(BSTree &T, RcdType e)
{
    //查找失败时插入
    if (T == NULL)
    {
        BSTNode *s;
        s = (BSTNode *)malloc(sizeof(BSTNode));
        if (s == NULL)
            return OVERFLOW;
        s->data = e;
        s->lchild = s->rchild = NULL;
        T = s;
        return TRUE;
    }
    if (e.key < T->data.key)
        return InsertBST(T->lchild, e);
    if (e.key > T->data.key)
        return InsertBST(T->rchild, e);
    //查找成功时退出
    return FALSE;
}
Status DeleteBST(BSTree &T, KeyType key)
{
    if (T == NULL)
        return FALSE;
    if (T->data.key == key)
    {
        //删除操作是调用函数
        DeleteNode(T);
        return TRUE;
    }
    else if (T->data.key > key)
        return DeleteBST(T->lchild, key);
    return DeleteBST(T->rchild, key);
}
void DeleteNode(BSTree &p)
{
    BSTNode *q, *s;
    q = p;

    //处理右子树为空和无子
    if (p->rchild == NULL)
    {
        //注意这句，p是父母结点的域
        p = p->lchild;
        free(q);
    }

    //处理左子树为空
    else if (p->lchild == NULL)
    {
        //同理
        p = p->rchild;
        free(q);
    }

    //处理皆非空，注意这里引用变量p几乎没用了
    else
    {
        //指向左子树
        s = p->lchild;

        //向右找到尽头的直接前驱s
        while (s->rchild != NULL)
        {
            q = s;
            s = s->rchild;
        } 
        p->data = s->data;

        if (q == p)

            //没进循环，s是左子树的根，删除左单子。
            q->lchild = s->lchild;
        else
        
            //删除右单子
            q->rchild = s->lchild;
        free(s);
    }
}

//L-L型，左孩子的左子树上插入，右旋
//R-R型，左旋
//L-R型，左子树先做左旋，失衡子树再右旋
//R-L型，
void R_Rotate(BBSTree &p)
{
    //对最小失衡子树p调整
    //以左孩子为轴，顺时针旋转
    BBSTree lc = p->lchild; //获取左孩子
    p->lchild = lc->rchild; //继承左孩子的右子树
    lc->rchild = p;         //成为左孩子的右子树？
    p = lc;                 //换回位置
}
void L_Rotate(BBSTree &p)
{
    BBSTree lc = p->rchild;
    p->rchild = lc->lchild;
    lc->lchild = p;
    p = lc;
}

void RightBalence(BBSTree &T){

}
void LeftBalance(BBSTree &T)
{
    BBSTree lc, rd;
    lc = T->lchild;
    switch (lc->bf)
    {
    case LH:
        T->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case RH:
        rd = lc->rchild;
        switch (rd->bf)
        {
        case LH:
            T->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            T->bf = lc->bf = EH;
            break;
        case RH:
            T->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
        L_Rotate(T->lchild);
        R_Rotate(T);
        break;
    }
}
Status InsertAVL(BBSTree &T, RcdType e, Status &taller)
{
    if (T == NULL)
    {
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = T->rchild = NULL;
        taller = TRUE;
    }
    else if (T->data.key == e.key)
    {
        taller = FALSE;
        return FALSE;
    }
    else if (T->data.key > e.key)
    {
        if (InsertAVL(T->lchild, e, taller) == FALSE)
            return FALSE;
        if (taller == TRUE)
        {
            switch (T->bf)
            {
            case LH:
                LeftBalance(T);
                taller = FALSE;
                break;
            case EH:
                T->bf = LH;
                taller = TRUE;
                break;
            case RH:
                T->bf = EH;
                taller = FALSE;
                break;
            }
        }
    }
    else
    {
        if (InsertAVL(T->rchild, e, taller) == FALSE)
            return FALSE;
        if (taller == TRUE)
        {
            switch (T->bf)
            {
            case LH:
                T->bf = EH;
                taller = FALSE;
                break;
            case EH:
                T->bf = RH;
                taller = TRUE;
                break;
            case RH:
                RightBalance(T);
                taller = FALSE;
                break;
            }
        }
    }
    return TRUE;
}