#include <stdio.h>

int main(int argc, const char *argv[])
{ 
    FILE *fpl1,*fpl2;
    int  a;
    if(argc != 3)
        return 1;
    fpl1 = fopen(argv[1],"r");
    fpl2 = fopen(argv[2],"w");
    
    while((a=fgetc(fpl1)) != EOF)
         fputc(a,fpl2);

    fclose(fpl1);
    fclose(fpl2);
    return 0;
}
