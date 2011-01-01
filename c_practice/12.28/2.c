#include <stdio.h>
#include <stdlib.h>
//约瑟夫环的链表实现
struct stu{
    int id;
    struct stu *next;
};
struct stu * make(int id,struct stu *p)
{
    struct stu *aa;
    aa=(struct stu *)malloc(sizeof(struct stu));
    aa->id=id;
    aa->next=p;
    return aa;
}
void print(struct stu *next,int n)
{
    struct stu *p=next;
    int i=0;
    while(1)
    {
        printf(" %d ",p->id);
        p=p->next;
        i++;
        if(i==n)
        {
            printf("\n");
            break;
        }
    }
}
int main(int argc, const char *argv[])
{
    struct stu *head,*p,*q;
    int i,n=0;
    head=p=make(1,NULL);
    p->next=p;
    for(i=2;i<=10;i++)
        p = p->next = make(i,p->next);
    print(head,10);
    while(p != p->next)
    {
        for(i=0;i<2;i++)
            p = p->next;
        q = p->next;
        p->next = p->next->next;
        printf(" id = %d  out \n",q->id);
        free(q);q=NULL;
        if(p == p->next)
        {
            printf(" %d win!!\n",p->id);
            break;
        }
        
    }
    return 0;
}
