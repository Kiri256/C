#include "head.h"

extern block *ready, *p;
extern int LLSMode;

block *spf(void)
{
    block *pt, *pr;
    pr = ready->next;
    pt = pr->next;
    while (pt != NULL)
    {
        if (pt->ntime < pr->ntime)
            pr = pt;
        pt = pt->next;
    }

    return takeOut(pr);
}

block *fcfsp(void)
{
    return takeOut(ready->next);
}

void lls(void)
{
    if (ready->next == NULL)
    {
        p = NULL;
        return;
    }
    if (LLSMode == 1 || LLSMode == 3)
        p = fcfsp();
    else if (LLSMode == 2)
        p = spf();
}