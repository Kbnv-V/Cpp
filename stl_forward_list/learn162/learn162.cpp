#include <iostream>
#include <forward_list>
using namespace std;

//forward_list - для реализации односвязных списков

int main()
{
    setlocale(LC_ALL, "RU");

    forward_list<int> fl;

    fl.push_front(111);
    fl.push_front(222);

    forward_list<int>::iterator it = fl.begin();
    // it++;
    //cout << *it << endl;

    fl.insert_after(it, 999);

    for (auto var : fl)
    {
        cout << var << endl;
    }
}
