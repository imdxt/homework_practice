#include <stdio.h>
int main(int argc, const char *argv[])
{
    char a[]="abc";
        a[1]=0;
        printf("%s\n",a);
        printf("%d\n",a[2]); 
        printf("%d\n",a[6]);
        printf("\n");
    return 0;
}
