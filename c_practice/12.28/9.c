#include <stdio.h>
#include <stdlib.h>

typedef struct stu{
   int id;
   char name[256];
   float chi;
   float math;
   float average;
   struct stu * next;
}stu_t;
stu_t *create(stu_t *p)
{
    stu_t *q = (stu_t *)malloc(sizeof(stu_t));
    p->next = q;
    q->next = NULL;
    return q;
}
stu_t *head_1(FILE *fpl1)
{
    stu_t *p,*head = (stu_t *)malloc(sizeof(stu_t));
    p=head;
    fscanf(fpl1,"%d%s%f%f%f",&p->id, p->name, &p->chi, &p->math, &p->average);
    while(1)
    {
       p=create(p);
       fscanf(fpl1,"%d%s%f%f%f",&p->id, p->name, &p->chi, &p->math, &p->average);
       if(feof(fpl1))
       break;
    }
    return head;
}
stu_t *newhead(stu_t *a)
{
    stu_t *max,*p,*q,*head = (stu_t *)malloc(sizeof(stu_t));
    q = head;
    p = a;
    while(p != NULL)
    {
        p = a;
        max = p;
        while(a != NULL)
        {
            if(max->average < a->next->average)
                max=a->next;
             a = a->next;   
        }
        if(max == p)
            p = max->next;
        else
        {
            a = p;
            while(a->next != NULL)
            {
                if(a->next == max)
                {
                   // a->next = max->next;
                    break;
                }
                a = a->next;
            }
            a->next = max->next;
        }
        q->next = max;
        q = q->next;
        q->next = NULL;
       // *q = *max;
       // q = create(q);
    }
    max = head->next;
    free(q);
    return max;
}
void free_all(stu_t *head)
{
    stu_t *p = head;
    while(p != NULL)
    {
        free(p);p->next = NULL;
        p = p->next;
    }
}
stu_t *insert(stu_t *head, FILE *fp1)
{
    stu_t *q,*p=(stu_t *)malloc(sizeof(stu_t));
    q = head;
    while(!feof(fp1))
        p = q->next;
        q->next = p;
    fscanf(stdin,"%d%s%f%f%f",&p->id, p->name, &p->chi, &p->math, &p->average);
    return head;
}
void print(stu_t *p)
{
    stu_t *q = p;
    int i=1;
    printf("seq ID     Name           Chinese  Math    Average\n");
    printf("-------------------------------------------------\n");
    while(q->next != NULL)
    {
        printf(" %d: %-7d%-16s%-8.1f%-8.1f%-8.1f\n",i,q->id, q->name ,q->chi, q->math, q->average);
        q = q->next;
        i++;
    }
    printf("-------------------------------------------------");
}
int main(int argc, const char *argv[])
{
    int a,flag = 1; 
    FILE *fp2,*fp1 = fopen("dong.txt","r");
  //  char buf[256];
    stu_t *p,*head;
    while(flag)
    {
        printf("Please select the option :\n");
        printf("1.Display all student's info\n");
        printf("2.Sort by average\n");
        printf("3.Inster a new info\n");
        printf("4.Delete a record\n");
        printf("5.Quit\n");
        printf("Please input your choice :");
        scanf("%d",&a); 
        getchar();
        switch(a)
        {
            case 1:
               // while(fgets(buf,256,fp1))
               //     printf("%s\n",buf);
                p = head_1(fp1);
                print(p);
                fclose(fp1);
                free_all(p);
                getchar();
                break;
            case 2:
                p = head_1(fp1);
                head = newhead(p);
                print(head);
                fclose(fp1);
                free_all(p);
                free_all(head);
                getchar();
                break;
            case 3:
                fp2 = fopen("dong.txt","a+");
                p = head_1(fp2);
                head =insert(p,fp2);
                fflush(fp2);
                print(head);
                free(head);
                free(p);
                break;
            case 4:
                break;
            case 5:
                flag=0;
                break;
        }
    }
    return 0;
}
