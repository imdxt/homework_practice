
#include "declare.h"
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
