#include <stdio.h>
#include <stdlib.h>

void myprintf(char *format , ...)
{
    char **p=&format;
    //p=p+1;
    int len=atoi(format),i,sum=0,a;
    //atoi把字符串内容转换成int
    for(i=1;i<=len;i++)
    {   
        a=atoi(*(p + i));
        sum += a;
    }
   printf("%d\n",sum);
 //   printf("%s\n",*(p+i));
    
   // char *a=&format;
   // a=a+4;
   //printf("%s\n",*(int *)a);
}
int main(int argc, const char *argv[])
{
    //sscanf(argv[1],"")
    myprintf("10","1","2","3","4","5","6","7","8","9","10");
    return 0;
}
