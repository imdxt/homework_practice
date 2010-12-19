#include <stdio.h>

int add(int x, int y){return x + y;}
int sub(int x, int y){return x - y;}
int mul(int x, int y){return x * y;}
int dev(int x, int y){return x / y;}
int mod(int x, int y){return x % y;}
struct cmd{
    char op ;
    int(* handle)(int, int);
} ;
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
