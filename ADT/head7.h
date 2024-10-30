#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef char TElemType;

typedef struct PTNode
{
    TElemType data;
    int parent;
} PTNode;
typedef struct
{
    PTNode *nodes;
    int r, nodeNum; //根位置和个数
} PTree;

typedef struct ChildNode
{
    int childIndex;
    struct ChildNode *nextChild;
} ChildNode;
typedef struct
{
    TElemType data;
    int parent;
    struct ChildNode *firstChild;
} PCTreeNode;
typedef struct
{
    PCTreeNode *nodes;
    int nodeNum, r;
} PCTree;

typedef struct CSTNode
{
    TElemType data;
    struct CSTNode *firstChild, *nextSibling;
} CSTNode, *CSTree, *CSForest;

CSTree MakeTree(TElemType e, int n, ...);
Status InsertChild(CSTree &T, int i, CSTree c);

Status InitTree(CSTree &T);
Status DestroyTree(CSTree &T);
int TreeDepth(CSTree T);
CSTNode *Search(CSTree T, TElemType e);
Status DEleteChild(CSTree &T, int i);

Status PreOrderTraverseForest(CSForest F,
                      Status(*visit)(TElemType));
int ForestDepth(CSForest F);
CSTNode *Search(CSForest F,TElemType e);

typedef struct{
    int *parent;
    int n;
}PForest,MFSet;

//构建n个单元素子集的并查集S
Status InitMFSet(MFSet &S,int n);

//销毁
Status DestroyMFSet(MFSet &S);

//查找元素i所属子集，返回代表元
int FindMFSet(MFSet &S,int i);

//判别i和j是否属于同一个子集
Status DiffMFSet(MFSet &S,int i,int j);

//合并i和j分别所属的子集
//将ri或rj合并到另一个去
Status UnionMFSet(MFSet &S,int i,int j);

//加权合并
Status UnionMFSet_WUR(MFSet &S,int i,int j);

//路径压缩
//将查找路径上的结点双亲都变成根节点（代表元）
//采用路径压缩的查找
int FindMFSet_PC(MFSet &S,int i);

//亲戚判定，并查集应用
Status hasRelationship(MFSet &S,int a,int b);

#define m 3
typedef int KeyType;
typedef struct BTNode{
    int keynum;
    KeyType key[m+1];
    struct BTNode  *parent;
    struct BTNode *ptr[m+1];
    //Record *recptr[m+1];
}BTNode,*BTree;

typedef struct{
    BTree pt;
    int i;
    int tag;
}result;

void SearchBTree(BTree t,int k,result &r);
int Search(BTree p,int k);

void InsertBTree(BTree &t,int k,BTree q,int i);
void split(BTree &q,int s,BTree &ap);
void newRoot(BTree &t,BTree p,int x,BTree ap);
void Insert(BTree &q,int i,int x,BTree ap);

void DeleteBTree(BTree &p,int i);

