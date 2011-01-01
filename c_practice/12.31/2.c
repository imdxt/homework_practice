#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void printsum(char *format,...)
{
    char *p;
    int sum=0,i,len=atoi(format);
    va_list ap;
    va_start(ap,format);
    for(i=0;i<len;i++)
    {
        p = va_arg(ap,char *);
       // printf("%s\n",p);
        sum += atoi(p);
    }
    printf("%d\n",sum);
    va_end(ap);
}
int main(int argc, const char *argv[])
{
    printsum("10","1","2","3","4","5","6","7","8","9","10");
    return 0;
}
