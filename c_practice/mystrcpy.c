#include <stdio.h>
char * mystrcpy(char *a, const char *b)
{   
    char *p=a;
   for(;*b!='\0';b++,p++)
       *p=*b;
        *p='\0';
        return a;
}
//////////////////////////////////////库函数strcpy的实现
char *mystrcpy_1(char *a, const char *b)
{
    char *p=a;
    while(*p++=*b++);
    return a;
}
///////////////////////////////////
char *mystrcpy_2(char *a,const char *b)
{
    int i=0;
    while(b[i])
        a[i]=b[i++];
    return a;
}
////////////////////////////////////////库函数strlen的实现
int mystrlen(const char *a)
{
    int b=0;
    while(*a){
    b++;
    a++;
    }
    return b;
}
/////////////////////////////////////

int mystrlen_1(const char *a)
{
    int b=0;
    for(;a[b]!=0;b++);
    return b;
}
///////////////////////////////
int main(int argc, const char *argv[])
{
    char a[10];
    char * mystrcpy(char *, const char *);
    printf("%s\n",mystrcpy(a,"dong"));
    printf("%s\n",mystrcpy_1(a,"dong"));
    printf("%s\n",mystrcpy_2(a,"dong"));
    
    printf("%d\n",mystrlen("dongxitian"));
    printf("%d\n",mystrlen_1("dongxitian"));
    return 0;
}
