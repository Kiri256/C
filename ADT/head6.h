#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;
typedef char TElemType;
typedef int KeyType;

typedef struct
{
    TElemType *elem;
    int lastIndex;
} SqBiTree;
Status is_DesenDant(SqBiTree T, int u, int v);

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R);
Status ReplaceLeft(BiTree &T, BiTree &LT);

void InitBiTree(BiTree &T);//创建一棵空树
void DestroyBiTree(BiTree &T);
Status BiTreeEmpty(BiTree T);//判断是是否为空树
Status BreakBiTree(BiTree &T, BiTree &L, BiTree &R);//分成三部分
Status RepalceRight(BiTree &L, BiTree &RT);

typedef struct TriTNode
{
    TElemType data;
    TriTNode *parent, *lchild, *rchild;
} TriTNode, *TriTree;

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
typedef struct LNode
{
    BiTree data;
    LNode *next;
} LSNode,* LStack;
Status Push_LS(LStack &S, BiTree e);
Status Pop_LS(LStack &S, BiTree e);
Status InitStack_LS(LStack &S);
Status StackEmpty_LS(LStack S);
BiTNode *GoFarLeft(BiTree T, LStack &S);
void InOrderTraverse_I(BiTree T, Status (*visit)(TElemType e));

typedef struct LQNode
{
    BiTree data;
    LQNode *next;
} LQNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LQueue;
void InitQueue_LQ(LQueue &Q);
Status EnQueue_LQ(LQueue &Q, BiTree e);
Status DeQueue_LQ(LQueue &Q, BiTree &e);

BiTNode *GoFarLeft(BiTree T, LStack &S);
void InOrderTraverse_I(BiTree T, Status (*visit)(TElemType e));
Status PreOrderTraverse(TriTree T, Status (*visit)(TElemType e));
void LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));

void DestroyBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
void CountLeaf(BiTree T, int &count);
BiTree CreateBiTree(char *defBT, int &i);

typedef struct
{
    KeyType key;
    ;
} RecordType, RcdType;
typedef struct
{
    RcdType *rcd;
    int n;
    int size;
    int tag;
    int (*prior)(KeyType, KeyType);
} Heap;
int greatPrior(int x, int y) { return x >= y; }
int lessPrior(int x, int y) { return x <= y; }
Status SwapHeapElem(Heap &H,int i,int j);
void ShiftDown(Heap &H, int pos);
Status InSertHeap(Heap &H, RcdType e);
Status RemoceFirstHeap(Heap &H, RcdType &e);
void MakeHaep(Heap &H, RcdType *E, int n, int size, int tag, int (*prior)(KeyType, KeyType));

Status InitHeap(Heap &H, int size, int (*prior)(KeyType, KeyType));
Status DestroyHeap(Heap &H);
Status RemoveHeap(Heap &H, int pos, RcdType &e0);

typedef struct{
    RcdType *rcd;
    int length;
    int size;
}RcdSqList;
void HeapSort(RcdSqList &L);

typedef struct BSTNode{
    RcdType data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
BSTree SearchBST(BSTree T,KeyType key);
BSTree SearchBST_I(BSTree T,KeyType key);
Status InsertBST(BSTree &T,RcdType e);
Status DeleteBST(BSTree &T,KeyType key);
void DeleteNode(BSTree &p);

Status InitBST(BSTree &T);
Status DestroyBST(BSTree &T);

typedef struct BBSTNode{
    RcdType data;
    int bf;//结点平衡因子，高度差。
    struct BBSTNode *lchild,*rchild;
}*BBSTree;
void R_Rotate(BBSTNode &p);
void L_Rotate(BBSTNode &p);
#define LH +1
#define EH 0
#define RH -1
void LeftBalance(BBSTree &T);
void RightBalance(BBSTree &T);
Status InsertAVL(BBSTree &T,RcdType e,Status &taller);