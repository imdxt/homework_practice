#include <iostream>
#include <cstring>
#include "person.h"
using namespace std;
Person::Person(const char *name, int age)
:name(NULL), age(age)
{
cout<<"create person"<<endl;
this->name = new char[strlen(name)+1];
strcpy(this->name, name);
}
void Person::display() const
{
cout<<"<<<< display person information >>>>"<<endl
<<" Name:"<<name<<endl<<" Age:"<<age<<endl;
}
Person::~Person()
{
cout<<"delete person"<<endl;
delete[] name;
}