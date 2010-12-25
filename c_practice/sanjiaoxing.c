#include <stdio.h>
void main()
{
   int nWidth,a,b;
   printf("Please Input wide = ");
      scanf("%d",&nWidth);
        for(a=(nWidth%2);a<=nWidth;a+=2)
        {
        for(b=0;b<nWidth;b++)
        {
        char chOut =' ';
        int nleft =(nWidth -a)/2;
        int nright = (nWidth+a)/2;
        if(b>=nleft&&b<nright)                                                        {
            chOut ='*';
        }
        printf("%c",chOut);
        }
        printf("\n");
    }
}
