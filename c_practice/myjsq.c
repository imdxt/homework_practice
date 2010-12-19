#include <stdio.h>
typedef int (*fun)(int , int);
//定义类型，为类型命名，与直接写出变量的类型定义变量效果完全相同。

int add(int a, int b)  { return a+b;}
int subtract(int a, int b) { return a-b;}
int multiply(int a, int b) { return a*b;}
int dev(int a, int b){ return a/b;}
int mod(int a, int b){ return a%b;}
int main(int argc, const char *argv[])
{
    int a,b,ad,su,mu,de,mo;
    char i;
    fun add1;//申请一个地址空间
    add1=add;//把函数add的入口地址赋给add1 

    fun subtract1;
    subtract1=subtract;
    
    fun multiply1;
    multiply1=multiply;

    fun dev1;
    dev1=dev;

    fun mod1;
    mod1=mod;
    while(1)
    {
    printf("Input a symbol:\n");
    scanf("%c",&i);
    if(i=='#') break;
        printf("Input num1:\n");
         scanf("%d",&a);
          printf("Input num2:\n");
          scanf("%d",&b);
          ad=add1(a,b);
          getchar();//因为输入完成之后要回车才能输入字符，程序会把回车当字符读入造成程序出乱，所以加上getchar（）
    switch(i)
    {
        case '+':
          ad=add1(a,b);
          printf("%d + %d= %d\n",a,b,ad);
          break;
         
        case '-':
         su=subtract1(a,b);
          printf("%d - %d= %d\n",a,b,su);
          break;
        case '*':
          mu=multiply1(a,b);
          printf("%d * %d= %d\n",a,b,mu);
          break;
        case '/':
          de=dev1(a,b);
          printf("%d / %d= %d\n",a,b,de);
          break;
        case '%':
          mo=mod1(a,b);
          printf("%d %% %d= %d\n",a,b,mo);
          //打印%的时候 中间要加一个%分开 否则会出错误
          break;
    }

    }
    return 0;
}
/******************************************************/
// this is teacher write;
#include <stdio.h>

int add(int x, int y){return x + y;}
int sub(int x, int y){return x - y;}
int mul(int x, int y){return x * y;}
int dev(int x, int y){return x / y;}
int mod(int x, int y){return x % y;}
struct cmd{
    char op ;
    int(* handle)(int, int);
} ;//结构体
void test(void){
     double a;
     scanf("%f", (float *)&a);
}
struct cmd arr[] = {
    {'+',add},
    {'-',sub},
    {'*',mul},
    {'/',dev},
    {'%',mod}
};
int main(int argc, char * argv[]){
    char op; int x,y;
    int i, ret;
    while(1)
    {
    scanf("%c", &op);

    if(op == '#') break;
    scanf("%d %d",&x, &y);
    for(i = 0; i < 5; i++)                                                          {   
    if(arr[i].op == op)
        ret = arr[i].handle(x, y);
    }                                                                               getchar();
    printf("%d %c %d = %d\n", x, op, y, ret);
    }
    return 0;
    }
