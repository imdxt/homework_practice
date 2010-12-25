#include <stdio.h>
#include <string.h>
typedef struct{
    char *comand[8];
    char *in;
    char *out;
}cmd;
cmd cmd_t;
int praces(char *a)
{
    char *p=a;
    int j=0;
    cmd_t.in=cmd_t.out=NULL;
    while(*p!='\0')
    {
        if(*p==' ')
        {
            *p='\0';
            p++;
            continue;
        }
        if(*p=='<')
        {
            p++;
            while(*p++==' ');
            cmd_t.in=--p;
        }
        if(*p=='>')
        {
            p++;
            while(*p++==' ');
            cmd_t.out=--p;
        }
        if(*p!='\0'&&((*(p-1)=='\0') || p==a))
        {
            cmd_t.comand[j++]=p;
            p++;
            continue;
        }
        p++;
    }
    cmd_t.comand[j]=NULL;
    return 0;
}
void show()
{
    int i;char *p;
    for(i=0;i<8;i++)
    {
        p=cmd_t.comand[i];
        if(p==NULL)
            break;
        if(i==0)
            printf(" Comand  : %s\n",p);
        else
            printf("        argument  : %s\n",p);
    }
   // printf("%s","\n");
    if(cmd_t.in || cmd_t.out)
        printf("        in-file   : %s\n        out-file  : %s\n",cmd_t.in,cmd_t.out);
}
int main(int argc, const char *argv[])
{
    char a[256],len;
    while(1)
    {
    printf(" Myshell%% :");
    fgets(a,256,stdin);
    len=strlen(a);
    a[len-1]='\0';
    praces(a);
    show();
    if(a[0]=='@')
    break;
    }
    return 0;
}
