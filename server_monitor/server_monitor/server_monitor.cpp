#include <iostream>
#include <chrono>
#include <thread>
#include"Menu.h"
#include"GetDisk.h"
#include"pid_command.h"
#include<fstream>
#include<signal.h>
#include<unistd.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    int oldPid = ReadPid();

    if (oldPid == 0)
    {
        cout << "Программа уже запущена. (PID: " << oldPid << ")" << endl << endl;
        cout << "Команды для управления: " << endl;
        cout << " kill -USR1 " << oldPid << " - Запуск мониторинга свободного места на диске." << endl;
        cout << " kill -USR12 " << oldPid << " - Остановка мониторинга свободного места на диске." << endl;
        cout << " kill -TERM " << oldPid << " - Завершение работы программы." << endl;
    }

    WritePid();
    cout << "Программа зпущена. PID - " << getpid() << endl;

    signal(SIGUSR1, SignalHandler);
    signal(SIGUSR2, SignalHandler);
    signal(SIGTERM, SignalHandler);
    

    Menu newMenu;

    pMenu = &newMenu;

    pMenu->StartModule();

    DeletePid();

    return 0;
}
