#include <stdio.h>
/*
int main(int argc, const char *argv[])
{
    FILE *fpl1,*fpl2;
    int  a;

    fpl1 = fopen("aa.txt","r");
    fpl2 = fopen("bb","w");
    
    while((a=fgetc(fpl1)) != EOF)
         fputc(a,fpl2);

    fclose(fpl1);
    fclose(fpl2);

    return 0;
}*/
/**************************************************/
int main(int argc, const char *argv[])
{
    FILE *fpl1,*fpl2;
    int  a;

    fpl1 = fopen("aa.txt","r");
    fpl2 = fopen("bb","w");
    
    while(1)
    {
        a=fgetc(fpl1);
        if(feof(fpl1))
       // if(EOF==a)
       {  printf("%d\n",feof(fpl1));
        break;
        }
        fputc(a,fpl2);
         printf("%d\n",feof(fpl1));
    }
    fclose(fpl1);
    fclose(fpl2);

    return 0;
}
