#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define SUCCESS 1
#define UNSUCCESS 0
#define OVERFLOW -1
typedef int Status;
typedef int ElemType;
//typedef char ElemType;

typedef struct
{
    ElemType *elem;
    int top;
    int size;
    int inc;
} SqStack;
Status InitStack_Sq(SqStack &S, int size, int inc);
Status Push_Sq(SqStack &S, ElemType e);
Status Pop_Sq(SqStack &S, ElemType &e);

Status StackEmpty_Sq(SqStack S);
Status GetTop_Sq(SqStack S, ElemType &e);
void ClearStack_Sq(SqStack &S);

typedef struct LNode
{
    ElemType data;
    LNode *next;
} LSNode, *LStack;

Status Push_LS(LStack &S, ElemType e);
Status Pop_LS(LStack &S, ElemType &e);

void InitStack_LS(LStack &S);
void DestroyStack_LS(LStack &S);
Status StackEmpty_LS(LStack S);
Status GetTop_LS(LStack S, ElemType &e);

typedef struct
{
    ElemType *elem;
    int size;
    int front;
    int rear;
} SqQueue;
Status InitQueue_Sq(SqQueue &Q, int size);
Status DeQeueu_Sq(SqQueue &Q, ElemType &e);
Status EnQueue_Sq(SqQueue &Q, ElemType e);

Status DestroyQueue_Sq(SqQueue &Q);
void ClearQueue_Sq(SqQueue &Q);
Status QueueEmpty_Sq(SqQueue Q);
int QeueuLength_Sq(SqQueue Q);
Status GetHead_Sq(SqQueue &Q, ElemType &e);

typedef struct LQNode
{
    ElemType data;
    struct LQNode *next;
} LQNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LQueue;
Status EnQueue_LQ(LQueue &Q, ElemType e);
Status DeQueue_LQ(LQueue &Q, ElemType &e);

void InitQueue_LQ(LQueue &Q);
void DestroyQueue_LQ(LQueue &Q);
Status QueueEmpty_LQ(LQueue Q);
int QueueLength_LQ(LQueue Q);
Status GetHead_LQ(LQueue Q, ElemType &e);

typedef struct
{
    ElemType *elem;
    int length;
    int size;
    int inc;
} SqList;
Status DeleteLast_Sq(SqList &L, ElemType &e);
int Search_Sq(SqList L, ElemType e);
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc);

Status InitList_Sq(SqList &L, int size, int inc);
Status ClearList_Sq(SqList &L);
Status ListEmpty_Sq(SqList L);
int ListLength_Sq(SqList L);
Status GetElem_Sq(SqList L, int i, ElemType &e);
Status ListTraverse_Sq(SqList L, Status (*visit)(ElemType e));
Status PutElem_Sq(SqList &L, int i, ElemType e);
Status Append_Sq(SqList &L, ElemType e);

typedef struct
{
    float coef; //系数
    int expn;   //指数
} Term;
typedef struct
{
    Term *elem;
    int length;
} Poly; //一元稀疏多项式

Status CreatePoly(Poly &P, Term e[], int n);
Status AddPoly(Poly pa, Poly pb, Poly &pc);

Status DestroyPoly(Poly &P);
Status PrintPoly(Poly P);
int PolyLength(Poly P);
void SubPoly(Poly pa, Poly pb, Poly &pc);
void MulPoly(Poly pa, Poly pb, Poly &pc);
void DivPoly(Poly pa, Poly pb, Poly &pc);

typedef struct
{
    int i, j;
    ElemType e;
} Triple; //三元组
typedef struct
{
    Triple *data;   //0元不用
    int mu, nu, tu; //行数，列数，非零元
} TSMatrix;
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);

Status CreateSMatrix(TSMatrix &M);
Status DestroySMatrix(TSMatrix &M);
void PrintSMatrix(TSMatrix M);
Status CopySMatrix(TSMatrix M, TSMatrix &T);
Status SubSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);
Status MulSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);
Status TransposeSMatrix(TSMatrix M, TSMatrix &Q);

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
Status InitList_L(LinkList &L);
LNode *Search_L(LinkList L, ElemType e);
LNode *NextElem_L(LNode *p);
LNode *MakeNode_L(ElemType e);
Status InsertAfter_L(LNode *p, LNode *q); //b结点之后插入q结点
Status DeleteAfter_L(LNode *p, ElemType &e);
Status CreatList_L(LinkList &L, int n, ElemType *A);
void InverseList(LinkList &L);
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc);

Status DestroyList_L(LinkList &L);
Status ClearList_L(LinkList &L);
Status ListEmpty(LinkList L);
int ListLength_L(LinkList L);
void ListTraverse_L(LinkList L, Status (*visit)(ElemType e));

typedef struct DuLNode
{
    ElemType data;
    struct DuLNode *prior, *next;
} DuLNode, DuLinkList;
Status InSertBefore_DuL(DuLNode *p, DuLNode *q);
Status Delete_DuL(DuLNode *p, ElemType &e);

Status InitList_DuL(DuLinkList &L);
Status DestroyList_DuL(DuLinkList &L);
Status ClearList_DuL(DuLinkList &L);
Status ListEmpty_DuL(DuLinkList L);
int ListLength_DuL(DuLinkList L);
DuLNode *Search_DuL(DuLNode *p);
DuLNode *PriorElem_DuL(DuLNode *p);
DuLNode *NextElem_DuL(DuLNode *p);
DuLNode *MakeNode_DuL(ElemType e);
Status InsertAfter_DuL(DuLNode *p, DuLNode *q);
void ListTraverse_DuL(DuLinkList L, Status (*visit)(ElemType e));

typedef LinkList CirLinkList;
Status InitList_CL(CirLinkList &L);
Status DeleteAfter_CL(CirLinkList &L, LNode *p, ElemType &e);
void Split(CirLinkList &LO, CirLinkList &LC, CirLinkList &LL);

typedef DuLinkList DuCirLinkList;
