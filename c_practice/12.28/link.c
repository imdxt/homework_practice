#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tmp_t{
    unsigned id;
    char name[20];
    float chinese;
    float math;
    float average;
    struct tmp_t *next;
}student_t;

student_t * creat(student_t *p, int id, char *name, float chinese, float math)
{
    p -> next = (student_t *)malloc(sizeof(student_t));
    p = p -> next;
    p -> next = NULL;
    p -> id = id;
    strcpy(p -> name, name);
    p -> chinese = chinese;
    p -> math = math;
    p -> average = (chinese+math)/2;

    return  p;
}

student_t * get_max(student_t *p1, student_t *p2)
{
    if(p1 -> average > p2 -> average)
        return p1;
    else 
        return p2;
}

student_t * get_max_in_all(student_t *p)
{   
    student_t *max, *head = p;
    student_t *tmp_head = (student_t *)malloc(sizeof(student_t));
    student_t *pnew = tmp_head;
   
    while(head != NULL) {
        p = head;
        max = p;
        while(p != NULL) {
            max = get_max(max, p);
            p = p -> next;
        }
        if(max == head) {
            head = max -> next;
        }
        else {
            p = head ;
            while(p -> next != NULL) {
                if(p -> next  == max)
                break;
                p = p -> next;
            }
            p -> next = max -> next;
        }
        pnew -> next = max;
        pnew = pnew -> next;
        pnew -> next = NULL;
    }
    max = tmp_head -> next;
    free(tmp_head);

    return max;
}
student_t * disp(student_t *p)
{
        printf("id:%-3d    name:%-15s chinese:%-6.1f    math:%-6.1f    average:%-6.1f\n", 
        p -> id, p -> name, p ->chinese, p -> math, p -> average);

        return p;
}

student_t * fun_void(student_t *p){;}

int tral(student_t *p, student_t * (*fun)(student_t *))
{
    student_t *tmp;
    int i = 0;
    while(p != NULL){
        tmp = fun(p);
        i++;
        p = p -> next;
    }
    return i;
}

student_t * read_from_file(FILE *fp)
{
    student_t tmp;
    if(feof(fp) != 0)
    return NULL;

    fscanf(fp, "%d%s%f%f%f", &tmp.id, tmp.name, &tmp.chinese, &tmp.math, &tmp.average);
    student_t *head = (student_t *)malloc(sizeof(student_t));
    head -> id = tmp.id;
    strcpy(head -> name, tmp.name);
    head -> chinese = tmp.chinese;
    head -> math = tmp.math;
    head -> average = (tmp.chinese+tmp.math)/2;
    student_t *p = head;
    
    while(1){
        if(EOF == fscanf(fp, "%d%s%f%f%f", &tmp.id, tmp.name, &tmp.chinese, &tmp.math, &tmp.average))
            break;
        p = creat(p, tmp.id, tmp.name, tmp.chinese, tmp.math);
    }
    
    return head;
}
void free_all(student_t *p)
{
     student_t *tmp;
     while(p != NULL){
        tmp = p;
        p = p -> next;
        free(tmp);
     }
}
student_t * delete(student_t *p, int id)
{   
    student_t *head_tmp, *end_tmp, *head = (student_t *)malloc(sizeof(student_t));
    head -> next = p;
    head ->id = 0;
    while(p -> next != NULL)
        p = p -> next;
    p -> next = (student_t *)malloc(sizeof(student_t));
    p -> next -> next = NULL;
    p -> next -> id = 0;

    for (p = head; p -> next != NULL; end_tmp = p, p = p -> next) 
    {
        if (p -> next -> id == id) 
        {
            //if(p -> next -> next == NULL)
            //{
            //free(p->next);
            //p -> next = NULL;
            //}
            //else
            //{
                free(p -> next);
                p -> next = p -> next -> next;
                //}
                
        }
    }
    free(p);
    end_tmp -> next = NULL;
    head_tmp = head -> next;
    free(head);

    return head_tmp;
}
int write_into_file(student_t *p, const char *fname)
{   
    FILE *fp = fopen(fname, "w");
    for (; p != NULL; p = p-> next) 
    {
        fprintf(fp, "%-7d%-15s%-8.1f%-8.1f%-8.1f\n", p -> id, p -> name, p -> chinese, 
            p -> math, (p -> chinese+p -> math)/2);
    }
    
    return fclose(fp);
}
int main(int argc, const char *argv[])
{
    char choice_c;
    int flag = 0, item_cont, id_tmp;

    FILE *fp = fopen("student.db", "r");
    student_t *head = read_from_file(fp);
    item_cont = tral(head, fun_void);

    while(!flag){
        printf("Please select the option:\n");
        printf("1.Display all student's info\n");
        printf("2.Sort by average\n");
        printf("3.Insert a new info\n");
        printf("4.Delete a record\n");
        printf("5.Quit\n");
        printf("Please input your choice:");
        
        scanf("%c", &choice_c);
        getchar();
        switch(choice_c)
        {
            case '1':
                tral(head, disp);
                break;    
            case '2':
                head = get_max_in_all(head); 
                tral(head, disp);
                free_all(head);
                fclose(fp);
                fp = fopen("student.db", "r");
                head = read_from_file(fp);
                break;
            case '3':
                fclose(fp);
                fp = fopen("student.db", "a+");
                student_t tmp;
                printf("Please input the new info(id name chinese math):\n%d:",1 + item_cont);
            
                scanf("%s%f%f", tmp.name, &tmp.chinese, &tmp.math);
                getchar();
                fprintf(fp, "%-7d%-15s%-8.1f%-8.1f%-8.1f\n", 1+item_cont, tmp.name, tmp.chinese, 
                    tmp.math, (tmp.chinese+tmp.math)/2);
                
                fclose(fp);
                free_all(head);
                fp = fopen("student.db", "r");
                head = read_from_file(fp);
                item_cont++;
                break;
            case '4':
                fclose(fp);
                printf("Please input the id:");
                scanf("%d", &id_tmp);
                getchar();
                head = delete(head, id_tmp);
                write_into_file(head, "student.db");
                free_all(head);
                fp = fopen("student.db", "r");
                head = read_from_file(fp);
                 break;
            case '5':
                fclose(fp);
                free_all(head);
                flag = 1;
                break;
            defalut:
                break;
        }
    }

    return 0;
    
}
