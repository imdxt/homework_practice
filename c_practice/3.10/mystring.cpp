#include <iostream>
#include <string.h>
#include "mystring.h"
using namespace std;
MyString::MyString(const char *str)
{
cout<<"ctor"<<endl;
if(str==NULL) {
len = 0;
data = new char[1];
*data = '\0';
} else {
len = strlen(str);
data = new char[len+1];
strcpy(data, str);
}
}
MyString::MyString(const MyString &other)
{
cout<<"copy ctor"<<endl;
len = other.len;
data = new char[len+1];
strcpy(data, other.data);
}
MyString::~MyString(void)
{
cout<<"dtor"<<endl;
delete[] data;
}
MyString &MyString::operator=(const MyString &other)
{
cout<<"assignment"<<endl;
if(this==&other)
return *this;
delete[] data;
len = other.len;
data = new char[len+1];
strcpy(data, other.data);
return *this;
}
int MyString::length(void) const
{
return len;
}
bool MyString::isEmpty(void) const
{
return len==0;
}
ostream &operator<<(ostream &out, const MyString &str)
{
out << str.data;
return out;
}
MyString operator+(const MyString &a, const MyString &b)
{
cout<<"concatenate"<<endl;
MyString temp("");
delete[] temp.data;
temp.len = a.len + b.len;
temp.data = new char[temp.len + 1];
strcpy(temp.data, a.data);
strcat(temp.data, b.data);
return temp;
}
