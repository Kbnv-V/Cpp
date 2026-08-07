#include <iostream>
#include<fstream>
#include <chrono>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "GetDisk.h"
#include "GetLog.h"

using namespace std;

string response; //переменная для ответа клиенту

//создаем агентов
GetDisk diskMonitor;
GetLog logMonitor;


//--- ОБРАБОТКА КОМАНД ---
void ProcessingCommand(const string command)
{
    //--- ЗАПУСК МОНИТОРИНГА ДИСКА ---
    if (command == "disk_monitor_start")
    {
        ofstream out("log_server.txt", ios::app);
        out.open("log_server.txt");
        if (out.is_open())
        {
            out << "Команда на включение мониторинга диска." << endl;
        }
        out.close();

        response = "Мониторинг диска запущен.";
        /*
        if (diskMonitor.GetStatusModule())
        {
            //вернуть, что служба уже запущена
        }
        else
        {
            diskMonitor.StartDiskMonitoring();

            //после запуска вернуть, что служба запустилась
        }
        */
    }
    //--- ОСТАНОВКА МОНИТОРИНГА ДИСКА ---
    else if (command == "disk_monitor_stop")
    {
        ofstream out("log_server.txt");
        out.open("log_server.txt");
        if (out.is_open())
        {
            out << "Команда на остановку мониторинга диска. Time - " << endl;
        }
        out.close();

        response = "Мониторинг диска остановлен.";
        /*
        if (!diskMonitor.GetStatusModule())
        {
            //вернуть, что служба уже остановлена
        }
        else
        {
            diskMonitor.StopDiskMonitoring();

            //после запуска вернуть, что служба остановилась
        }
        */
    }
    //--- ЗАПУСК МОНИТОРИНГА ЛОГОВ ---
    else if (command == "log_monitor_start")
    {
        //запуск мониторинга логов еще не готов
    }
    //--- ОСТАНОВКА МОНИТОРИНГА ЛОГОВ ---
    else if (command == "log_monitor_stop")
    {
        //останова мониторинга логов еще не готова
    }
    // --- ПОЛУЧЕНИЕ СТАТУСА ВСЕХ СЛУЖБ ---
    else if (command == "service_status")
    {
        //получение статус всех служб еще не готово
    }

}


//--- СОЗДАНИЕ СЛУШАЮЩЕГО СОКЕТА ---
void SockThread()
{
    //создание сокета
    int sockServer = socket(AF_INET, SOCK_STREAM, 0);

    if (sockServer < 0)
    {
        cout << "Ошибка при создании сокета";
    }

    //разрешаем многократное подключение к сокету
    int opt = 1;
    setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //привязка сокета к порту
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(666);

    //привязка сокета к адресу
    bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));

    //переводим сокет в решим прослушки
    listen(sockServer, 10);

    while (true)
    {
        //accept возвращает сокет для общения с клиентом
        int sockClient = accept(sockServer, NULL, NULL);

        char buffer[1024];

        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(sockClient, buffer, sizeof(buffer) - 1, 0);

        if (bytes > 0)
        {
            string cmd(buffer, bytes);

            ProcessingCommand(cmd);

            send(sockClient, response.c_str(), response.size(), 0); //отправка ответа клиенту
        }

        close(sockClient);
    }

    close(sockServer);
}

int main()
{
    cout << "Сервер запущен" << endl;

    thread sockThread(SockThread);

    sockThread.detach();

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}