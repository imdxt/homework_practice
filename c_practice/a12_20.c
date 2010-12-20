#include <stdio.h>

#include <string.h>
union work{
    int a;
    char c;
    char bb[100];
};//联合体，共用一个地址，能输出最后赋值的内容
int main(int argc, const char *argv[])
{
    union work uu;//定义联合体类型变量
    uu.a=127;
    char *q;
    int i,*p[4],a=10;char b[10]={1,'b',3,4,5,6,7,8,9};
    strcpy(uu.bb,"abc");
    printf("%s\n",uu.bb);
    printf("%s\n",&uu.a);
    printf("%x\n",uu.a);
    printf("%d\n",uu.a);
    p[0]=&a;
    p[1]=(int *)&b[0];//把char型转换成int指针，就是把地址强制转换成int
    printf("%d\n",*(p[0]));
    q = (char *)p[1];
    for(i=0;i<9;i++){
      //  printf("%d\n", *q++);
      //  这样也可以实现全部打印出来，不要直接写，最好用q代替
        
    printf("%d\n",*((char *)p[1]+i));
   //转换成char型用int型指针p［］输出char型b［］的内容输出
   
   // printf("%c\n",*((char *)*(p+1)+i));
    }
    return 0; 
}
/*************************************************/
#include <stdio.h>
struct stu_t{
    char name[100];
    int ID;
    int chinese;
    void (*p)(int , int);
};
void printf_1(int a, int b){
    int i,j;
    for(i=0;i<a;i++){
        for(j=0;j<b;j++)
        printf(" * ");
        printf("\n");
    }
}

struct stu_t arr[]={
    {"dong1",111,97,printf_1},
    {"dong2",222,90,printf_1},
    {"dong3",333,97,printf_1},
    {"dong4",444,97,printf_1},
    {"dong5",555,97,printf_1}
};
int main(int argc, const char *argv[])
{  
    int i,a,b; 
    printf("Please Input wide =");
    scanf("%d",&a);
    printf("Please Input long =");
    scanf("%d",&b);
    getchar();
    for(i=0;i<5;i++)
   {
    printf("name:%s  ID:%d  chinese:%d\n",arr[i].name,arr[i].ID,arr[i].chinese);
   arr[i].p(a , b);
   }
  // printf("\0");
    return 0;
}

/***********************************************************/

