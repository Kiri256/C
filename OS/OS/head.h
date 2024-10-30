#include <stdio.h>
#include <stdlib.h>

struct time
{
    int h;
    int m;
};

struct block
{
    char name[5];
    time reachTime;
    time enterTime;
    time runTime;
    time endTime;
    int utime;
    int ntime;
    int nsize;
    int ndeck;
    struct block *prior, *next;
};

struct node
{
    char ID;
    bool state;
    int address;
    int size;
    node *prior, *next;
};

block *takeOut(block *pt);

void hls(void);

void lls(void);

bool allocate(block *ptemp);
void recycle(void);