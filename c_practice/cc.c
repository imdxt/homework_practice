 #include <stdio.h>
 void print_segi(void)
 {
    printf(" * ");
 }
 int main(int argc, const char *argv[])
 {
     int i,j;
     void (*piont1)(void)=print_segi;
    // piont1=print_segi;
     for(i=0;i<5;i++)
     {
        for(j=0;j<5;j++)
        {
          (*piont1)();
        }
        printf("\n");
     }
     return 0;
 }
