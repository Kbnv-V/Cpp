#include <iostream>
#include <map>
using namespace std;

//STL - map и multimap
//контейнеры хранят в себе пару: ключ и значение
//map хранит в себе уникальные значения, а multimap может хранить все

int main()
{
    setlocale(LC_ALL, "RU");

    map<int, string> newMap; //объявление map

    //по ключу строится бинарное дерево

    newMap.insert(pair<int, string>(1, "Телефон")); //это синтаксис добавления ключа и значения в map
    newMap.insert(make_pair<int, string>(2, "Монитор")); //это добавление ключа/значения через метод make_pair
    newMap.emplace(3, "Ноутбук"); //этот метод упрощает добавление ключа/значения в map

    //если пытаться добавить элемент уже с ключом, который есть в map, то элемент не будет добавлен

    auto it = newMap.find(1);
    if (it != newMap.end())
    {
        cout << it->second << endl;
    }

    cout << newMap[3] << endl;


    map<string, int> myMap;

    myMap.emplace("Иван", 10000);
    myMap.emplace("Сергей", 20000);
    myMap.emplace("Женя", 141200);
    myMap.emplace("Костя", 1412400);

    myMap["Женя"] = 1054000;

    myMap["Вася"] = 2001124; //если такого ключа нет в map, то в map будет добавлен новый ключ. Далее такой ключ добавлить будет уже нельзя

    cout << myMap["Женя"] << endl;
    cout << myMap.at("Костя") << endl;

    //тут обработка исключения при попытке получить ключ через метод at
    try
    {
        myMap.at("Владимир") = 991000; //чере метод at если ключа нет в map, то новый не добавится. At бросит исключение
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
    }

    myMap.erase("Иван"); //удаление элемента из map


    //работа с multimap

    multimap<string, int> myMultimap;

    myMultimap.emplace("Гриша", 112031);
    myMultimap.emplace("Гриша", 11412031);
    myMultimap.emplace("Маша", 112031);

    //у multimap не перегружены [] и нет метода at

}
