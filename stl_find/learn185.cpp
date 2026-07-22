#include <iostream>
#include <algorithm> //библиотека для использования алгоритмов STL
#include <vector>
using namespace std;

//STL. Алгоритм FIND для поиска

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


int main()
{
    setlocale(LC_ALL, "RU");

    vector<int> vec = { 512, 14, 992, 412, 6 };

    /*
    auto iter{ vec.begin() };

    for (auto start{ vec.begin() }; start != vec.end(); start++)
    {
        cout << *start << endl;
    }
    */

    vector<Person> people =
    {
        Person("Вася", 140),
        Person("Ваня", 150),
        Person("Андрей", 180),
        Person("Маша", 174),
        Person("Миша", 180),
        Person("Игорь", 172),
        Person("Рома", 190)
    };

    //это стандарнтный алогоритм для поиска
    auto res = find(vec.begin(), vec.end(), 9911); //синтаксис алгоритма для поиска. 1 параметр начало диапазона, 2 - конец диапазона, 3 значение, которое хотим найти

    //cout << *res << endl;

    //если find в заданном диапазоне ничего не нашел, то он вернет указатель на конец коллекции (vec)
    if (res == vec.end())
    {
        cout << "Значение не найдено!" << endl;
    }

    //find_if ищет по условию. Так же задается диапазон поиска, и в 3 пар. задаем лямбду-предикат
    //условие можно задать любое
    auto result = find_if(vec.begin(), vec.end(), [](int val) { return val % 2 == 0; });

    //если четных чисел нет, то алгоритм вернет указатель на последний элемент коллекции. А если четно есть, то он вернет первое найденное значение в коллекции
    if (result == vec.end())
    {
        cout << "Четное число не найдено!" << endl;
    }
    else
    {
        cout << "Четное число найдено!" << endl;
    }

    //find_if_not инвертированный вариант алгоритма find_if. Условия работают наоборот
    auto result1 = find_if_not(vec.begin(), vec.end(), [](int val) { return val > 0; });

    //если четных чисел нет, то алгоритм вернет указатель на последний элемент коллекции. А если четно есть, то он вернет первое найденное значение в коллекции
    if (result1 == vec.end())
    {
        cout << "-" << endl;
    }
    else
    {
        cout << "+" << endl;
    }

    //АЛОГОРИТМЫ С КЛАССОМ PERSON

    //find без перегрузки операторов сравнения с объектами классов не работает

    //find_if и find_if_not не требует перегрузки операторов сравнения
    auto resultPers = find_if(people.begin(), people.end(), [](const Person& val) { return val.Scoure >= 190; });

    if (resultPers == people.end())
    {
        cout << "Нет студентов, у кого более 190 баллов!" << endl;
    }
    else
    {
        cout << "Есть студенты, у кого более 190 баллов!" << endl;
    }

    //TEST CODE

    std::vector<int> numcoll{ 5,2,65,31,5,88,21,96 };

    for (const auto& num : numcoll)
    {
        std::cout << num << '\x20';
    }
    std::cout << '\n';

    auto it = find(numcoll.begin(), numcoll.end(), 88);

    if (it != numcoll.end())
    {
        int idx = it - numcoll.begin();
        std::cout << "Found \"" << *it << "\" at index \"" << idx << "\"";
    }
}