#include <stdio.h>
#include <string.h>

int mystrstr(char *new, char *str, char *stcstr)
{
    int cont = 0,i = 0, j = 0,temp = 0;
    int len1 = strlen(str);
    int len2 = strlen(stcstr);

    for (i = 0; i <len2; i++) 
    {
        for (j = 0; j < len1; j++) 
        {
            if((str[j] == stcstr[i + j]) && (stcstr[i + j] != '\0'))
                temp++;
            else break;
        }
        if(temp == len1)
        {
            cont++;
            temp = 0;
            for (j = 0; j < len1; j++) 
                stcstr[i + j] = new[j];
        }
        temp = 0;
    }
    printf("%s\n",stcstr);

    return cont;
}

int main(int argc,  char *argv[])
{
    int cont = 0;

    cont = mystrstr(argv[1],argv[2],argv[3]);
    printf("%d\n",cont);

    return 0;
}
