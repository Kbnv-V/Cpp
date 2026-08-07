#include "GetLog.h"
#include <iostream>
#include <fstream>
#include <sys/inotify.h>
#include <vector>
#include <map>
using namespace std;

bool GetLog::SetStatusModule(bool value)
{
	statusModule = value;

	return true;
}

bool GetLog::GetStatusModule()
{
	return false;
}

void GetLog::StartLogMonitoring()
{
	statusModule = true;

	logThread = thread([this] {GetAllLogs(); });
}

void GetLog::StopLogMonitoring()
{
	if (logThread.joinable())
	{
		logThread.join();
	}

	statusModule = false;
}

void GetLog::GetAllLogs()
{
	string smtpLogPatch = "/home/bitrix/www/bitrix/mailer.txt"; //путь до файла с логами smtp
	string ldapLogPatch = "/home/bitrix/www/bitrix/ldap_logger.txt"; //путь до файла с логами ldap

	vector<string> filesPatch = { smtpLogPatch, ldapLogPatch };

	map<int, string> mapWatch; //тут храним пары id дескриптора => путь до файла
	map <string, ifstream> filesStreams; //тут храним потоки по открытым файлам

	int fileDeskriptor = inotify_init(); //получаем файловый дескриптор

	//проверяем на ошибки
	if (fileDeskriptor == -1)
	{
		return 1;
	}

	for (auto filePatch : filesPatch)
	{
		int wd = inotify_add_watch(fileDeskriptor, filePatch.c_str(), IM_MODIFY); //в параметры передаем файловый дескриптор, путь до файла и событие

		if (wd == -1)
		{
			ofstream logger;

			logger.open("logMonitor_logger.txt");

			if (logger.is_open())
			{
				logger << "Не удалось добавить в мониторинг файл " << filePatch << "\n";
			}

			continue;
		}

		mapWatch[wd] = filePatch;

		filesStreams[filePatch].open(filePatch, ios::ate); //тут мне создаем ключ и сразу можем вызвать у него метод open
		//так как мы обращаемся к ключу в мап, а у него значение ifstream, то можем вызвать метод и сразу присвоить значение
	}

	char buffer[sizeof(struct inotify_event) + NAME_MAX + 1];
	//размер буффера зависит от размера inotify_event + место для имена файла (NAME_MAX + 1)
	//далее по коду в buffer будет писать read(). Туда он будет писать структуру событий, которые произошли
	
	while (statusModule)
	{
		//read() блокирует поток до наступления события в любом файле
		read(fd, buffer, sizeof(buffer));

		//создаем указатель event и присваиваем ему адрес на buffer с новым типом данных
		struct inotify_event* event = (struct inotify_event*)buffer;

		string filePatch = mapWatch[event->wd]; //определяем измененный файл

		string line;
		auto& fileStream = filesStreams[filePatch];
		fileStream.clear(); //сбрасываем EOF (End of file). Это состояние файлового потока. Говорит, что файл прочитан до конца

		while (getline(fileStream, line))
		{
			string message;

			if (line.find("error") != string::npos || line.find("failed") != string::npos)
			{
				message = "В логе " + filePatch + " обнаружена запись с ошибкой!";
				string command = "php /home/bitrix/www/local/server_monitor/send_mess.php" + message;
			}
		}

		close(fileDeskriptor);
		return 0;
	}
}

void GetLog::CheckString(const string log)
{

}


