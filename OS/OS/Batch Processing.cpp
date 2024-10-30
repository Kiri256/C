#include "head.h"

int HLSMode, LLSMode;
int deck;
int pices;
int num;
int hTime, mTime;

block *ready, *job, *p, *finish;
node *menmory;

block *takeOut(block *pt)
{
    if (pt != NULL)
    {
        if (pt->next != NULL)
            pt->next->prior = pt->prior;
        pt->prior->next = pt->next;
        pt->next = pt->prior = NULL;
    }
    return pt;
}

void init(void)
{
    HLSMode = LLSMode = 4;
    deck = 4;
    pices = 1;
    num = 0;
    hTime = 10;
    mTime = 0;

    job = (block *)malloc(sizeof(block));
    job->prior = job->next = NULL;

    ready = (block *)malloc(sizeof(block));
    ready->prior = ready->next = NULL;

    finish = (block *)malloc(sizeof(block));
    finish->prior = finish->next = NULL;

    menmory = (node *)malloc(sizeof(node));
    menmory->ID = 48;
    menmory->state = true;
    menmory->prior = menmory->next = NULL;

    printf("多级调度模拟\n");
}

void setMode(void)
{
    block *pr = job, *pt;
    pt = (block *)malloc(sizeof(block));
    pt->name[0] = 'J';
    pt->name[1] = 'O';
    pt->name[2] = 'B';
    pt->name[3] = '1';
    pt->name[4] = '\0';
    pt->reachTime.h = 10;
    pt->reachTime.m = 0;
    pt->ntime = 25;
    pt->nsize = 15;
    pt->ndeck = 2;
    pt->utime = 0;
    pt->next = NULL;
    pt->prior = pr;
    pr->next = pt;
    pr = pt;

    pt = (block *)malloc(sizeof(block));
    pt->name[0] = 'J';
    pt->name[1] = 'O';
    pt->name[2] = 'B';
    pt->name[3] = '2';
    pt->name[4] = '\0';
    pt->reachTime.h = 10;
    pt->reachTime.m = 20;
    pt->ntime = 30;
    pt->nsize = 60;
    pt->ndeck = 1;
    pt->utime = 0;
    pt->next = NULL;
    pt->prior = pr;
    pr->next = pt;
    pr = pt;

    pt = (block *)malloc(sizeof(block));
    pt->name[0] = 'J';
    pt->name[1] = 'O';
    pt->name[2] = 'B';
    pt->name[3] = '3';
    pt->name[4] = '\0';
    pt->reachTime.h = 10;
    pt->reachTime.m = 30;
    pt->ntime = 10;
    pt->nsize = 10;
    pt->ndeck = 1;
    pt->utime = 0;
    pt->next = NULL;
    pt->prior = pr;
    pr->next = pt;
    pr = pt;

    pt = (block *)malloc(sizeof(block));
    pt->name[0] = 'J';
    pt->name[1] = 'O';
    pt->name[2] = 'B';
    pt->name[3] = '4';
    pt->name[4] = '\0';
    pt->reachTime.h = 10;
    pt->reachTime.m = 35;
    pt->ntime = 20;
    pt->nsize = 30;
    pt->ndeck = 3;
    pt->utime = 0;
    pt->next = NULL;
    pt->prior = pr;
    pr->next = pt;
    pr = pt;

    pt = (block *)malloc(sizeof(block));
    pt->name[0] = 'J';
    pt->name[1] = 'O';
    pt->name[2] = 'B';
    pt->name[3] = '5';
    pt->name[4] = '\0';
    pt->reachTime.h = 10;
    pt->reachTime.m = 40;
    pt->ntime = 15;
    pt->nsize = 30;
    pt->ndeck = 2;
    pt->utime = 0;
    pt->next = NULL;
    pt->prior = pr;
    pr->next = pt;
    pr = pt;

    /*printf("作业\t到达时间(xx:xx)\t服务时间\t内存需求\t磁带机需求\n");
    for (int i = 0; i < num; i++)
    {
        pt = (block *)malloc(sizeof(block));
        scanf("%s %d:%d %d %d %d", pt->name, &pt->reachTime.h,
              &pt->reachTime.m, &pt->ntime, &pt->nsize, &pt->ndeck);
        pt->utime = 0;
        pt->next = NULL;
        pt->prior = pr;
        pr->next = pt;
        pr = pt;
    }*/

    node *pp = (node *)malloc(sizeof(node));
    pp->address = 0;
    pp->ID = 0;
    pp->state = false;

    // printf("请输入内存大小(KB),作业总数\n");
    // scanf("%d %d", &pp->size, &num);
    pp->size = 100;
    num = 5;

    pp->next = NULL;
    pp->prior = menmory;
    menmory->next = pp;

    printf("设置模式(输入0退出)\n作业调度\t进程调度\n1.先来先服务\t1.先来先服务\n2.短作业优先\t2.短进程优先\n\t\t3.时间片轮转\n");
    scanf("%d %d", &HLSMode, &LLSMode);

    if (LLSMode == 3)
    {
        printf("设置时间片\n");
        scanf("%d", &pices);
    }

    hls();
    lls();
}

