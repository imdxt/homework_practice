#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stu{
   int id;
   char name[256];
   float chi;
   float math;
   float average;
   struct stu * next;
}stu_t;
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

stu_t *newhead(stu_t *a)
{
    stu_t *max,*temp_head = (stu_t *)malloc(sizeof(stu_t));
    stu_t *q,*head = temp_head;
    while(a != NULL)
    {
        max = q = a;
        while(q->next != NULL)
        {
            if(max->average < q->next->average)
                max=q->next;
             q = q->next;   
        }
        if(max == a)
            a = a->next;
        else
        {
            q = a;
            while(q->next != NULL)
            {
                if(q->next == max)
                {
                    q->next = max->next;
                    break;
                }
                q = q->next;
            }
        }
        head->next = max;
        head = head->next;
        head->next = NULL;
    }
    max = temp_head->next;
    free(temp_head);
    return max;
}
void free_all(stu_t *head)
{
    stu_t *p;
    while(head != NULL)
    {
        p = head;
        head = head->next;
        free(p);p = NULL;
    }
}

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
void write(stu_t *head)
{
        stu_t *p;
       FILE *fp1 = fopen("dong.txt","w");
        while(head != NULL)
        {
             fprintf(fp1,"%-7d%-16s%-8.1f%-8.1f%-8.1f\n",head->id,head->name,head->chi,head->math,(head->chi + head->math)/2);
             head = head->next;
        }
        fclose(fp1);
        free_all(head);
        fp1 = fopen("dong.txt","r");
        p = head_1(fp1);
        print(p);
        free_all(p);
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
int main(int argc, const char *argv[])
{
    int a,i,flag = 1,cont, cont_temp = 1,del_way;
    FILE *fp1 = fopen("dong.txt","r");
    char buf[256]={0};
    stu_t *p,*head;
    p = head_1(fp1);
    cont_temp = cont = init(p);
    while(flag)
    {
        printf("***********Please select the option :*************\n");
        printf("       1.Display all student's info\n");
        printf("       2.Sort by average\n");
        printf("       3.Inster a new info\n");
        printf("       4.Delete a record\n");
        printf("       5.Quit\n");
        printf("**************************************************\n");
        printf("Please input your choice :");
        scanf("%d",&a); 
        getchar();
        switch(a)
        {
            case 1:
                printf("seq ID     Name           Chinese  Math    Average\n");
                printf("-------------------------------------------------\n");
                fclose(fp1);
                fp1 = fopen("dong.txt","r");
                if(fgetc(fp1) == EOF){
                    fseek(fp1, 0L, SEEK_SET);
                    printf("          The file is empty!!!!!\n");
                    break;
                }
                fseek(fp1, 0L, SEEK_SET);
                i = 1;
                while(fgets(buf,256,fp1))
                {
                    printf(" %d: %s",i,buf);
                    i++;
                }
                printf("-------------------------------------------------\n");
                break;
            case 2:
                fclose(fp1);
                fp1 = fopen("dong.txt","r");
                p = head_1(fp1);
                head = newhead(p);
                print(head);
                free_all(head);
                break;
            case 3:
                fclose(fp1);
                fp1 = fopen("dong.txt","a+");
                printf("Please input new info (name chinese math)\n%d: ",cont + 1);
                stu_t temp;
                fscanf(stdin,"%s %f %f",temp.name,&temp.chi,&temp.math);
                temp.average = (temp.chi + temp.math)/2;
                fprintf(fp1,"%-7d%-16s%-8.1f%-8.1f%-8.1f\n",cont+1,temp.name,temp.chi,temp.math,temp.average);
                cont++;
                cont_temp = cont;
                fflush(fp1);
                break;
            case 4:
                fclose(fp1);
                fp1 = fopen("dong.txt","a+");
                if(fgetc(fp1) == EOF)
                {
                     fseek(fp1, 0L, SEEK_SET);
                     printf("-------------------------------------------------\n");
                     printf("          The file is empty!!!!!\n");
                     printf("-------------------------------------------------\n");
                     break;
                }
                fseek(fp1, 0L, SEEK_SET);
                printf("Please choose the way:\n");
                printf("1.Delete by ID\n");
                printf("2.Delete by name\n");
                printf("3.Exit\n");
                printf("Your choice:");
                scanf("%d",&del_way);
                getchar();
                delete_way(del_way,cont_temp);
                printf("-------Please input Enter continue------>>");
                getchar();
                break;
            case 5:
                flag=0;
                break;
        }
    }
    return 0;
}
