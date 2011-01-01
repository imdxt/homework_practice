#include <stdio.h>
#include <string.h>
#include <ctype.h>
//位操作
void get_num_bit(int a)
{
    int b[32] = {0},i = 0,j = 0;
    printf("decimal %d chage to binary is ",a);
    while(a)
    {
        b[i++] = a&1;
        a = a>>1;
    }
    for (j = i-1;j >= 0;j--) 
       printf("%d",b[j]);
}
int mul(int a,int b)
{
    int i,sum=0;
    for(i = 0;i < 31;i++)
    {
        if((b>>i) & 1)
            sum += a<<i;
    }
    return sum;
}
void exchange(char s[])
{
    int i = 0;
    for(i = 0;i < strlen(s); i++)
    {
     if(s[i] >='a' && s[i] <= 'z')
        s[i]=toupper(s[i]);
     else if(s[i] >= 'A' && s[i] <= 'Z')
              s[i]=tolower(s[i]);
    }  
    printf("%s\n",s);
}
void encryption(char b)
{
    char a = '&';
    char d;
    d = a ^ b;
    printf("this char ASCII =%d\n",d);
    if(d < 33)
        printf("Please input value char\n");
    else
    printf("After encrytion :%c\n",d);
}
int main(int argc, const char *argv[])
{
    int i,flag=1,a,b;
    char c[256];
    char d;
    while(flag)
    {
        printf("1.decimal to binary\n");
        printf("2.x*y\n");
        printf("3.low or up exchange\n");
        printf("4.encryption\n");
        printf("5.Exit\n");
        printf("Please choose [1-5]:");
        scanf("%d",&i);
        getchar();
        switch(i)
        {
            case 1:
                printf("***********************************\n");
                printf("Input a number:");
                scanf("%d",&a);
                getchar();
                get_num_bit(a);
                printf("\n*******Input Enter continue********\n");
                getchar();
                break;
            case 2:
                printf("***********************************\n");
                printf("Please input x y:");
                scanf("%d %d",&a,&b);
                getchar();
                printf("%d  *  %d  = %d\n", a, b, mul(a,b));
                printf("******Input Enter continue********\n");
                getchar();
                break;
            case 3:
                printf("*************************************\n");
                printf("Please input a string :");
                scanf("%s",c);
                getchar();
                exchange(c);
                printf("******Input Enter continue********\n");
                getchar();
                break;
            case 4:
                printf("*************************************\n");
                printf("Please input a char:");
                scanf("%c",&d);
                getchar();
                encryption(b);
                printf("******Input Enter continue*********\n");
                getchar();
                break;
            case 5:
                flag=0;
                break;
        }
    }
    return 0;
}
