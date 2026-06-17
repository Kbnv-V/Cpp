#include <iostream>
#include <thread>
#include <chrono> //для работы со временем
using namespace std;

//многопоточное программирование. thread

void doWork()
{
    for (size_t i = 0; i < 10; i++)
    {
        cout << "ID потока: " << this_thread::get_id() << " DoWork " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000)); //прост.имен chorno тут используется для паузы
    }
}

int main()
{
    setlocale(LC_ALL, "RU");

    thread th(doWork); //чтобы выполнять параллельно другую задачу, надо создать экземпляк thread и передать в него указатель на функцию (без скобок)
    thread th1(doWork);

    //th.detach(); //разрывает связь между объектом th и потоком, который выполняется

    //doWork();

    for (size_t i = 0; i < 10; i++)
    {
        cout << "ID потока: " << this_thread::get_id() << " main " << i << endl; //синтаксис изпользование метода из пространства имен. Тут получаем ID потока
        this_thread::sleep_for(chrono::milliseconds(500)); //прост.имен chorno тут используется для паузы. приостанавливает выполнение потока
    }

    th.join(); //позволяет дожитаться выполнения задачи
    th1.join();
    //метод join надо вызывать в том месте, где нужно дождаться выполнения
}
