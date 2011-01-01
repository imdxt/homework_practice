#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void m(char **a)
{
    char *p=malloc(100);
    strcpy(p,"aaa");
    *a=p;
}
int main(int argc, const char *argv[])
{
    char *p="bbb";
    m(&p);
    printf("%s\n",p);
    return 0;
}
