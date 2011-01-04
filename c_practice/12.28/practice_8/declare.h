#ifndef _DECLARE_H_
#define _DECLARE_H_
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
stu_t * create(stu_t *p, int id, char *name, float chi, float math);
int init(stu_t *head);
stu_t * head_1(FILE *fpl1); 
stu_t * newhead(stu_t *a);
void free_all(stu_t *head);
stu_t * delete_id(stu_t *head, int id);
stu_t * delete_name(stu_t *head, char name[256]);
void print(stu_t *p);   
void write(stu_t *head);
void delete_way(int way,int cont_temp);
#endif
