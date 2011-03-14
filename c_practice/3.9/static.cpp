#include <iostream>

using namespace std;

class A
{
    public:
    static int i;

};

int A::i;

int main()
{
    A a,b;
    b.i = 20;
    a.i = 10;

    cout << a.i << endl << b.i << endl;

    A::i = 30;

    cout << a.i << endl << b.i << endl;

    return 0;
}
