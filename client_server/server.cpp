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
    SOCKET ClientSocket = INVALID_SOCKET; //инициализируем его константой, потому что сокет пока неверный. **Это будет клиентский сокет
    SOCKET ListenSocket = INVALID_SOCKET; //**это слушающий сокет на сервере

    const char* sendBuffer = "Hello, Bro! :) [SERVER]"; //для отправки сообщения на сервер. Буфер для отправки
    char revBuffer[512]; //Буфер для приема

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        cout << "WSAStartup failed. resuld = " << result << endl;
        return 1;
    }

    ZeroMemory(&addrInfo, sizeof(addrInfo)); //ZeroMemory работает только на винде

    //задаем параметры в структуру данных. Так же, как и в клиенте
    addrInfo.ai_family = AF_INET; //семейство протоколов. У нас AF_INET это IPv4
    addrInfo.ai_socktype = SOCK_STREAM; //тип сокетов
    addrInfo.ai_protocol = IPPROTO_TCP; //протокол
    addrInfo.ai_flags = AI_PASSIVE; //**тут мы говорим, что хотим получить инфу для пассивной стороны (т.е.) сервера

    result = getaddrinfo(NULL, "666", &addrInfo, &addrResult); //эта функция проверяет наличие удаленного узла в сети и прогладывает к нему путь
    //**так как сервер никакого адреса не знает, то в функции в адрес задаем NULL

    if (result != 0)
    {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    //addrResult->ai_next; //это для того, если несколько мест подключения


    //СОЗДАНИЕ СОКЕТА
    //в параметры передаем полученные данные из getaddrinfo. **в этом месте на сервере мы создаем слушающий сокет
    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);

    //проверяем создание сокета
    if (ListenSocket == INVALID_SOCKET)
    {
        cout << "Ошибка при создании сокета!" << endl;
        freeaddrinfo(addrResult);//очищаем структуру данных
        WSACleanup();
        return 1;
    }

    //делаем подключение к созданному сокету. **создаем привязку слушающего сокета к адресу из getaddrinfo.
    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);

    //проверяем результат подключения
    if (result == SOCKET_ERROR)
    {
        cout << "Binding socket failed!" << endl;

        //функция для закрытия соцета
        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    //устанавливаем режим прослушивания на слушающий сокет
    result = listen(ListenSocket, SOMAXCONN);//1 параметр это слушающий сокет, 2 параметр - максимальное кол-во соединений, которое может обслужить сокет
    //функция listen блокирующая. Они будет ждать соединения.

    if (result == SOCKET_ERROR)
    {
        cout << "Listening socket failed!" << endl;

        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    //функция accept возвращает сокет, который получен при соединении с клиентом
    ClientSocket = accept(ListenSocket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET)
    {
        cout << "Accepting socket failed!" << endl;
        closesocket(ClientSocket);
        ClientSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket); //закрываем слушающий сокет

    

    do
    {
        ZeroMemory(revBuffer, 512);//чистим буффер

        result = recv(ClientSocket, revBuffer, 512, 0);//функция для приема данных

        //проверяем заполнение буффера
        if (result > 0)
        {
            cout << "Received bytes: " << result << endl;
            cout << "Received data: " << revBuffer << endl;

            result = send(ClientSocket, sendBuffer, 512, 0);

            if (result == SOCKET_ERROR)
            {
                cout << "Ошибка при отправке ответа клиенту!" << endl;

                closesocket(ClientSocket);
                ClientSocket = INVALID_SOCKET;
                freeaddrinfo(addrResult);//очищаем структуру данных

                WSACleanup();
                return 1;
            }
        }
        else if (result == 0)
        {
            cout << "Connection closed..." << endl;

        }
        else
        {
            cout << "Ошибка при получении ответа!" << endl;
            closesocket(ClientSocket);
            ClientSocket = INVALID_SOCKET;
            freeaddrinfo(addrResult);//очищаем структуру данных

            WSACleanup();
            return 1;
        }
    } while (result > 0);

    //освобождаем сокет
    result = shutdown(ClientSocket, SD_SEND);
    //параметр константа SD_SEND полностью закрывает сокет на отправку. Но прием будет работать

    if (result == SOCKET_ERROR)
    {
        cout << "Ошибка при закрытии клиентского сокета сокета!\t" << result << endl;

        closesocket(ClientSocket);
        ClientSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);//очищаем структуру данных

        WSACleanup();
        return 1;
    }

    closesocket(ClientSocket);
    ClientSocket = INVALID_SOCKET;
    freeaddrinfo(addrResult);//очищаем структуру данных

    WSACleanup();

    system("pause");

    return 0;
}
