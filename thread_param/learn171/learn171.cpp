#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void doWork(int a, int b, string message)
{
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Начало работы функции doWork" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Параметр a - " << a << endl;
    cout << "Параметр b - " << b << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Сумма параметров a и b - " << a + b << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Выпол сообщения - " << message << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Конец работы функции doWork" << endl;

}

int main()
{
    setlocale(LC_ALL, "RU");

    //doWork(1240, 54122);

    thread newTh(doWork, 100, 150, "Тестовое сообщение"); //синтаксис передачи параметров в поток

    for (size_t i = 0; i < 10; i++)
    {
        cout << "ID потока - " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    newTh.join();
}
