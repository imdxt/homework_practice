#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct stu{
  int id;
  char name[256];
  int chi;
  int math;
  int average;
  struct stu *next;
}stu_t;
stu_t *creat(stu_t *pro,int id,char *name,int chi,int math)
{
    stu_t *p;
    p=(stu_t *)malloc(sizeof(stu_t));
    p->id=id;
    strcpy(p->name,name);
    p->chi=chi;
    p->math=math;
    p->average=(chi+math)/2;
    p->next=NULL;
    pro->next=p;
    return p;
}
stu_t *get_max(stu_t *a)
{
    stu_t *p,*max;
    stu_t *q=(stu_t *)malloc(sizeof(stu_t));
    int i;
    while(a != NULL)
    {
         max=p=a;
        while(p->next != NULL)
        {   
            if(max->average > p->next->average)
                  max=max;
             else
                max=p->next;
             p=p->next;
        }
        if(max==a)
            a=a->next;
        else
        {
            p=a;
            while(p->next != NULL)
            {
            if(p->next==max)
            {
                p->next=max->next;
                break;
            }
             p=p->next;
            }
        }
        q=max;

   printf("id =%d name =%s chinese =%d math =%d\n",max->id,max->name,max->chi,max->math);   
    }        
     return q;
}
void print(stu_t * q)
{
    stu_t *p=q;
    while(p != NULL)
    {
        printf("id =%d name =%s chinese =%d math =%d\n",p->id,p->name,p->chi,p->math);
       p=p->next;
    }
}
int main(int argc, const char *argv[])
{
    stu_t *head,*q;
    int i;
    head=malloc(sizeof(stu_t));
    q=head;
    stu_t p[]={
    {1,"dong1",99,99},
    {2,"dong2",90,90},
    {3,"dong3",85,85},
    {4,"dong4",84,84},
    {5,"dong5",87,87},
    };
    for(i=0;i<5;i++)
    q=creat(q,p[i].id,p[i].name,p[i].chi,p[i].math);
    print(head->next);
    printf("*******************************\n");
    get_max(head->next);
    return 0;
}
