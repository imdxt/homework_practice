#include <stdio.h>
typedef struct {
    int id;
    int chinese;
    char name[256];
}stu;
void swap(stu *a ,stu *b)
{
    stu temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int main(int argc, const char *argv[])
{
    stu stu1={10,20,"dong1"};
    stu stu2={100,200,"dong2"};
    swap(&stu1,&stu2);
    printf("   stu1  id      = %d      \n",stu1.id);
    printf("   stu1  chinese = %d      \n",stu1.chinese);
    printf("   stu1  name    = %s      \n",stu1.name);
    printf("   stu2  id      = %d      \n",stu2.id);
    printf("   stu2  chinese = %d      \n",stu2.chinese);
    printf("   stu2  name    = %s      \n",stu2.name);
    return 0;
}