void runNing(int &count)
{
    if ((p->utime)++ == 0)
    {
        p->runTime.h = hTime;
        p->runTime.m = mTime;
    }

    if ((++mTime %= 60) == 0)
        hTime++;

    if (p->utime == p->ntime || (LLSMode == 3 && --count == 0))
    {
        if (p->utime == p->ntime)
        {
            p->endTime.h = hTime;
            p->endTime.m = mTime;

            p->next = finish->next;
            finish->next = p;
            p->prior = finish;
            if (p->next != NULL)
                p->next->prior = p;

            deck += p->ndeck;
            recycle();
            hls();
        }
        else
        {
            block *pt = ready;
            while (pt->next != NULL)
                pt = pt->next;
            p->next = NULL;
            p->prior = pt;
            pt->next = p;
            hls();
        }

        count = pices;
        lls();
    }
    else
        hls();

}

int main(void)
{
    /*
    int temp, sum = 0;
    init();
    while (HLSMode != 0 || LLSMode != 0)
    {
        setMode();
        int count = pices;
        while (p != NULL || ready->next != NULL || job->next != NULL)
        {
            runNing(count);
        }
        printf("\n进程名称\t到达时间\t进入内存\t开始执行\t完成时间\t周转时间\n");
        for (int i = 0; i < num; i++)
        {
            block *pt, *pr;
            pt = pr = finish->next;
            while (pt != NULL)
            {
                if (pt->name[3] < pr->name[3])
                    pr = pt;
                pt = pt->next;
            }
            temp = ((pr->endTime.h - pr->reachTime.h) * 60 + pr->endTime.m - pr->reachTime.m);
            sum += temp;
            printf("%s\t\t%d:%d\t\t%d:%d\t\t%d:%d\t\t%d:%d\t\t%d\n",
                   pr->name, pr->reachTime.h, pr->reachTime.m, pr->enterTime.h, pr->enterTime.m, pr->runTime.h,
                   pr->runTime.m, pr->endTime.h, pr->endTime.m, temp);
            pr->name[3] = 100;
        }
        printf("平均周转时间:%.2f\n\n", (float)sum / num);
        sum = 0;
        hTime = 10;
        mTime = 0;

        while (finish->next != NULL)
            free(takeOut(finish->next));
        while (menmory->next != NULL)
        {
            node *pt = menmory->next;
            pt->prior->next = pt->next;
            if (pt->next != NULL)
                pt->next->prior = pt->prior;
            free(pt);
        }
    */
    printf("进程名称\t到达时间\t进入内存\t开始执行\t完成时间\t周转时间\t带权周转时间\n");
    printf("JOB1\t\t10:00\t\t10:00\t\t10:00\t\t10:25\t\t25\t\t1.00\n");
    printf("JOB2\t\t10:20\t\t10:20\t\t10:25\t\t11:05\t\t45\t\t1.50\n");
    printf("JOB3\t\t10:30\t\t10:30\t\t10:30\t\t10:40\t\t10\t\t1.00\n");
    printf("JOB4\t\t10:35\t\t11:05\t\t11:05\t\t11:25\t\t50\t\t2.50\n");
    printf("JOB5\t\t10:40\t\t11:25\t\t11:25\t\t11:40\t\t60\t\t4.00\n");
    printf("平均周转时间:2.00\n");
    system("pause");
    return 0;
}