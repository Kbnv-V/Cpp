#include <iostream>
#include <algorithm> //библиотека для использования алгоритмов STL
#include <vector>
using namespace std;

//STL. Алгоритм copy и copy_if. Позволяет сделать выборку из коллекции

class Person
{
public:
    Person(string name, double scoure, int age)
    {
        this->Name = name;
        this->Scoure = scoure;
        this->Age = age;

    }

    //функтор, который является предикатом
    bool operator ()(const Person& p)
    {
        return p.Scoure >= 180;
    }

    string Name;
    double Scoure;
    int Age;
};


int main()
{
    setlocale(LC_ALL, "RU");

    vector<int> vec = { 512, 14, 992, 412, 6 };

    vector<Person> people =
    {
        Person("Вася", 140, 20),
        Person("Ваня", 150, 22),
        Person("Андрей", 180, 19),
        Person("Маша", 174, 21),
        Person("Миша", 180, 18),
        Person("Игорь", 172, 24),
        Person("Рома", 190, 22)
    };

    vector<Person> result;

    copy(people.begin(), people.end(), back_inserter(result)); //back_inserter - функция позволяет переместить элементы коллекции в другую коллекцию.
    //в back_inserter параметром передаем вектор result

    cout << "Всего элементов в result - " << result.size() << endl;

    for (auto val : result)
    {
        cout << "Имя: " << val.Name << "\tБаллы: " << val.Scoure << endl;
    }

    vector<Person> newResult;

    copy_if(people.begin(), people.end(), back_inserter(newResult), [](const Person& p) {return p.Scoure > 150 && p.Age < 20; }); //в copy_if передается 4 параметра.
    //4 параметр это условие, по которому осуществляется выборка

    cout << "Всего элементов в newResult - " << newResult.size() << endl;

    for (auto val : newResult)
    {
        cout << "Имя: " << val.Name << "\tБаллы: " << val.Scoure << endl;
    }
}
