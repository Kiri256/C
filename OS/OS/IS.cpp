#include "head.h"

extern node *menmory;
extern block *p;

bool allocate(block *ptemp)
{
    node *pr, *pt;
    pr = pt = menmory->next;

    while (pt != NULL)
    {
        if (pt->size >= ptemp->nsize)
            break;
        /*if (pt->state == false && pt->size >= ptemp->nsize)
        {
            if (pr->state == true)
                pr = pt;
            else if (pt->size < pr->size) // pr->state==false&&pr->size>pp->size，最佳适配
                pr = pt;
        }*/
        pt = pt->next;
    }
    pr=pt;
    if (pr == NULL || pr->state == true || pr->size < ptemp->nsize)
        return false;
    if (pr->size == ptemp->nsize)
    {
        pr->ID = ptemp->name[3];
        pr->state = true;
    }
    else
    {
        pt = (node *)malloc(sizeof(node));
        pt->ID = ptemp->name[3];
        pt->state = true;
        pt->size = ptemp->nsize;
        pt->address = pr->address;

        pr->size -= ptemp->nsize;
        pr->address = pr->address + ptemp->nsize;

        pr->prior->next = pt;
        pt->prior = pr->prior;
        pr->prior = pt;
        pt->next = pr;
    }
    return true;
}

void recycle(void)
{
    node *pt, *pr;
    pt = menmory->next;
    while (pt != NULL && pt->ID != p->name[3])
        pt = pt->next;
    if (pt == NULL)
        return;

    if (pt->prior->state == true && (pt->next == NULL || (pt->next != NULL && pt->next->state == true)))
    {
        pt->ID = 48;
        pt->state = false;
        return;
    }
    if (pt->prior->state == false)
    {
        pr = pt->prior;
        pr->prior->next = pt;
        pt->prior = pr->prior;

        pt->ID = 48;
        pt->state = false;
        pt->address = pr->address;
        pt->size += pr->size;
        free(pr);
    }
    if (pt->next != NULL)
    {
        pr = pt->next;
        pt->next = pr->next;
        if (pr->next != NULL)
            pr->next->prior = pt;

        pt->ID = 48;
        pt->state = false;
        pt->size += pr->size;
        free(pr);
    }
}
