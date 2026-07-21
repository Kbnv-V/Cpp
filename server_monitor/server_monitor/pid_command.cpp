#pragma once
#include<fstream>
#include<iostream>
#include<signal.h>
#include"Menu.h"
#include"pid_command.h"
#include<unistd.h>

using namespace std;

Menu* pMenu = nullptr;

//функция для записи pid 
void WritePid()
{
    ofstream file("server_monitor.pid");
    if (file.is_open())
    {
        file << getpid();
        file.close();
    }
}

//функция для удаления pid файла
void DeletePid()
{
    remove("server_monitor.pid");
}

//чтение pid в файле
int ReadPid()
{
    ifstream file("server_monitor.pid");

    if (file.is_open())
    {
        int pid;

        file >> pid;
        file.close();

        return pid;
    }

    return 0;
}

//обработчики сигналов
void SignalHandler(int signal)
{
    if (signal == SIGUSR1)
    {
        cout << "Запуск мониторинг свободного места на диске." << endl;

        if (pMenu)
        {
            pMenu->StartDiskMonitor();
        }
    }
    else if (signal == SIGUSR2)
    {
        cout << "Остановка мониторинга свободного места на диске." << endl;

        if (pMenu)
        {
            pMenu->StopDiskMonitor();
        }
    }
    else if (signal == SIGTERM)
    {
        cout << "Завершение работы." << endl;

        DeletePid();
        exit(0);
    }
}