#include <stdio.h>

int main(int argc, const char *argv[])
{
    int k=10;
    char a[][3]={"123","456","789"};
    char s[100];
    sscanf(a[0],"%d",&k);
//sscanf与scanf类似，都是用于输入的，只是后者以键盘(stdin)为输入源，前者以固定字符串为输入源。
//本句的意思是将a［］中的字符串以%d的形式传给k
    printf("%d\n",k);
    sprintf(s,"%d",10);
//sprintf 最常见的应用之一莫过于把整数打印到字符串中
//本句的意思是将10 对应整型 传给字符串s中
    printf("%s\n",s);
    return 0;
}
