
#include "declare.h"
void print(stu_t *p)
{
    stu_t *q = p;
    FILE *fpl1 = fopen("dong.txt","r");
    int i=1;
    printf("seq ID     Name           Chinese  Math    Average\n");
    printf("-------------------------------------------------\n");
    if(fgetc(fpl1) == EOF)
        printf("          The file is empty!!!!!\n");
    while(q != NULL)
    {
        printf(" %d: %-7d%-16s%-8.1f%-8.1f%-8.1f\n",i,q->id, q->name ,q->chi, q->math, q->average);
        q = q->next;
        i++;
    }
    printf("-------------------------------------------------\n");
}
