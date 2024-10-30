#include "head3-4.h"

void InsesrtSort(RcdSqList &L)
{
    int i, j;
    for (i = 1; i < L.length; i++)
        if (L.rcd[i].key > L.rcd[i + 1].key)
        {
            L.rcd[0] = L.rcd[i + 1];
            j = i + 1;
            do
            {
                j--;
                L.rcd[j + 1] = L.rcd[j];
            } while (L.rcd[0].key < L.rcd[j - 1].key);
            L.rcd[j] = L.rcd[0];
        }
}
void ShellInsertSort(RcdSqList &L, int dk)
{
    int i, j;
    for (i = 1; i < L.length; i++)
        if (L.rcd[i].key > L.rcd[i + dk].key)
        {
            L.rcd[0] = L.rcd[i + dk];
            j = i + dk;
            do
            {
                j -= dk;
                L.rcd[j + dk] = L.rcd[j];
            } while (j - dk > 0 && L.rcd[0].key < L.rcd[j - dk].key); //可能跳跃过哨兵
            L.rcd[j] = L.rcd[0];
        }
}
void ShellSort(RcdSqList &L, int d[], int t)
{
    int k;
    for (k = 0; k < t; k++)
        ShellInsert(L, d[k]);
}
void bubbleSort(int a[], int n)
{
    int i, j, temp, change = 1;
    for (i = n - 1; i > 1 && change; i--)
    {
        change = 0;
        for (j = 0; j < i; j++)
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                change = 1;
            }
    }
}

void RadixPass(KeysRcdType rcd[], KeysRcdType rcd1[], int n,
               int i, int count[], int pos[], int radix)
{
    int k, j;
    for (k = 1; k <= n; k++)
        count[rcd[k].keys[i]]++;
    pos[0] = 1;
    for (j = 2; j < radix; j++)
        pos[j] = pos[j - 1] + count[j - 1];
    for (k = 1; k <= n; k++)
    {
        j = rcd[k].keys[i];
        rcd1[pos[j]++] = rcd[k];
    }
}
Status RadixSort(KeysSqList &L)
{
    KeysRcdType *rcd1;
    int i, j;
    int *count, *pos;
    count = (int *)malloc(L.radix * sizeof(int));
    pos = (int *)malloc(L.radix * sizeof(int));
    rcd1 = (KeysRcdType *)malloc((L.length + 1) * sizeof(KeysRcdType));
    if (count == NULL || pos == NULL || rcd1 == NULL)
        return OVERFLOW;
    i = 0;
    while (i < L.digitNum)
    {
        for (j = 0; j < L.radix; j++)
            count[j] = 0;
        if (i % 2 == 0)
            RadixPass(L.rcd, rcd1, L.length, i++, count, pos, L.radix);
        else
            RadixPass(rcd1, L.rcd, L.length, i++, count, pos, L.radix);
    }
    if (L.digitNum % 2 == 1)
        for (j = 1; j <= L.length; j++)
            L.rcd[j] = rcd1[j];
    free(count);
    free(pos);
    free(rcd1);
    return OK;
}

Status InitHash(HashTable &H, int size, int (*hash)(KeyType, int))
{
    int i;
    H.rcd = (Node **)malloc(size * sizeof(Node *));
    if (H.rcd == NULL)
        return OVERFLOW;
    for (i = 0; i < size; i++)
        H.rcd[i] = NULL;
    H.size = size;
    H.hash = hash;
    H.count = 0;
    return OK;
}
int hash(KeyType key, int hashsize)
{
    return (3 * key) % hashsize;
}
Node *SearchHash(HashTable H, int key)
{
    int p = hash(key, H.size);
    Node *np = H.rcd[p];
    while (np != NULL && np->r.key != key)
        np = np->next;
    return np;
}
Status InsertHash(HashTable &H, RcdType e)
{
    int p;
    Node *np;
    np = SearchHash(H, e.key);
    if (np == NULL)
    {
        p = H.hash(e.key, H.size);
        np = (Node *)malloc(sizeof(Node));
        if (np == NULL)
            return OVERFLOW;
        np->r = e;
        np->next = H.rcd[p];
        H.rcd[p] = np;
        H.count++;
        return OK;
    }
    return ERROR;
}

Status InitHash2(HashTable2 &H, int size, int (*hash)(KeyType, int),
                 void (*collision)(int &hashValue, int hashSize))
{
    int i;
    H.rcd = (RcdType *)malloc(size * sizeof(RcdType));
    H.tag = (int *)malloc(size * sizeof(int));
    if (H.rcd == NULL || H.tag == NULL)
        return OVERFLOW;
    H.size = size;
    H.count = 0;
    for (i = 0; i < size; i++)
        H.tag[i] = 0;
    H.hash = hash;
    H.collision = collision;
    return OK;
}
Status SearchHash2(HashTable2 H, KeyType key, int &p, int &c)
{
    p = H.hash(key, H.size);
    //开放定址哈希表没有真正意义上的删除，-1的元素要读并走过
    while ((H.tag[p] == 1 && H.rcd[p].key != key) || H.tag[p] == -1)
    {
        H.collision(p, H.size);
        c++;
    }
    //if(H.rcd[p].key==key&&H.tag[p]==1)return SUCCESS;
    if (H.tag[p] != 0)
        return SUCCESS;
    return UNSUCCESS; //tag=0,表示可以插入
}
void collision(int &hashValue, int hashSize)
{
    hashValue = (hashValue + 1) % hashSize; //这是线性探测。二次：+-（自然数）^2.
}
int InsertHash2(HashTable2 &H, RcdType e)
{
    int c = 0, p;
    if (SearchHash2(H, e.key, p, c) == SUCCESS)
        return -1; //元素已经存在不需要再插入
    else
    {
        H.rcd[p] = e;
        H.tag[p] = 1;
        H.count++;
    }
}
Status DeleteHash2(HashTable2 &H, KeyType key, RcdType &e)
{
    //删除key的记录
    int p, c = 0;
    if (SearchHash2(H, key, p, c) == UNSUCCESS)
        return UNSUCCESS;
    else
    {
        e = H.rcd[p];
        H.tag[p] = -1;
        H.count--;
        return SUCCESS;
    }
}