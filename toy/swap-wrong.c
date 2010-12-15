#include <stdio.h>
void swap(int, int);
int main(int argc, const char *argv[])
{
    int a, b;
    a = 2;
    b = 3;
    swap(a, b);
    printf("a is now %d\nb is now %d\n",a,b);
    return 0;
}

void swap(int x, int y)
{
    int tmp;
    tmp = y;
    y = x;
    x = tmp;

}
