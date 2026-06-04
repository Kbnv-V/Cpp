#include <iostream>
#include <vector>
using namespace std;

//итераторы

int main()
{
    setlocale(LC_ALL, "RU");

    vector<int> myVector = { 1, 2, 551, 9, 871, 872, 612 };
    vector<int> myVector1 = { 812, 815, 98, 12, 512, 12 };

    vector<int>::iterator iter = myVector.begin();//begin возвращает указатель на первый элемент вектора

    advance(iter, 3); //функция позвоялет перейти на определенное количество значений вперед. И в этот индекс потом можно добавить новое значение

    myVector.insert(iter, 999); //так добавляется новое значение в вектор через итератор. 1 аргумент - итератор, 2 - значение

    //iter++; //тут мы переходит к следующему элементу. Можно сказать, что двигаемся далее по элементам
    //cout << *iter << endl; //чтобы показать результат, надо разъименовать. Потому что мы получили указатель ранее
    
    //тут итератор будет в условии for
    for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++)
    {
        cout << *i << endl;
    }

    cout << "------------------" << endl;

    vector<int>::iterator itErase = myVector1.begin(); //итератор для удаления значения по индексу
    //advance(itErase, 2);
    //myVector1.erase(itErase); //метод для удаления знаечния из вектора через итератор.

    myVector1.erase(itErase, itErase + 3); // тут удаление диапазона элементов

    //для того чтобы использовать константный итератор, надо объявлять так - vector<int>::const_iterator
    //тут испольется констатный итератор
    for (vector<int>::const_iterator i = myVector1.cbegin(); i != myVector1.cend(); i++) //cbegin и cend тоже константные
    {
        cout << *i << endl;
    }

    cout << "------------------ Обратный итератор" << endl;

    //тут используется обратный итератор
    for (vector<int>::reverse_iterator i = myVector1.rbegin(); i != myVector1.rend(); i++) //rbegin и rend для обратного итератора
    {
        cout << *i << endl;
    }
}
