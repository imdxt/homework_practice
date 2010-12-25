#include <stdio.h>
//在字符串中输出最长的字符长度及其那段字符
struct aa
{
    int len_max;
    char *str_max;
}longstr;
//struct aa str(char *a)
//返回值为结构体类型的函数
void str(char *a)
{  
  //  struct aa mystr;
     char *str1;
     str1=a;
    int len1;
    longstr.len_max=len1=1;
    longstr.str_max=str1;
    //mystr.len_max=len1=1;
   // mystr.str_max=str1;
   // 下面的依次改变
    while(*str1++)
    {
    if(*str1==*(str1+1))
     len1++;
     else
     {
        if(len1>longstr.len_max)
        {
            longstr.len_max=len1;
            longstr.str_max=str1-len1+1;
        }
        len1=1;
     }
    }
    int i;
    printf("      len_max = %d\n",longstr.len_max);
    printf("      str_max : ");
    for(i=0;i<longstr.len_max;i++)
        printf("%c",longstr.str_max[i]);
    printf("\n");
  //  return mystr;
}
int main(int argc, const char *argv[])
{
  // int i;
  //  char a[]="aabcccchhhffffffddd";
    char a[101];
    printf("      Input a string :\n      ");
    scanf("%100s",a);//100为只读取前100的长度
    getchar();
  // longstr=str(a);
  // printf("%d\n",longstr.len_max);
  // for(i=0;i<longstr.len_max;i++)
  //    printf("%c",longstr.str_max[i]);
  // printf("\n");
     str(a);
    return 0;
}
