#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
using namespace std;

//STL - stack. Адаптер контейнеров

int main()
{
    setlocale(LC_ALL, "RU");

    stack<int, deque<int>> newStack; //синтаксис с определением типа данных и какой контейнер будем использовать

    newStack.push(1); //сначала создается объект, потом перемещается в коллекцию(stack)
    newStack.push(2);
    newStack.push(3);

    newStack.emplace(4); //создает объект сразу в коллекции. Этот метод быстрее

    auto a = newStack._Get_container(); //метод для извлечения контейнера. После извлевлечения можно использовать базовые методы контейнера, который мы задали выше

    cout << a[2] << endl;

    cout << "Размер стека: " << newStack.size() << endl;
    cout << "Метод pop: " << newStack.top() << endl;

    while (!newStack.empty())
    {
        cout << newStack.top() << endl;
        newStack.pop();
    }
}
