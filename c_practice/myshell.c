#include <stdio.h>
#include <string.h>
//输入命令
int parse(char *a)
{
    char * p=a;
    char *comand[8];
    int i=0,j=0;
    while(*p != '\0')
    {   
        if(*p == ' ')
       {
        *p='\0';
        p++;
        continue;
        }
        if(*(p-1)=='\0'||p==a)
       {
            comand[j]=p;
            p++;
            j++;
            continue;
       }
       p++;
    }
      
       printf("comand   : %s \n",comand[0]);
       for(i=0;i<j;i++)
       {
       if(comand[i][0]=='-')
            printf("         argument : %s \n",comand[i]);
       if(comand[i][0]=='<')
            printf("         in       : %s \n",comand[i+1]);
       if(comand[i][0]=='>')
            printf("         out      : %s \n",comand[i+1]);
       }
    return 0;
}
int main(int argc, const char *argv[])
{
    char a[256],len;
    printf("Please myshell %% ");
    fgets(a,256,stdin);
    len=strlen(a);
    a[len-1]='\0';
    //把最后一个回车改成\0
    parse(a);
    return 0;
}
