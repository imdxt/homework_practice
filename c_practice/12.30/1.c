#include <stdio.h>
int get_right_bit(int a,int b)
{
    return (a>>b)&1;
}
int mul(int a,int b)
{
    int i,sum=0;
    for(i=0;i<31;i++)
    {
        if((b>>i)&1)
            sum += a<<i;
    int a,b;
    int c=100,i,dd;
    if(argc != 3)
    {
        printf("--------Please input command--------- \n");
        return 1;
    }
    sscanf(argv[1],"%d",&a);
    sscanf(argv[2],"%d",&b);
    printf("%d * %d =%d\n",a,b,mul(a,b));
   // sscanf(argv[1],"%d",&c);
  /*  int len=sizeof(int)*8;
    printf("len = %d\n",len);
    printf("a = %d b = %d\n",a,b);
    printf("a = %d b = %d\n",b^a^a,a^b^b);
    for(i=0;i<len;i++)
        printf("%d",get_right_bit(c,len-1-i));
    printf("\n");
   */
    return 0;
}
