#include <iostream>
using namespace std;
class MyString
{
friend ostream &operator<<(ostream &, const MyString &);
friend MyString operator+(const MyString &, const MyString &);
public:
MyString(const char *);
MyString(const MyString &);
~MyString(void);
MyString &operator=(const MyString &);
int length(void) const;
bool isEmpty(void) const;
private:
char *data;
int len;
};