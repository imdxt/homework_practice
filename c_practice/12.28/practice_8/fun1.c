
#include "declare.h"
stu_t * create(stu_t *p, int id, char *name, float chi, float math)
{
    p -> next = (stu_t *)malloc(sizeof(stu_t));
    p = p -> next;
    p -> next = NULL;
    p -> id = id;
    strcpy(p -> name, name);
    p -> chi = chi;
    p -> math = math;
    p -> average = (chi + math)/2;

    return  p;
}
int init(stu_t *head)
{
    int i=0;
    stu_t *p=head;
    while(p != NULL)
    {
        i = p->id;
        p = p->next;
    }
    return i;
}
stu_t *head_1(FILE *fpl1)
{
    stu_t tmp;
    if(fgetc(fpl1) == EOF){
        fseek(fpl1, 0L, SEEK_SET);
        return NULL;
    }
    fseek(fpl1, 0L, SEEK_SET);

    fscanf(fpl1, "%d%s%f%f%f", &tmp.id, tmp.name, &tmp.chi, &tmp.math, &tmp.average);
    stu_t *p,*head = (stu_t *)malloc(sizeof(stu_t));
    head -> id = tmp.id;
    strcpy(head -> name, tmp.name);
    head -> chi = tmp.chi;
    head -> math = tmp.math;
    head -> average = (tmp.chi+tmp.math)/2;
    head ->next = NULL;
    p = head;
    
    while(1){
        fscanf(fpl1, "%d%s%f%f%f", &tmp.id, tmp.name, &tmp.chi, &tmp.math, &tmp.average);
        if(feof(fpl1))
            break;
        p = create(p, tmp.id, tmp.name, tmp.chi, tmp.math);
    }
    
    return head;
}
