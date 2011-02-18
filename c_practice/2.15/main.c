#include <stdio.h>
#include <string.h>

int mystrstr(const char *str, const char *stcstr)
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
        }
        temp = 0;
    }

    return cont;
}

int main(int argc, const char *argv[])
{
    int cont = 0;

    cont = mystrstr(argv[1],argv[2]);
    printf("%d\n",cont);

    return 0;
}
    
/***********************techer******************************/
/*
#include <stdio.h>

int mystrstr(const char *str, const char *srcstr)
{
    const char * str_p = str;
    const char * srcstr_p = srcstr;
    int mun = 0;

    while(*str && *srcstr)
    {
        while(*str == *srcstr && *srcstr != '\0')
        {
            str++, srcstr++;
            if(*str == '\0')
                num++;
        }
        str = str_p;
        srcstr_p++;
        srcstr = srcstr_p;
    }
    return num;
}
int main(int argc, char *argv[])
{
    
    int cont = 0;

    cont = mystrstr(argv[1],argv[2]);
    printf("%d\n",cont);
    return 0;
}
*/
/***********************************************************/
