#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int num = 0;
    int temp[54] = {0};
    int i = 0,j = 0;
    srand(time(NULL));

    while(1)
    {
       init: num = rand()%52;
        temp[i] = num;
        for(j = 0; j < i; j++)
        {
            if(temp[j] == num)
                goto init;
        }
        printf("%d  ",temp[i]+1);
        i++;
        if(i == 52)
            break;
    }
    putchar('\n');
    for(i = 0; i < 52; )
    {
        printf("1 : %4d%c    ",temp[i]%13+1,(temp[i])%4+65);
        printf("2 : %4d%c    ",(temp[i + 1])%13+1,(temp[i + 1])%4+65);
        printf("3 : %4d%c    ",(temp[i + 2])%13+1,(temp[i + 2])%4+65);
        printf("4 : %4d%c    \n",(temp[i + 3])%13+1,(temp[i + 3])%4+65);
        i = i + 4;
    }

    return 0;
}
