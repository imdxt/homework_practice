#ifndef PERSON_H
#define PERSON_H
class Person
{
public:
Person(const char *name, int age);
~Person();
void display() const;
private:
char *name;
int age;
};
#endif //PERSON_H