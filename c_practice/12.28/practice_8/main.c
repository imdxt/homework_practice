#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declare.h"

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
