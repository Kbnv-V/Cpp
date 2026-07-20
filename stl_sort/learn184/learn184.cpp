#include <iostream>
#include <algorithm> //библиотека для использования алгоритмов STL
#include <vector>
using namespace std;

//STL. Алгоритм SORT

class Person
{
public:
    Person(string name, double scoure)
    {
        this->Name = name;
        this->Scoure = scoure;
    }

    //функтор, который является предикатом
    bool operator ()(const Person& p)
    {
        return p.Scoure >= 180;
    }

    string Name;
    double Scoure;
};

//это предикат
bool func(int a)
{
    return a > 0;
}

bool func1(int a)
{
    return a <= 0;
}

bool pred(int a, int b)
{
    return a > b;
}

int main()
{
    setlocale(LC_ALL, "RU");

    int const SIZE = 5;
    int arr[SIZE] = { 1, -12, 44, -412, 5 };

    sort(arr, arr + SIZE, [](int a, int b) {return a > b; });

    for (int val : arr)
    {
        cout << val << endl;
    }

    cout << "------------------------------------\n";

    vector<int> vec = { 1, 512, -14, 0, 991, -412, -0, 5 };

    sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; }); //без 3 параметра стандарно сортирует от меньшено к большему. С 3 параметром сортирует от большего к меньшему
    //так же 3 парамтером можно указывать лямбду

    vector<Person> people =
    {
        Person("Вася", 140),
        Person("Ваня", 150),
        Person("Андрей", 180),
        Person("Маша", 174),
        Person("Миша", 190),
        Person("Игорь", 172),
        Person("Рома", 182)
    };

    sort(people.begin(), people.end(), [](const Person& p1, const Person& p2) { return p1.Name < p2.Name; });

    for (int val : vec)
    {
        cout << val << endl;
    }

    cout << "------------------------------------\n";

    for (auto val : people)
    {
        cout << "Имя: " << val.Name << "\t Баллы: " << val.Scoure << endl;
    }

    //int result = count_if(people.begin(), people.end(), people.front()); //в качетсвет 3 параметра передаем ссылку на 1 объект в векторе

    //cout << result << endl;


}
