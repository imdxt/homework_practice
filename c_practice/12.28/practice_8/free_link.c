
#include "declare.h"
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
