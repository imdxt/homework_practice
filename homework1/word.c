#include <stdio.h>
#include <string.h>
int aaa(char);
int main(int argc, const char *argv[])
{   
    char a[100]={0};
    char b[100]={0};
    int i=0,c=0,j=0,k=0;
    printf("Input string\n");
    gets(a);
    printf("original output:\n");
    puts(a);
    for(i=j=strlen(a)-1;i>=0;i--)
    {
         if(aaa(a[i]))
         {
            for(k=0;j==(strlen(a)-1)?k<(j-i):k<(j-i-1);k++)
                 b[c++]=a[i+k+1];
             b[c++]=a[i];
              j=i;
         }   
         if(i==0)
        {
            for(k=0;k<j;k++)
             b[c++]=a[k];
        }
    }
   printf("inverted output:\n");
    puts(b);
    return 0;
}
int aaa(char temp)
{
    if( (temp>='0' && temp<='9') || (temp>='A' && temp<='Z') || (temp>='a' && temp<='z') )
    return 0;
    else
    return 1;

}
