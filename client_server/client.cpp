#define WIN32_LEAN_AND_MEAN //этот макрос должен быть обязательно включен для сетевой разработки на винде

#include <iostream>
#include <windows.h>
#include <winSock2.h>
#include <WS2tcpip.h>

using namespace std;

//test socket clietnt

int main()
{
    setlocale(LC_ALL, "RU");

    WSADATA wsaData; //это струкутра данных для инфы о сокете
    ADDRINFO addrInfo; //это структура для фукции getaddrinfo
    ADDRINFO* addrResult = nullptr;
    int result;
    SOCKET ConnectSocket = INVALID_SOCKET; //инициализируем его константой, потому что сокет пока неверный.

    const char* sendBuffer = "Hello, Bro! :) [CLIENT]"; //для отправки сообщения на сервер. Буфер для отправки
    char revBuffer[512]; //Буфер для приема
    
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        cout << "WSAStartup failed. resuld = " << result << endl;
        return 1;
    }

    ZeroMemory(&addrInfo, sizeof(addrInfo)); //ZeroMemory работает только на винде

    //задаем параметры в структуру данных
    addrInfo.ai_family = AF_INET; //семейство протоколов. У нас AF_INET это IPv4
    addrInfo.ai_socktype = SOCK_STREAM; //тип сокетов
    addrInfo.ai_protocol = IPPROTO_TCP; //протокол

    result = getaddrinfo("localhost","666", &addrInfo, &addrResult); //эта функция проверяет наличие удаленного узла в сети и прогладывает к нему путь

    if (result != 0)
    {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    //addrResult->ai_next; //это для того, если несколько мест подключения


    //СОЗДАНИЕ СОКЕТА
    //в параметры передаем полученные данные из getaddrinfo
    ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);

    //проверяем создание сокета
    if (ConnectSocket == INVALID_SOCKET)
    {
        cout << "Ошибка при создании сокета!" << endl;
        freeaddrinfo(addrResult);//очищаем структуру данных
        WSACleanup();
        return 1;
    }

    //делаем подключение к созданному сокету
    result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);

    //проверяем результат подключения
    if (result == SOCKET_ERROR)
    {
        cout << "Ошибка при подключении к серверу!" << endl;

        //функция для закрытия соцета
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    result = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), 0);

    if (result == SOCKET_ERROR)
    {
        cout << "Ошибка при отправке сообщения на сервер!" << endl;

        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    cout << "Bytes send: " << result << endl;

    //освобождаем сокет
    result = shutdown(ConnectSocket, SD_SEND);
    //параметр константа SD_SEND полностью закрывает сокет на отправку. Но прием будет работать

    if (result == SOCKET_ERROR)
    {
        cout << "Ошибка при закрытии сокета!\t" << result << endl;

        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    do
    {
        ZeroMemory(revBuffer, 512);//чистим буффер

        result = recv(ConnectSocket, revBuffer, 512, 0);//функция для приема данных

        //проверяем заполнение буффера
        if (result > 0)
        {
            cout << "Received bytes: " << result << endl;
            cout << "Received data: " << revBuffer << endl;
        }
        else if (result == 0)
        {
            cout << "Connection closed!" << endl;

        }
        else
        {
            cout << "Ошибка при получении ответа!" << endl;
        }
    } while (result > 0);

    closesocket(ConnectSocket);
    ConnectSocket = INVALID_SOCKET;
    freeaddrinfo(addrResult);//очищаем структуру данных

    WSACleanup();

    system("pause");

    return 0;
}