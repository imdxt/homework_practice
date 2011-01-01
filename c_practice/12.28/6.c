#include <stdio.h>

int main(int argc, const char *argv[])
{ 
    FILE *fpl1,*fpl2;
    char  a[100];
    int len;
    if(argc != 3)
        return 1;
    fpl1 = fopen(argv[1],"r");
    fpl2 = fopen(argv[2],"w");
    
    while(1)
   {
    if(feof(fpl1))
        break;
    len = fread(a,1,20,fpl1);
    printf("%d\n",len);
    fwrite(a,1,len,fpl2);
   }
    fclose(fpl1);
    fclose(fpl2);
    return 0;
}
