#include <iostream>
using namespace std;

class MyException : public exception
{
public:
    //тут мы определяем конструктор по умолчанию и передаем в него указатель на char. 
    //а далее через : вызываем конструктор exception и передаем туда параметр. Таким образом ничего более дописывать не надо.
    MyException(const char* msg, const int dataState) : exception(msg)
    {
        this->dataState = dataState;
    };

    int GetDataState()
    {
        return dataState;
    }
private:
    int dataState;

};

void Func(int value)
{
    if (value < 0)
    {
        throw exception("Число меньше 0!");
    }

    if (value == 0)
    {
        throw MyException("Число равно 0!", value);
    }

    if (value == 1)
    {
        throw exception("Число равно 1!");
    }
}

int main()
{
    setlocale(LC_ALL, "RU");

    try
    {
        Func(1);
    }
    catch (MyException& myEx) //лучше в начале указывать более конкретный тип данных
    {
        cout << myEx.what() << endl;
        cout << "Состояние объекта - " << myEx.GetDataState() << endl;
    }
    catch (const exception& ex)
    {
        cout << ex.what() << endl;
    }
}
