#include <stdio.h>

int main(int argc, const char *argv[])
{ 
    FILE *fpl1,*fpl2;
    char  a[100];
    int n,i;
    if(argc != 3)//判断命令行是否已经输入三个命令 否则退出
        return 1;
    fpl1 = fopen(argv[1],"r");
    fpl2 = fopen(argv[2],"w");
    
    fgets(a,100,fpl1);
    fputs(a,fpl2);
   // for(i=0;i<30;i++)
   // fputc(a[i],stdout); 
    printf("%s\n",a);
    n = fcloseall();
   // fclose(fpl2);
    printf("%d\n",n);
    return 0;
}
