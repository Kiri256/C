#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define UNSUCCESS 0
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
void InsertSort(RcdSqList &L);
void ShellInsert(RcdSqList &L, int dk);
void ShellSort(RcdSqList &L, int d[], int t);
void BubbleSort(RcdSqList &L);
void bubbleSort(RcdSqList &L);

typedef struct
{
    KeyType *keys;
    ;
} KeysRcdType;
typedef struct
{
    KeysRcdType *rcd;//零元不用
    int length;
    int size;
    int digitNum;
    int radix;
} KeysSqList;
void RadixPass(KeysRcdType rcd[], KeysRcdType rcd1[],
               int n, int i, int count[], int pos[], int radix);
Status RadixSort(KeysSqList &L);

typedef struct Node
{
    RcdType r;
    struct Node *next;
} Node;
typedef struct
{
    Node **rcd;
    int size;
    int count;
    int (*hash)(KeyType key, int hashsize);
} HashTable;
Status InitHash(HashTable &H, int size, int (*hash)(KeyType, int));
int hash(KeyType key, int hashsize);
Node *SearchHash(HashTable H, int key);
Status InsertHash(HashTable &H, RcdType e);
Status DestroyHash(HashTable &H);
Status DeleteHash(HashTable &H, KeyType key, RcdType &e);

typedef struct
{
    RcdType *rcd;
    int size;
    int count;
    int *tag;               //开放定址哈希表没有真正的删除
    int (*hash)(KeyType key, int hashSize);
    void (*collision)(int &hashValue, int hashSize);
} HashTable2;
Status InitHash2(HashTable2 &H, int size, int (*hash)(KeyType, int), void (*collision)(int &, int));
Status SearchHash2(HashTable2 H, KeyType key, int &p, int &c);
void collision(int &hashValue, int hashSize);
int InsertHash2(HashTable2 &H, RcdType e);
Status DeleteHash2(HashTable2 &H, KeyType key, RcdType &e);
Status DestroyHash2(HashTable2 &H);
Status CreatHash2(HashTable &H);
