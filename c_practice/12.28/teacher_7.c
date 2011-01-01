#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stu *link;
struct stu{
    char name[256];
    int chinese;
    int maths;
    int average;
    link next;
};

link make(link n,FILE *fp)
{
    link p ;
    p = malloc(sizeof(struct stu));
    fscanf(fp, "%s %d %d %d", p->name, &p->chinese, &p->maths, &p->average);
    p->next = n;
    return p;
}
void travel(link head)
{
    link p = head;
    while(p){       
        fprintf(stdout, "%10s %5d %5d %5d\n", p->name, p->chinese, p->maths, p->average);
        p = p->next;
    }
}
link sort_insert(link head, link n)
{
    link p = head, pre;
    if(n->average > p->average){
    n->next = p;
    return n;
    }
    pre = p; p = p->next;
    while(p != NULL){
        if(n->average > p->average) break;
        pre = p; p = p->next;
    }
    if(p){
        n->next = p;
        pre->next = n;
    }
    else{
        n->next = NULL;
        pre->next = n;
    }

    return head;      
}
link sort(link head)
{
    link p,tmp, new = head;
    p = head->next; 
    new->next = NULL;
    while(p){
    tmp = p->next;
    new = sort_insert(new, p);
    p = tmp;
    }
    return new;
}
int main(int argc, char *arg[])
{
    struct stu stu1[] = {
    {"zhang",90,82,85},
    {"song",90,85,84},
    {"zhao",90,88,83},
    {"wang",90,89,81},
    {"li",90,81,80}};
    FILE *fp; int i; link head, p;

    fp = fopen("stu.txt","w");
    for(i = 0; i < 5; i++)
    fprintf(fp, "%s %d %d %d\n", stu1[i].name, stu1[i].chinese, stu1[i].maths, stu1[i].average);
    fclose(fp);

    fp = fopen("stu.txt","r");
    p = make(NULL, fp);
    for(i = 0; i < 4; i++){
    p = make(p, fp);
    }
    head = p;
    fclose(fp);

    head = sort(head);
    travel(head);

    return 0;
}

