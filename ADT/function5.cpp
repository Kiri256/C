#include "head5.h"

int BinSearch(RcdType rcd[], KeyType key, int low, int high)
{
    int mid = (low + high) / 2;
    if (low > high)
        return -1;
    if (rcd[mid].key == key)
        return mid;
    if (rcd[mid].key > key)
        return BinSearch(rcd, key, low, mid - 1);
    else
        return BinSearch(rcd, key, mid + 1, high);
}
int BinSearch_ite(RcdType rcd[], KeyType key, int low, int high)
{
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (rcd[mid].key > key)
            high = mid - 1;
        else if (rcd[mid].key == key)
            return mid;
        else
            low = mid + 1;
    }
    return -1;
}

void Merge(RcdType SR[], RcdType TR[], int i, int m, int n)
{
    //SR中i到m，m+1到n归并到TR，0元不用
    int k, j;
    for (j = m + 1, k = i; i <= m && j < n; k++)
    {
        if (SR[i].key <= SR[j].key)
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    while (i <= m)
        TR[k++] = SR[i++];
    while (j <= n)
        TR[k++] = SR[j++];
}
void MSort(RcdType R1[], RcdType R2[], int i, int s, int t)
{
    int m;
    if (s == t) //分解到单个
    {
        if (i % 2 == 1) //奇数层复制到R2，返回偶数层归并，处理奇数次递归。
            R2[s] = R1[s];
    }
    else
    {
        m = (s + t) / 2;
        MSort(R1, R2, i + 1, s, m);
        MSort(R1, R2, i + 1, m + 1, t);
        //划分
        if (i % 2 == 1)
            Merge(R1, R2, s, m, t);
        else
            Merge(R2, R1, s, m, t);
        //归并
    }
}
void MSort_ite(RcdType R1[], RcdType R2[], int n)
{
    //对R1归并，R2辅助
    int d, i, j, jk, k, m;
    //递归层数d，当前区间长度k，区间左边界j，右边界jk，区间中点m，循环辅助变量i
    d = ceil(log(n) / log(2));
    if (d % 2 == 1)
        //处理奇数次归并
        for (i = 1; i <= n; i++)
            R2[i] = R1[i];
    for (k = 2; d > 0; k *= 2, d--)
        //从小归并到大,条件变量是d
        for (j = 1; j <= n; j += k)
        {
            //内循环对每一个区间归并，划分和归并处于同一层
            m = j + (k - 1) / 2;
            //m=(j+j+(k-1))/2,长度包括自身要减一。
            if (m > n)
                //处理中点已超长度
                m = n;
            jk = j + k - 1;
            if (jk > n)
                //处理右边界已超长度
                jk = n;
            if (d & 2 == 1)
                //奇数层从R2归并到R1
                Merge(R2, R1, j, m, jk);
            else
                Merge(R1, R2, j, m, jk);
        }
}
void MergeSort(RcdSqList &L)
{
    RcdType *R;
    R = (RcdType *)malloc((L.length + 1) * sizeof(RcdType));
    if (R != NULL)
        MSort(L.rcd, R, 0, 1, L.length);
    //MSort_ite(L.rcd,R,0,L.length);
    free(R);
}

int Partition(RcdType rcd[], int low, int high)
{
    //对rcd[low..high]做一次划分，返回枢纽
    rcd[0] = rcd[low];
    while (low < high)
    {
        while (low < high && rcd[high].key >= rcd[0].key)
            //从后面找到比枢纽小的
            high--;
        rcd[low] = rcd[high];
        while (low < high && rcd[low].key <= rcd[0].key)
            //找到比枢纽大的
            low++;
        rcd[high] = rcd[low];
    }
    rcd[low] = rcd[0];
    return low;
}
void QSort(RcdType rcd[], int s, int t)
{
    int pivotloc;
    if (s < t)
    {
        pivotloc = Partition(rcd, s, t);
        QSort(rcd, s, pivotloc - 1); //枢纽已经排好，不用动了
        QSort(rcd, pivotloc + 1, t);
    }
}
void QuickSort(RcdSqList &L)
{
    QSort(L.rcd, 1, L.length);
}

//"把切分好的区间压入自定义的栈里，然后遍历这个栈"

//迭代快排？
//使用栈来储存每次划分的边界，但真的有必要用栈吗？有必要后进先出吗
//感觉逻辑很乱
/*"非递归的版本反而慢一些，
猜测可能是函数参数出入栈已经被解释器优化的很好了，
c++的版本显示,只有当数组非常大，
比如1e6以上的时候，非递归的优势才更明显，
但是在python里，这时早已到达最大递归深度了。。。"*/
struct LStack
{
    KeyType low;
    KeyType high;
    LStack *next;
};
void QSort_ite(RcdType rcd[], int s, int t)
{
    int pivotloc;
    LStack *S, *p;

    //初始化，把第一个low和high也看作栈元素解决循环的问题
    S = NULL;
    p = (LStack *)malloc(sizeof(LStack));
    p->low = s;
    p->high = t;
    p->next = S;
    S = p;

    while (S != NULL)
    {
        //出栈
        p = S;
        s = p->low;
        t = p->high;
        S = S->next;
        free(p);
        
        while (s < t)
        {
            pivotloc = Partition(rcd, s, t);
            //入栈前判断有必要进吗
            if (pivotloc < t - 1)
            {
                p = (LStack *)malloc(sizeof(LStack));
                p->low = pivotloc + 1;
                p->high = t;
                p->next = S;
                S = p;
            }
            if (pivotloc > s + 1)
            {
                p = (LStack *)malloc(sizeof(LStack));
                p->low = s;
                p->high = pivotloc - 1;
                p->next = S;
                S = p;
            }
        }
    }
}

int GListDepth(GList L)
{
    int h1, h2;
    if (L == NULL)
        return 1;
    if (L->tag == ATOM)
        return 0;
    h1 = GListDepth(L->un.ptr.hp);
    h2 = GListDepth(L->un.ptr.tp) + 1;
    return h1 > h2 ? h1 : h2;
}
//表尾添加表结点，然后把p赋值给hp
Status Append(GList &L, GLNode *p)
{
    GLNode *pp, *tail;
    tail = (GLNode *)malloc(sizeof(GLNode));
    if (tail == NULL)
        return -1;
    tail->tag = LIST;
    tail->un.ptr.hp = p;
    tail->un.ptr.tp = NULL;
    if (L == NULL)
        L = tail;
    else
    {
        for (pp = L; pp->un.ptr.tp != NULL; pp = pp->un.ptr.tp)
            ;
        pp->un.ptr.tp = tail;
    }
    return OK;
}
