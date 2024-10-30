#include "head.h"

extern int num, hTime, mTime, deck, HLSMode;
extern block *job, *ready, *p;
extern node *menmory;

block *sjf(void)
{
    int i = 0;
    block *pr, *pt = job->next;

    while (pt != NULL)
    {
        i++;
        pt = pt->next;
    }

    while (i-- > 0)
    {
        pr = pt = job->next;
        while (pt != NULL &&
               (pt->reachTime.h < hTime || (pt->reachTime.h == hTime && pt->reachTime.m <= mTime)))
        {
            if (pr->utime == 1 || (pt->ntime < pr->ntime && pt->utime == 0))
                pr = pt;
            pt = pt->next;
        }
        if (pr == NULL)
            break;
        if (pr->utime == 0 &&
            (pr->reachTime.h < hTime || (pr->reachTime.h == hTime && pr->reachTime.m <= mTime)) &&
            pr->ndeck <= deck && allocate(pr))
        {
            deck -= pr->ndeck;

            pt = job->next;
            while (pt != NULL)
            {
                pt->utime = 0;
                pt = pt->next;
            }
            return takeOut(pr);
        }
        else
            pr->utime = 1;
    }
    pt = job->next;
    while (pt != NULL)
    {
        pt->utime = 0;
        pt = pt->next;
    }
    return NULL;
}

block *fcfsj(void)
{
    block *pr;
    for (pr = job->next; pr != NULL; pr = pr->next)
    {
        if (pr->reachTime.h < hTime ||
            (pr->reachTime.h == hTime && pr->reachTime.m <= mTime))
        {
            if (pr->ndeck <= deck && allocate(pr))
            {
                deck -= pr->ndeck;
                break;
            }
        }
    }
    return takeOut(pr);
}

void hls(void)
{
    if (job->next == NULL)
        return;
    block *pt, *pr;
    if (HLSMode == 1)
        pr = fcfsj();
    else if (HLSMode == 2)
        pr = sjf();
    else
        ;
    if (pr == NULL)
        return;
    pr->enterTime.h = hTime;
    pr->enterTime.m = mTime;
    if (p != NULL && pr != NULL && pr->ntime < p->ntime)
    {
        block *pt;
        for (pt = ready; pt->next != NULL; pt = pt->next)
            ;
        p->next = NULL;
        p->prior = pt;
        pt->next = p;

        p = pr;
    }
    else
    {
        for (pt = ready; pt->next != NULL; pt = pt->next)
            ;
        pr->prior = pt;
        pt->next = pr;
    }
    int i = 1;
    printf("被选中作业：%s\n内存状态：\n分区号\t分区始址\t分区大小\t分区状态\n", pr->name);
    for (node *pt = menmory->next; pt != NULL; pt = pt->next)
        if (pt->state == false)
            printf("%d\t%d\t\t%d\t\t空闲\n", i++, pt->address, pt->size);
    printf("磁带机剩余：%d\n", deck);
}