#include <stdio.h>
typedef int (*fun)(int , int);
int add(int a, int b)  { return a+b;}
int subtract(int a, int b) { return a-b;}
int multiply(int a, int b) { return a*b;}
int dev(int a, int b){ return a/b;}
int mod(int a, int b){ return a%b;}
int main(int argc, const char *argv[])
{
    int a,b,ad,su,mu,de,mo;
    char i;
    fun add1;
    add1=add;

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
          getchar();
    switch(i)
    {
        case '+':
          ad=add1(a,b);
          printf("%d+%d=%d\n",a,b,ad);
          break;
         
        case '-':
         su=subtract1(a,b);
          printf("%d-%d=%d\n",a,b,su);
          break;
        case '*':
          mu=multiply1(a,b);
          printf("%d*%d=%d\n",a,b,mu);
          break;
        case '/':
          de=dev1(a,b);
          printf("%d/%d=%d\n",a,b,de);
          break;
        case '%':
          mo=mod1(a,b);
          printf("%d %% %d=%d\n",a,b,mo);
          break;
    }

    }
    return 0;
}
