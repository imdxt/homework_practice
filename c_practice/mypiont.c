#include <stdio.h>
//打印出*型矩阵 我这里用的main函数参数 的强制转换类型 运行用./a.out k

void printf_1(void){
    printf(" * ");
}
void my_print(int a ,void (*fun)(void)){
    int j;
        for(j=0;j<a;j++)
                fun();    
}
int main(int argc, const char *argv[])
{
    int i;
    int k;
    sscanf(argv[1],"%d",&k);
    //格式转换 还可以转换其他的形式，现在转换成int型
    for(i=0;i<k;i++){
    my_print(k,printf_1);
    printf(" %d\n",i+1);
    }
    return 0;
}
/*************************************************/
#include <stdio.h>//比较两个数的大小 用反调函数实现
int cmp_int(void *a, void *b)
{
    if ( *(int *)a >= *(int *)b )
     return 1;
     else
     return 0;
}
int cmp_char(void *a, void *b)
{
    if ( *(char *)a >= *(char *)b )
     return 1;
     else
     return 0;
}
void * get_max(void *a , int len ,int size , int (*fun)(void * ,void *))
{
    void *max;
    int i;
    max = a;
    for(i=0;i<len;i++){
   if(fun(max , a+i*size))
        max=max;
   else
         max=a+i*size;
   }
   return max;
}
int main(int argc, const char *argv[])
{
    int a[10]={1,2,3,5,4,6,9,8,7};
    char b[10]={1,4,5,2,0,1,8,7,6};
    int * ret;
    ret =(int *)get_max(a , 10 , 4 , cmp_int);
    printf("cmp_int max =%d\n",*ret);
    ret =(int *)get_max(b , 10 , 1 , cmp_char);
    printf("cmp_char max =%d\n",*(char *)ret);
    return 0;
}
