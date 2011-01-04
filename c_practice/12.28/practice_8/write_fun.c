
#include "declare.h"
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
