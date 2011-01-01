#include <stdio.h>
//约瑟夫环问题
struct people {
    int ID;
    int out;
}aa[100];

int main(int argc, const char *argv[])
{   
    int i,j=0,m=0,a=0;
    for(i=0;i<100;i++)
    {
        aa[i].ID=i+1;
        aa[i].out=0;
    }
    
    //for(m=0;m<50;m++)
    //{     
        for(i=0;i<100;i++)
        {        
            for(; ;)
            {
                if(aa[m].out==0){
                j++;
                    if(j==3){
                    j=0;
                    aa[m].out=1;
                    a++;
                    printf("%d : ID=%d out\n",a,aa[m].ID);
                    break;
                    } 
                }
                m++;
                m=m%100;
            } 
           }
     //}
    return 0;
}
