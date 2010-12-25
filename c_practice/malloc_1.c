#include <stdio.h>
#include <stdlib.h>
struct x {
    int x[5];
    int y;
};
int main(int argc, const char *argv[])
{
    struct x *p;
    int i,j;
    p=(struct x *)malloc(sizeof(struct x)*10);
    if(p==NULL){
    printf("  Error!内存已用完  \n");
    return 0;
    }
    for(i=0;i<10;i++)
    {
        for (j = 0; j < 5; j++)     
            p[i].x[j] = j + 1;
        p[i].y=6;
        //结构体数组用数组访问形式如上通过.访问
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<5;j++)
        printf(" p[%d]->x[%d] = %d ",i+1,j,(p+i)->x[j]);
        printf("p[%d]->y = %d \n",i+1,(p+i)->y);
        //结构体指针的访问通过->访问
    }
    return 0;
}
