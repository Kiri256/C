#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OK 1
#define ERROR 0
typedef int Status;
typedef int KeyType;

typedef struct
{
    KeyType key;
    ;
} RecordType, RcdType;
typedef struct
{
    RcdType *rcd;
    int length;
    int size;
} RcdSqList;

int BinSearch(RcdType rcd[], KeyType key, int low, int high);
int BinSearch_ite(RcdType rcd[], KeyType key, int low, int high);

void Merge(RcdType SR[], RcdType TR[], int i, int m, int n);
void MSort(RcdType R1[], RcdType R2[], int i, int s, int t);
void MSort_ite(RcdType R1[], RcdType R2[], int n);
void MergeSort(RcdSqList &L);

int Partition(RcdType rcd[], int low, int high);
void QSort(RcdType rcd[], int s, int t);
void QuickSort(RcdSqList &L);

typedef char AtomType;
typedef enum
{
    ATOM,
    LIST
} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct
        {
            GLNode *hp;
            GLNode *tp;
        } ptr;//注意这个ptr
    } un;
} GLNode, *GList;
int GListDepth(GList L);
Status Append(GList &L, GLNode *p);

GLNode *MakeAtom(AtomType e);
void InitGList(GList &L);
Status  DestroyGList(GList &L);
GLNode *GetHead(GList L);
GList GetTail(GList L);//求表尾
Status InsertHead(GList &L,GLNode *p);
Status DeleteHead(GList &L,GList *p);
GList CopyGList(GList L);
int GListLength(GList L);