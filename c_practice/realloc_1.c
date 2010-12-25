#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{   
    int *p,i=0,j;
    p=(int *)malloc(sizeof(int));
    printf(" Input num :\n");
    while(1)
    {
        printf("      ");
        scanf("%d",&p[i]);
        getchar();
        if(p[i++]==-1)
        break;
        p=realloc(p,sizeof(int)*(i+1));
    }
    for(j=0;j<i-1;j++)
    printf(" [ %d ] ",p[j]);
    printf("\n");
    free(p);p=NULL;
    return 0;
}
