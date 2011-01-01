#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//单向链表的建立 插入 删除 
struct stu{
    int id;
    int chinese;
    char name[256];
    struct stu *next;
};
struct stu * create(struct stu *pro , int id ,int chinese , char *name)
{
    struct stu *p = (struct stu *)malloc(sizeof(struct stu));
    p->id =id;
    p->chinese = chinese;
    strcpy(p->name,name);
    p->next = NULL;
   
    pro->next=p;
    return p;
}
void print(struct stu *p)
{
    printf("id =%d chinese =%d name =%s\n",p->id,p->chinese,p->name);
   
}
struct stu * delete(int id ,struct stu *pp)
{
    struct stu * q,*p=pp;
    if(p->id==id)
    {
        q=p->next;
        free(pp);p=NULL;
        return q;
    }
    while(p->next != NULL)
    {
        if(p->next->id == id)
        {
            q=p->next;
            p->next=p->next->next;
            free(q);q=NULL;
        }
        p=p->next;
    }
    return pp;
}
void next(struct stu *p,void (*fun)(struct stu *))
{  
    struct stu *q;
    while(p != NULL)
    {
        fun(p);
     //   if(p->id==0){
      //  q=p->next;
     //   p->next=p->next->next;
     //   free(q);q=NULL;
     //  }
        p=p->next;
    }
}
struct stu *charru(struct stu *next,int id,int chinese ,char *name)
{   
    if(next == NULL)
    return NULL;
    struct stu *p;
    p=malloc(sizeof(struct stu));
    p->id=id;
    p->chinese=chinese;
    strcpy(p->name,name);
    p->next=next->next;
    next->next=p;
    return p;
}
int main(int argc, const char *argv[])
{
    struct stu *p,*head;
    int i,k;
    char aa[256]; 
    head = (struct stu *)malloc(sizeof(struct stu));
    p=head;
    //head->id = 0;
    //head->chinese = 90;
    //strcpy(head->name,"dong0");
    sscanf(argv[1],"%d",&k);
    for(i=1;i<k;i++)
    {
        sprintf(aa,"dong%d",i);
        p=create(p,i,90+i%10,aa);
    }
    //for(i=0;i<10;i++)
    //{
   // head=delete(1,head);
    next(head,print);
   
    printf("*********************\n");
    //}
    p=head->next;
    charru(p,100,90,"dong100");
    next(head,print);
   
    return 0;
}
