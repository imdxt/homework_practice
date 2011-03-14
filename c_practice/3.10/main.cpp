#include <iostream>
#include "mystring.h"
using namespace std;
int main()
{
MyString str("hello");
MyString str1 = str;
cout<<"Length of str1: "<<str1.length()<<endl;
cout<<"Value of str1: "<<str1<<endl;
MyString str2 = "";
cout<<"Is str2 empty? "<<(str2.isEmpty()?"true":"false")<<endl;
str2 = " world";
cout<<"Now value of str2: "<<str2<<endl;
cout<<"Now value of str: "<<str1+str2<<endl;
cout<<"Value of another expression: "<<str1 + "_world"<<endl;
cout<<"Value of yet another expression: "<<"Hello," + str2<<endl;
MyString str3 = str1 + str2;
cout<<"Value of str3: "<<str3<<endl;
return 0;
}