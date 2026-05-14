#include <iostream>
using namespace std;

//умные указатели
//для автоматической очистки указателя надо создавать класс, который это будет делать
//это и есть умный указатель

template<typename T>
class SmartPointer
{
public:
    SmartPointer(T *value)
    {
        this->ptr = value;
    }

    ~SmartPointer()
    {
        delete ptr;
    }

    T& operator *()
    {
        return *ptr;
    }

private:
    T* ptr;

};

int main()
{
    setlocale(LC_ALL, "RU");
    /*
    int* ptr = new int(5);
    delete ptr;
    */

    SmartPointer<int> pointer = new int(10);

    cout << *pointer << endl;
}
