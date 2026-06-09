#include <iostream>
#include <vector>
#include <list>
using namespace std;

//STL - list

template <typename T>
void PrintList(const list<T>& list)
{
    for (auto i = list.cbegin(); i != list.cend(); ++i) //list.cbegin() и list.cend() это константные указатели
    {
        cout << *i << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");

    list<int> newList = {1, 4, 66, 11, 1453, 80, 1245, 80, 91, 88, 88, 109, 88};
    newList.push_back(100);
    newList.push_front(200);

    //newList.sort(); //метод для сортировки
    newList.unique(); //метод для поиска и удаления одинаковых значений в списке
    newList.reverse(); //метод переворачивает список. Теперь он в обратном порядке

    list<int>::iterator it = newList.begin(); //или можно записать auto it. Это будет короче

    advance(it, 3);//сдвигает итератор на несколько позиций вперед

    newList.assign(3, 809); //затирает старые значения и добавляет указанное. Первый параметр это кол-во элементов, а второй это само число

    PrintList(newList);

}
