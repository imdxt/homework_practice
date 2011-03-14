#include <iostream>

using namespace std;

//template < class T>
/*class Node
{
public:
    Node* next;
    int date;

};


*/
//template <class T>
//


class List
{
public:
   List* head;
   int date;
   const int a;
   //Node* head;
   List()//:head(NULL)
   {
        head = NULL;
   }
   void insertHead( int value)
   {
        List* p = new List;
        p->head = head;
        p->date = value;
        head = p;
   }
    void print()
    {
        List* p = head;
        while(p)
        {
            cout << p->date << endl;
            p = p->head;
        }
    }

};

int main()
{
   List list;

   list.insertHead(5);
   list.insertHead(10);
   list.insertHead(20);
   
   list.print();
   
   return 0;
}
