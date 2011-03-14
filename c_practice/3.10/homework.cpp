#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Node
{
	public:
		Node<T>* next;
		T data;
};

template <class T>
class List
{
	protected:
		Node<T>* head;

	public:
		List()
		{
			head = NULL;
		}

		~List()
		{
			while(!isEmpty())
			{
				delete removeHead();
			}
		}

		void insertHead(T data)
		{
			Node<T>* p = new Node<T>;
			p->data = data;
			p->next = head;
			head = p;
		}

		Node<T>* getHead()
		{
			return head;
		}

		Node<T>* removeHead()
		{
			if(head == NULL)
			  return NULL;

			Node<T>* p = head;
			head = head->next;
			return p;
		}

		Node<T>* getNext(Node<T>* p)
		{
			if(p == NULL)
			  return NULL;
			return p->next;
		}

		bool isEmpty()
		{
			return head == NULL;
		}
};

class Person
{
	public:
		virtual void print() = 0;

		string name;
		string tel;
		string type;
		int age;
};

class Teacher : public Person
{
	public:
		Teacher(string name, string tel, string type, int age)
		{
			this->name = name;
			this->tel = tel;
			this->type = type;
			this->age = age;
		}
		void print()
		{
			cout << name
				<< "\t"
				<< type
				<< "\t"
				<< tel
				<< "\t"
				<< age
				<< endl;
		}
};

class Student: public Person
{
	public:
		Student(string name, string tel, string type, int age, int score)
		{
			this->name = name;
			this->tel = tel;
			this->type = type;
			this->age = age;
			this->score = score;
		}
		int score;
		void print()
		{
			cout << name
				<< "\t"
				<< type
				<< "\t"
				<< tel
				<< "\t"
				<< age
				<< "\t"
				<< score
				<< endl;
		}
};


/* Persons 表示人的集合 */
class Persons
{
	public:
		List<Person*> persons;

		/* init函数将文件的内容读取出来，放入persons链表中 */
		void init(string file)
		{
			FILE* f = fopen(file.c_str(), "rw");
			char name[32];
			char type[32];
			char tel[32];
			int age;
			int score;
			Person* person;

			if(f == NULL)
			{
				return;
			}
			
			char buf[1024];
			char* ret;
			while(1)
			{
				ret = fgets(buf, sizeof(buf), f);
				if(ret == NULL)
				{
				  break;
				}

				if(strlen(buf) < 10)
				  continue;

				if(strstr(buf, "Teacher") == NULL)
				{
					sscanf(buf, "%s %d %s %s %d", name, &age, type, tel, &score);
					person = new Student(name, tel, type, age, score);
				}
				else
				{
					sscanf(buf, "%s %d %s %s", name, &age, type, tel);
					person = new Teacher(name, tel, type, age);
				}

				persons.insertHead(person);
			}

		}

		/* print将链表的内容打印出来 */
		void print()
		{
			Node<Person*>* tmp = persons.getHead();
			while(tmp)
			{
				tmp->data->print();
				tmp = persons.getNext(tmp);
			}
		}
};

int main()
{
	Persons p;
	p.init("input.txt");
	p.print();
	return 0;
}
