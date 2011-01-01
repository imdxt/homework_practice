#include <stdio.h>
struct stu{
    int id;
    char name[256];
    float chinese;
    float math;
    float average;
};
int main(int argc, const char *argv[])
{
    struct stu stu1={1,"dong1",99.0,98.0,98.5};
    FILE *fp1;
    fp1=fopen("dong.txt","w");
    fprintf(fp1, "%-15s%-15s%-15s%-15s%-15s\n","ID","name","chinese","math","average");
    fclose(fp1);
    fp1=fopen("dong.txt","a+");
    printf("Input ID name Chinese math \n");
    while(1)
    {
    fscanf(stdin,"%d %s %f %f",&stu1.id,stu1.name, &stu1.chinese, &stu1.math);
    stu1.average = (stu1.chinese + stu1.math)/2;
    fprintf(fp1,"%-15d%-15s%-15.1f%-15.1f%-15.1f\n",stu1.id, stu1.name, stu1.chinese, stu1.math, stu1.average);
    fflush(fp1);
    }
    fclose(fp1);
    return 0;
}
