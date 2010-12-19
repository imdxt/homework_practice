#include <stdio.h>
int fun1(int a , int b)
{
    return a*b;
}
int main(int argc, const char *argv[])
{
    int (*fun)(int , int);
    fun=fun1;
    int i,j;
    scanf("%d",&i);
    printf("j=");
    scanf("%d",&j);
    int a=(*fun)(i,j);
    printf("i*j=%d\n",a);
    printf("%p\n",fun);
    printf("%p\n",*fun1);
    return 0;
}
