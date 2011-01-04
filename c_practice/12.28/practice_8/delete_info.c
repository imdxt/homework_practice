#include "declare.h"
stu_t *delete_id(stu_t *head, int id)
{
    stu_t *q,*p=head;
    if(p->id == id)
    {
        q = p;
        p = p->next;
        free(q); q = NULL;
        return p;
    }
    while(p != NULL)
    {
        if(p->next->id == id)
        {
            q = p->next;
            p->next = q->next;
            free(q);q = NULL;
            break;
        }
        p = p->next;
    }
    return head;
}
stu_t *delete_name(stu_t *head, char name[256])
{
    stu_t *q,*p=head;
    if(strcmp(p->name, name) == 0)
    {
        q = p;
        p = p->next;
        free(q); q = NULL;
        return p;
    }
    while(p != NULL)
    {
        if(strcmp(p->next->name, name) == 0)
        {
            q = p->next;
            p->next = q->next;
            free(q);q = NULL;
            break;
        }
        p = p->next;
    }
    return head;
}
void delete_way(int way,int cont_temp)
{
    char name[256];
    int id_cont;
    stu_t *p,*head;
    FILE *fp1;
    switch(way)
    {
        case 1:
            printf("Please input delete the ID :1~%d:",cont_temp);
            scanf("%d",&id_cont);
            getchar();
            fp1 = fopen("dong.txt","r");
            p = head_1(fp1);
            fclose(fp1);
            head = delete_id(p,id_cont);
            write(head);
            break;
        case 2:
            printf("Please input delete the Name :");
            scanf("%s",name);
            getchar();
            fp1 = fopen("dong.txt","r");
            p = head_1(fp1);
            fclose(fp1);
            head = delete_name(p,name);
            write(head);
        case 3:
            break;
    }
}
